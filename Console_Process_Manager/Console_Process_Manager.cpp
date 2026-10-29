#include "ProcessManager.hpp"
#include <sstream>

// Преобразует строку UTF-8, полученную от пользователя, в std::wstring,
// которую можно передавать функциям Windows API.
std::wstring Utf8ToWide(const std::string& text)
{
	if (text.empty())
		return {};

	int size = MultiByteToWideChar(
		CP_UTF8, 0, text.c_str(), -1,
		nullptr, 0
	);

	// Нулевой результат означает, что преобразование не удалось.
	if (size == 0)
		return {};

	std::wstring result(size, L'\0');

	if (MultiByteToWideChar(
		CP_UTF8, 0, text.c_str(), -1,
		result.data(), size) == 0)
	{
		return {};
	}

	result.pop_back(); // Убираем завершающий L'\0', добавленный API.
	return result;
}

int main()
{
	setlocale(LC_ALL, "RU");

	// Цикл позволяет вводить команды до тех пор, пока пользователь не введёт exit.
	while (true)
	{
		std::wcout << "> ";

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
				std::wcout << L"Укажите имя процесса или PID." << std::endl;
			}
			else
			{
				// После преобразования тоже проверяем строку: функция конвертации
				// возвращает пустую строку, если преобразование не удалось.
				std::wstring searchName = Utf8ToWide(argument);
				if (searchName.empty())
				{
					std::wcout << L"Не удалось преобразовать аргумент поиска." << std::endl;
				}
				else
				{
					std::wcout << L"PID   | NAME" << std::endl;
					FindProcesses(searchName);
				}
			}
		}
		else if (command == "help")
		{
			std::wcout << L"list - показать список процессов\n";
			std::wcout << L"find <name|PID> - поиск по части имени или PID\n";
			std::wcout << L"help - показать список команд\n";
			std::wcout << L"exit - закрыть программу\n";
		}
		else
		{
			std::wcout << L"Неизвестная команда. Введите help для списка команд.\n";
		}
	}

	return 0;
}
