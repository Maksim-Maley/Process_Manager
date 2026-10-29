#include "ProcessManager.hpp"
#include <limits>
#include <stdexcept>

// Выводит таблицу всех процессов, видимых через Windows Tool Help API.
void ListProcesses()
{
	std::wcout << std::left;
	std::wcout << std::setw(5)
		<< L"PID" << L" | "
		<< std::setw(40)
		<< L"NAME" << L" | "
		<< std::setw(8)
		<< L"THREADS" << L" | "
		<< std::setw(12)
		<< L"PARENT PID" << L" | "
		<< std::setw(14)
		<< L"BASE PRIORITY" << L"|\n";
	std::wcout << L"--------------------------------------------------------------------------------------" << std::endl;

	// Создаём снимок списка процессов. Без него перечислить процессы нельзя.
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "CreateToolhelp32Snapshot failed. Error code: "
			<< errorCode << '\n';
		return;
	}

	PROCESSENTRY32W process{};
	process.dwSize = sizeof(process);

	// Получаем первую запись снимка. Если это не удалось, закрываем дескриптор.
	BOOL result = Process32FirstW(hProcessSnap, &process);
	if (!result)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "Process32FirstW failed. Error code: "
			<< errorCode << '\n';
		CloseHandle(hProcessSnap);
		return;
	}

	// Обрабатываем текущую запись, затем переходим к следующей.
	do
	{
		std::wcout << std::left
			<< std::setw(5) << process.th32ProcessID << L" | "
			<< std::setw(40) << process.szExeFile << L" | "
			<< std::setw(8) << process.cntThreads << L" | "
			<< std::setw(12) << process.th32ParentProcessID << L" | "
			<< std::setw(14) << process.pcPriClassBase << L"|\n";

		// Сбрасываем код ошибки перед вызовом, чтобы отличить конец списка от ошибки.
		SetLastError(ERROR_SUCCESS);
		result = Process32NextW(hProcessSnap, &process);
	} while (result);

	DWORD errorCode = GetLastError();
	if (errorCode != ERROR_NO_MORE_FILES)
	{
		std::cerr << "Process32NextW failed. Error code: "
			<< errorCode << '\n';
	}

	// Освобождаем дескриптор снимка после завершения перечисления.
	CloseHandle(hProcessSnap);
}

// Проверяет, содержится ли поисковая строка внутри имени процесса.
// CompareStringOrdinal с TRUE выполняет сравнение без учёта регистра.
bool ContainsSearchName(const std::wstring& processName, const std::wstring& searchName)
{
	const int lengthProcess = static_cast<int>(processName.length());
	const int lengthSearch = static_cast<int>(searchName.length());

	// Сдвигаем начало фрагмента по имени процесса и сравниваем фрагмент с запросом.
	for (int i = 0; i <= lengthProcess - lengthSearch; ++i)
	{
		int result = CompareStringOrdinal(
			processName.c_str() + i, // Начало проверяемого фрагмента.
			lengthSearch,             // Длина фрагмента.
			searchName.c_str(),       // Поисковая строка.
			lengthSearch,             // Длина поисковой строки.
			TRUE                      // Игнорировать регистр.
		);

		if (result == CSTR_EQUAL)
			return true; // Найдено совпадение.
	}

	return false; // Ни один фрагмент не совпал.
}

// Возвращает true, только если запрос состоит из ASCII-цифр и может быть PID.
bool IsNumericQuery(const std::wstring& searchName)
{
	if (searchName.empty())
		return false;

	return std::all_of(searchName.begin(), searchName.end(),
		[](wchar_t ch) { return ch >= L'0' && ch <= L'9'; });
}

// Ищет процесс по PID, если запрос числовой, иначе — по подстроке имени.
void FindProcesses(const std::wstring& searchName)
{
	// Защита на уровне самой функции: пустой запрос не должен совпасть со всеми именами.
	if (searchName.empty())
	{
		std::wcout << L"Укажите имя процесса или PID." << std::endl;
		return;
	}

	// Числовой запрос трактуем как PID; остальные запросы считаем текстом для поиска имени.
	const bool isNumeric = IsNumericQuery(searchName);
	DWORD targetPid = 0;

	if (isNumeric)
	{
		try
		{
			const unsigned long parsedValue = std::stoul(searchName);

			// Не допускаем преобразования числа за пределами типа DWORD.
			if (parsedValue > static_cast<unsigned long>((std::numeric_limits<DWORD>::max)()))
			{
				std::wcout << L"Ошибка: введённый PID превышает допустимый диапазон (DWORD).\n";
				return;
			}

			targetPid = static_cast<DWORD>(parsedValue);
		}
		catch (const std::invalid_argument&)
		{
			std::wcout << L"Ошибка: неверный формат PID.\n";
			return;
		}
		catch (const std::out_of_range&)
		{
			std::wcout << L"Ошибка: число слишком велико.\n";
			return;
		}
	}

	// Создаём один снимок и используем его для поиска по PID или имени.
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "CreateToolhelp32Snapshot failed. Error code: "
			<< errorCode << '\n';
		return;
	}

	PROCESSENTRY32W process{};
	process.dwSize = sizeof(process);

	bool found = false;
	BOOL result = Process32FirstW(hProcessSnap, &process);

	if (!result)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "Process32FirstW failed. Error code: "
			<< errorCode << '\n';
		CloseHandle(hProcessSnap);
		return;
	}

	do
	{
		bool match = false;

		// Ветвление логики в зависимости от типа запроса.
		if (isNumeric)
		{
			// Для PID требуется полное числовое совпадение.
			if (process.th32ProcessID == targetPid)
				match = true;
		}
		else
		{
			// Для имени ищем вхождение строки без учёта регистра.
			if (ContainsSearchName(process.szExeFile, searchName))
				match = true;
		}

		// Если найдено совпадение — выводим PID и имя и запоминаем результат.
		if (match)
		{
			std::wcout << process.th32ProcessID
				<< L"\t" << process.szExeFile << L"\n";
			found = true;
		}

		// Переходим к следующему процессу; ERROR_NO_MORE_FILES означает конец снимка.
		SetLastError(ERROR_SUCCESS);
		result = Process32NextW(hProcessSnap, &process);
	} while (result);

	DWORD errorCode = GetLastError();
	if (errorCode != ERROR_NO_MORE_FILES)
	{
		std::cerr << "Process32NextW failed. Error code: "
			<< errorCode << '\n';
	}
	else if (!found)
	{
		std::wcout << L"Процесс не найден.\n";
	}

	// Закрываем снимок и при успешном поиске, и если совпадений нет.
	CloseHandle(hProcessSnap);
}