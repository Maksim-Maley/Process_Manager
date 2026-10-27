#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream> 

void ListProcesses()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 process;
	process.dwSize = sizeof(PROCESSENTRY32);

	std::cout << "PID | NAME | THREADS | PARENT PID | BASE PRIORITY" << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "CreateToolhelp32Snapshot failed. Error code: "
			<< errorCode << '\n';
		return ;
	}

	if (!Process32First(hProcessSnap, &process))
	{
		DWORD errorCode = GetLastError();
		std::cerr << "Process32First failed. Error code: "
			<< errorCode << '\n';
		CloseHandle(hProcessSnap);
		return ;
	}
	do
	{
		std::wcout << std::setw(5)
			<< process.th32ProcessID << " | " //PID
			<< std::setw(40)
			<< process.szExeFile << " | " //Name process
			<< std::setw(3)
			<< process.cntThreads << " | " //Количество потоков выполнения, запущенных процессом.
			<< std::setw(6)
			<< process.th32ParentProcessID << " | " //Идентификатор процесса, создавшего этот процесс
			<< std::setw(3)
			<< process.pcPriClassBase << " | "; //Базовый приоритет всех потоков, созданных в ходе этого процесса.

		std::cout << "\n";

	} while (Process32Next(hProcessSnap, &process));
	DWORD errorCode = GetLastError();

	if (errorCode != ERROR_NO_MORE_FILES)
	{
		std::cerr << "Process32Next failed. Error code: "
			<< errorCode << '\n';
	}
	CloseHandle(hProcessSnap);
}

void FindProcesses(const std::wstring& searchName)
{
	if (searchName.empty())
	{
		std::cout << "Укажите процесс\n";
		return;
	}

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS,
		0
	);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		DWORD errorCode = GetLastError();

		std::cout << "Не удалось получить список процессов. Код ошибки: "
			<< errorCode << '\n';
		return;
	}

	PROCESSENTRY32W process{};
	process.dwSize = sizeof(process);

	bool found = false;

	if (Process32FirstW(hProcessSnap, &process))
	{
		do
		{
			if (CompareStringOrdinal(
				process.szExeFile,
				-1,
				searchName.c_str(),
				-1,
				TRUE) == CSTR_EQUAL)
			{
				std::wcout
					<< L"PID: " << process.th32ProcessID
					<< L"\tИмя: " << process.szExeFile
					<< L'\n';

				found = true;
			}

		} while (Process32NextW(hProcessSnap, &process));
	}
	else
	{
		DWORD errorCode = GetLastError();

		std::cout << "Не удалось прочитать список процессов. Код ошибки: "
			<< errorCode << '\n';
	}

	CloseHandle(hProcessSnap);

	if (!found)
	{
		std::wcout << L"Процесс не найден\n";
	}
}

std::wstring Utf8ToWide(const std::string& text)
{
	if (text.empty())
		return {};

	int size = MultiByteToWideChar(
		CP_UTF8, 0, text.c_str(), -1,
		nullptr, 0
	);

	if (size == 0)
		return {};

	std::wstring result(size, L'\0');

	if (MultiByteToWideChar(
		CP_UTF8, 0, text.c_str(), -1,
		result.data(), size) == 0)
	{
		return {};
	}

	result.pop_back(); // Убираем завершающий L'\0'
	return result;
}

int main()
{
	setlocale(LC_ALL, "RU");

	while (true)
	{
		std::cout << "> ";

		std::string input;
		if (!std::getline(std::cin, input))
			break;

		std::stringstream ss(input);
		std::string command, argument;

		ss >> command;
		ss >> argument;

		if (command == "exit")
			break;

		if (command == "list")
		{
			ListProcesses();
		}

		else if (command == "find")
		{
			if (argument.empty())
			{
				std::cout << "Укажите процесс" << std::endl;
			}
			else
			{
				FindProcesses(Utf8ToWide(argument));
			}
		}

		else if (command == "help")
		{
			std::cout << "list - show processes\n";
			std::cout << "find <name> - search for a process\n";
			std::cout << "help - show available commands\n";
			std::cout << "exit - close the program\n";
		}
		else
			std::cout << "Неизвестная команда. Введите help для списка команд. \n" ;
	}

}
