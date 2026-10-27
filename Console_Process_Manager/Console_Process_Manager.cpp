#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <iomanip>
#include <sstream> 

int main()
{
	setlocale(LC_ALL, "RU");

	HANDLE hProcessSnap;
	//HANDLE hProcess;
	PROCESSENTRY32 process;
	//DWORD dwPriorityClass;

	DWORD errorCode = GetLastError();

	while (true)
	{
		std::cout << "> ";

		std::string input;
		std::getline(std::cin, input);

		std::stringstream ss(input);
		std::string command, argument;

		ss >> command;
		ss >> argument;

		if (input == "exit")
			break;

		if (command == "list")
		{
			std::cout << "PID | NAME | THREADS | PARENT PID | BASE PRIORITY" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;

			hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE)
			{
				std::cerr << "CreateToolhelp32Snapshot failed. Error code: "
					<< errorCode << '\n';
				return 1;
			}

			process.dwSize = sizeof(PROCESSENTRY32);

			if (!Process32First(hProcessSnap, &process))
			{
				std::cout << "Process32First";
				CloseHandle(hProcessSnap);
				std::cerr << "Process32First failed. Error code: "
					<< errorCode << '\n';
				return 1;
			}
			do
			{
				std::cout << std::setw(5)
					<< process.th32ProcessID << " | "; //PID
				std::wcout << std::setw(40)
					<< process.szExeFile << " | "; //Name process
				std::cout << std::setw(3)
					<< process.cntThreads << " | " //Количество потоков выполнения, запущенных процессом.
					<< std::setw(6)
					<< process.th32ParentProcessID << " | " //Идентификатор процесса, создавшего этот процесс
					<< std::setw(3)
					<< process.pcPriClassBase << " | "; //Базовый приоритет всех потоков, созданных в ходе этого процесса.

				std::cout << "\n";

				//if (dwPriorityClass)
					//std::cout << "\n  Priority class    = %d" << dwPriorityClass;

			} while (Process32Next(hProcessSnap, &process));

		}
		else if (command == "find")
		{
			if (argument.empty())
			{
				std::cout << "Укажите процесс" << std::endl;
			}
			else
			{

			}
		}
		else
			std::cout << "Неизвестная команда. Введите help для списка команд. \n" ;
	}

}
