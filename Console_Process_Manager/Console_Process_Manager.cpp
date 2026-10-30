#include "ProcessManager.hpp"
#include <sstream>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	// Цикл позволяет вводить команды до тех пор, пока пользователь не введёт exit.
	while (true)
	{
		std::cout << "> ";

		std::string input;
		if (!std::getline(std::cin, input))
			break; // Например, если поток ввода закрыт.

		// Разделяем введённую строку на команду и первый аргумент.
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
			// Не вызываем поиск, если пользователь не указал аргумент.
			if (argument.empty())
			{
				std::cout << "Укажите имя процесса или PID." << std::endl;
			}
			else
			{
				// После преобразования тоже проверяем строку: функция конвертации
				// возвращает пустую строку, если преобразование не удалось.
				std::wstring searchName = Utf8ToWide(argument);
				if (searchName.empty())
				{
					std::cout << "Не удалось преобразовать аргумент поиска." << std::endl;
				}
				else
				{
					std::cout << "PID   | NAME" << std::endl;
					FindProcesses(searchName);
				}
			}
		}
		else if (command == "help")
		{
			std::cout << "list - показать список процессов\n";
			std::cout << "find <name|PID> - поиск по части имени или PID\n";
			std::cout << "help - показать список команд\n";
			std::cout << "exit - закрыть программу\n";
		}
		else
		{
			std::cout << "Неизвестная команда. Введите help для списка команд.\n";
		}
	}

	return 0;
}
