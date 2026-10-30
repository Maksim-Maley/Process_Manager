# Windows Process Manager

[English](#english) | [Русский](#русский)

<a id="english"></a>
## English

A Windows console application written in C++20 for viewing running processes and searching for processes by executable-name substring or process ID (PID). The project uses the Windows Tool Help API and separates UTF-8 conversion utilities into a dedicated module.

## Features

- Interactive command loop: execute several commands without restarting the application.
- Display a process list with:
  - Process ID (PID)
  - Executable name
  - Number of threads
  - Parent process ID
  - Base priority
- Search executable names by substring, case-insensitively.
- Search for a process by PID when the query contains only decimal digits.
- UTF-8 console input and output using the Windows console code page.
- Convert between UTF-8 strings and Windows wide strings for console output and Windows API calls.
- Display command help and report unknown commands.
- Report Windows API error codes when snapshot creation or process enumeration fails.
- Close process snapshot handles after enumeration.

## Commands

| Command | Description | Example |
|---|---|---|
| `list` | Display the running process list. | `list` |
| `find <name>` | Find processes whose executable names contain the specified text, case-insensitively. | `find note` |
| `find <PID>` | Find a process by its numeric process ID. | `find 1234` |
| `help` | Display available commands. | `help` |
| `exit` | Exit the application. | `exit` |

Examples:
- `find notepad.exe` searches for executable names containing `notepad.exe`.
- `find note` can match an executable such as `notepad.exe`.
- `find 1234` is interpreted as a PID search, not as a name search.

The command parser reads the command and one whitespace-separated argument. Search terms containing spaces are not currently supported as a single argument.

## Technology

- C++20
- Windows API / Tool Help API: `CreateToolhelp32Snapshot`, `Process32FirstW`, and `Process32NextW`
- Windows console code-page functions: `SetConsoleOutputCP` and `SetConsoleCP`
- Win32 UTF-8 conversion functions: `MultiByteToWideChar` and `WideCharToMultiByte`
- Standard C++ streams, strings, and algorithms
- Visual Studio project format (`.vcxproj`)

## Requirements

- Windows
- Visual Studio with the **Desktop development with C++** workload and a compatible C++ toolset
- C++20 support

## Build and run

1. Clone or download this repository.
2. Open `Console_Process_Manager.slnx` in a compatible version of Visual Studio.
3. Select a configuration such as **Debug | x64**.
4. Build the solution and run the console application.
5. Enter `help` to display the available commands.

The Visual Studio project currently declares Debug and Release configurations for Win32 and x64 and uses the C++20 language standard. Build and runtime tests have not been independently verified as part of this README update.

## Project structure

```text
Process_Manager/
├── Console_Process_Manager.slnx
├── README.md
└── Console_Process_Manager/
    ├── Console_Process_Manager.cpp
    ├── ProcessManager.cpp
    ├── ProcessManager.hpp
    ├── UTF8.cpp
    ├── UTF8.hpp
    ├── Console_Process_Manager.vcxproj
    └── Console_Process_Manager.vcxproj.filters
```

### Source files

- **`Console_Process_Manager.cpp`** — application entry point, console code-page setup, command input loop, parsing, and command dispatch.
- **`ProcessManager.hpp`** — declarations for process listing and searching; includes the UTF-8 utility declarations through `UTF8.hpp`.
- **`ProcessManager.cpp`** — process snapshot creation, enumeration, process-list output, PID/name matching, and Windows API error reporting.
- **`UTF8.hpp`** — declarations of `Utf8ToWide` and `WideToUtf8`.
- **`UTF8.cpp`** — implementation of UTF-8 / wide-string conversion using the Windows conversion APIs.
- **`Console_Process_Manager.vcxproj`** — Visual Studio build configuration and source-file registration.
- **`Console_Process_Manager.vcxproj.filters`** — source and header grouping in Solution Explorer.

## Current limitations

- The parser accepts one whitespace-separated argument; search terms containing spaces are not supported.
- Numeric-only search input is always treated as a PID. A process name consisting only of digits therefore cannot be searched as a name.
- UTF-8 conversion helpers return an empty string when conversion fails; they do not currently expose a detailed conversion error.
- The application lists and searches processes only. Suspending or terminating processes, changing priority, sorting, and live CPU or memory monitoring are not implemented.
- Build and runtime tests have not been confirmed as part of this README update.

## Purpose

This project is a learning exercise in C++, Windows process enumeration, command parsing, console encoding, UTF-8 conversion, and separating functionality into source and header files.

---

<a id="русский"></a>
## Русский

Консольное приложение для Windows на C++20, предназначенное для просмотра запущенных процессов и поиска по части имени исполняемого файла или по идентификатору процесса (PID). Проект использует Windows Tool Help API, а функции преобразования UTF-8 вынесены в отдельный модуль.

## Возможности

- Интерактивный цикл команд: выполнение нескольких команд без перезапуска приложения.
- Вывод списка процессов со следующими данными:
  - Идентификатор процесса (PID)
  - Имя исполняемого файла
  - Количество потоков
  - PID родительского процесса
  - Базовый приоритет
- Поиск по части имени исполняемого файла без учёта регистра.
- Поиск по PID, если запрос состоит только из десятичных цифр.
- Настройка кодовой страницы консоли для UTF-8 при вводе и выводе.
- Преобразование строк между UTF-8 и широким форматом Windows для работы с консолью и Windows API.
- Вывод справки и сообщение о неизвестной команде.
- Вывод кодов ошибок Windows API при проблемах с созданием снимка или перечислением процессов.
- Закрытие дескрипторов снимка процессов после перечисления.

## Команды

| Команда | Описание | Пример |
|---|---|---|
| `list` | Вывести список запущенных процессов. | `list` |
| `find <name>` | Найти процессы, в имени которых содержится указанная строка, без учёта регистра. | `find note` |
| `find <PID>` | Найти процесс по числовому идентификатору. | `find 1234` |
| `help` | Показать доступные команды. | `help` |
| `exit` | Завершить работу приложения. | `exit` |

Примеры:
- `find notepad.exe` ищет имена исполняемых файлов, содержащие `notepad.exe`.
- `find note` может найти процесс с именем `notepad.exe`.
- `find 1234` воспринимается как поиск по PID, а не как поиск по имени.

Парсер считывает команду и один аргумент, разделённые пробельными символами. Поисковые запросы, содержащие пробелы, пока не поддерживаются как единый аргумент.

## Технологии

- C++20
- Windows API / Tool Help API: `CreateToolhelp32Snapshot`, `Process32FirstW` и `Process32NextW`
- Функции настройки кодовой страницы консоли: `SetConsoleOutputCP` и `SetConsoleCP`
- Функции преобразования строк Windows: `MultiByteToWideChar` и `WideCharToMultiByte`
- Стандартные потоки, строки и алгоритмы C++
- Формат проекта Visual Studio (`.vcxproj`)

## Требования

- Windows
- Visual Studio с рабочей нагрузкой **Разработка классических приложений на C++** и совместимым инструментарием C++
- Поддержка C++20

## Сборка и запуск

1. Клонируйте репозиторий или скачайте его архив.
2. Откройте `Console_Process_Manager.slnx` в совместимой версии Visual Studio.
3. Выберите конфигурацию, например **Debug | x64**.
4. Соберите решение и запустите консольное приложение.
5. Введите `help`, чтобы увидеть список доступных команд.

В проекте Visual Studio объявлены конфигурации Debug и Release для Win32 и x64. Используется стандарт C++20. Сборка и тестирование во время обновления README отдельно не подтверждались.

## Структура проекта

```text
Process_Manager/
├── Console_Process_Manager.slnx
├── README.md
└── Console_Process_Manager/
    ├── Console_Process_Manager.cpp
    ├── ProcessManager.cpp
    ├── ProcessManager.hpp
    ├── UTF8.cpp
    ├── UTF8.hpp
    ├── Console_Process_Manager.vcxproj
    └── Console_Process_Manager.vcxproj.filters
```

### Исходные файлы

- **`Console_Process_Manager.cpp`** — точка входа, настройка кодовой страницы консоли, цикл ввода, разбор команд и вызов нужных функций.
- **`ProcessManager.hpp`** — объявления функций вывода списка процессов и поиска; подключает объявления UTF-8-преобразований через `UTF8.hpp`.
- **`ProcessManager.cpp`** — создание снимка процессов, перечисление, вывод списка, поиск по имени/PID и обработка ошибок Windows API.
- **`UTF8.hpp`** — объявления функций `Utf8ToWide` и `WideToUtf8`.
- **`UTF8.cpp`** — реализация преобразования UTF-8 и широких строк с помощью функций Windows API.
- **`Console_Process_Manager.vcxproj`** — настройки сборки Visual Studio и регистрация исходных файлов.
- **`Console_Process_Manager.vcxproj.filters`** — группировка исходных файлов и заголовков в обозревателе решений.

## Текущие ограничения

- Парсер принимает один аргумент, разделённый пробелами; запросы с пробелами пока не поддерживаются.
- Любой запрос, состоящий только из цифр, трактуется как PID. Поэтому имя процесса, состоящее только из цифр, нельзя искать как имя.
- Функции преобразования UTF-8 возвращают пустую строку при ошибке, но пока не предоставляют подробную информацию о причине сбоя.
- Приложение только перечисляет и ищет процессы. Приостановка или завершение процессов, изменение приоритета, сортировка и мониторинг CPU или памяти пока не реализованы.
- Сборка и тестирование во время обновления README не подтверждались.

## Цель проекта

Учебный проект для практики C++, перечисления процессов Windows, разбора команд, работы с кодировкой консоли, преобразования UTF-8 и разделения функциональности по исходным файлам и заголовкам.
