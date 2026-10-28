#include "ProcessManager.hpp"
#include <sstream> 

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
		std::wcout << "> ";

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
				std::wcout << L"Укажите процесс" << std::endl;
			}
			else
			{
				FindProcesses(Utf8ToWide(argument));
			}
		}

		else if (command == "help")
		{
			std::wcout << "list - show processes\n";
			std::wcout << "find <name> - search for a process\n";
			std::wcout << "help - show available commands\n";
			std::wcout << "exit - close the program\n";
		}
		else
			std::wcout << L"Неизвестная команда. Введите help для списка команд. \n" ;
	}

}
