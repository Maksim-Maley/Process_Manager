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
	HANDLE hProcess;
	PROCESSENTRY32 process;
	DWORD dwPriorityClass;

	std::cout << ">";

	std::string input;
	std::getline(std::cin, input);

	std::stringstream ss(input);
	std::string command, argument;

	ss >> command;
	ss >> argument;

	if (command == "list")
	{
		std::cout << "PID      NAME" << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			std::cout << "CreateToolhelp32Snapshot (of processes)";
			return(FALSE);
		}

		process.dwSize = sizeof(PROCESSENTRY32);

		if (!Process32First(hProcessSnap, &process))
		{
			std::cout << "Process32First"; 
			CloseHandle(hProcessSnap);          
			return(FALSE);
		}
		do
		{								
			std::cout << std::setw(5)
				<< process.th32ProcessID << "    "; //PID
			_tprintf(process.szExeFile); //Name process
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
		return 0;
}


/*
std::cout << std::setw(3)
				<< process.cntThreads << "    "; //Количество потоков выполнения, запущенных процессом.
			std::cout << std::setw(6)
				<< process.th32ParentProcessID<< "    "; //Идентификатор процесса, создавшего этот процесс
			std::cout << std::setw(3)
				<< process.pcPriClassBase<< "    "; //Базовый приоритет всех потоков, созданных в ходе этого процесса.
*/