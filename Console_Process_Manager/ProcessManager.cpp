#include "ProcessManager.hpp"

void ListProcesses()
{
	std::wcout << std::left;
	std::wcout << std::setw(5)
		<< "PID" << L" | "
		<< std::setw(40)
		<< "NAME" << L" | "
		<< std::setw(3)
		<< "THREADS" << L" | "
		<< std::setw(6)
		<< "PARENT PID" << L" | "
		<< std::setw(3)
		<< "BASE PRIORITY" << L" |\n";
	std::wcout << "--------------------------------------------------" << std::endl;

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "CreateToolhelp32Snapshot failed. Error code: "
			<< errorCode << '\n';
		return;
	}

	PROCESSENTRY32 process;
	process.dwSize = sizeof(process);

	BOOL result = Process32First(hProcessSnap, &process);

	if (!result)
	{
		DWORD errorCode = GetLastError();

		std::cerr << "Process32First failed. Error code: "
			<< errorCode << '\n';

		CloseHandle(hProcessSnap);
		return;
	}

	do
	{
		std::wcout << std::left;
		std::wcout << std::setw(5)
			<< process.th32ProcessID << L" | "
			<< std::setw(40)
			<< process.szExeFile << L" | "
			<< std::setw(3)
			<< process.cntThreads << L" | "
			<< std::setw(6)
			<< process.th32ParentProcessID << L" | "
			<< std::setw(3)
			<< process.pcPriClassBase << L" |\n";

		SetLastError(ERROR_SUCCESS);

		result = Process32Next(hProcessSnap, &process);

	} while (result);

	DWORD errorCode = GetLastError();

	if (errorCode != ERROR_NO_MORE_FILES)
	{
		std::cerr << "Process32Next failed. Error code: "
			<< errorCode << '\n';
	}

	CloseHandle(hProcessSnap);
}

bool ContainsSearchName(const std::wstring& processName, const std::wstring& searchName)
{
	int lengthProcess = static_cast<int>(processName.length());
	int lengthSearch = static_cast<int>(searchName.length());
	
	for (int i = 0; i <= lengthProcess - lengthSearch; ++i)
	{
		
		int result = CompareStringOrdinal(
			processName.c_str() + i,  // начало фрагмента
			lengthSearch,                // длина фрагмента
			searchName.c_str(),       // поисковая строка
			lengthSearch,                // её длина
			TRUE                      
		);

		
		if (result == CSTR_EQUAL)
			return true;
	}

	return false;
}

bool IsNumericQuery(const std::wstring& searchName)
{
	if (searchName.empty())
		return false;
	return std::all_of(searchName.begin(), searchName.end(),
		[](wchar_t ch) { return ch >= L'0' && ch <= L'9'; });
}

bool FindProcessByPid(DWORD targetPid) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) return false;

	PROCESSENTRY32W process;
	process.dwSize = sizeof(process);

	bool found = false;
	if (Process32FirstW(hProcessSnap, &process)) {
		do {
			if (process.th32ProcessID == targetPid) {
				found = true;
				break;
			}
		} while (Process32NextW(hProcessSnap, &process));
	}
	CloseHandle(hProcessSnap);
	return found;
}

void FindProcesses(const std::wstring& searchName)
{
	bool isNumeric = IsNumericQuery(searchName);
	DWORD targetPid = 0;

	if (isNumeric) {
		try {
			unsigned long parsedValue = std::stoul(searchName);
			if (parsedValue > static_cast<unsigned long>((std::numeric_limits<DWORD>::max)())) {
				std::wcout << L"Ошибка: введённый PID превышает допустимый диапазон (DWORD).\n";
				return;
			}
			targetPid = static_cast<DWORD>(parsedValue);
		}
		catch (const std::invalid_argument&) {
			std::wcout << L"Ошибка: неверный формат PID.\n";
			return;
		}
		catch (const std::out_of_range&) {
			std::wcout << L"Ошибка: число слишком велико.\n";
			return;
		}
	}

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "CreateToolhelp32Snapshot failed. Error code: "
			<< errorCode << '\n';
		return;
	}

	PROCESSENTRY32W process;
	process.dwSize = sizeof(process);

	bool found = false;
	BOOL result = Process32FirstW(hProcessSnap, &process);


	if (!result)
	{
		DWORD errorCode = GetLastError();

		std::cerr << "Process32First failed. Error code: "
			<< errorCode << '\n';

		CloseHandle(hProcessSnap);
		return;
	}

	do
	{
		bool match = false;

		// Ветвление логики в зависимости от типа запроса
		if (isNumeric) {
			// Сравниваем числовой PID
			if (process.th32ProcessID == targetPid) {
				match = true;
			}
		}
		else {
			// Ищем подстроку в имени (ваша существующая функция)
			if (ContainsSearchName(process.szExeFile, searchName)) {
				match = true;
			}
		}

		// Если нашли совпадение — выводим и ставим флаг
		if (match) {
			std::wcout << process.th32ProcessID
				<< '\t' << process.szExeFile << L"\n";
			found = true;
		}
		
		SetLastError(ERROR_SUCCESS);
		result = Process32NextW(hProcessSnap, &process);

	} while (result);

	DWORD errorCode = GetLastError();

	if (errorCode != ERROR_NO_MORE_FILES)
	{
		std::cerr << "Process32Next failed. Error code: "
			<< errorCode << '\n';
	}

	else if (!found)
	{
		std::wcout << L"Process not found\n";
	}

	CloseHandle(hProcessSnap);
}