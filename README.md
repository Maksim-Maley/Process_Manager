# Windows Process Manager

[English](#english) | [Русский](#русский)

<a id="english"></a>
## English

A small interactive Windows console application written in C++20. It lists running processes and searches for processes by executable-name substring or PID using the Windows Tool Help API.

## Features

- Interactive command loop: run multiple commands without restarting the application.
- List running processes with PID, executable name, thread count, parent PID, and base priority.
- Search executable names by substring, case-insensitively.
- Search by PID when the argument consists only of digits.
- Display command help and report unknown commands.
- Report Windows API error codes when snapshot creation or process enumeration fails.
- Close process snapshot handles after enumeration.

## Commands

| Command | Description | Example |
|---|---|---|
| `list` | Display the process list and its available fields. | `list` |
| `find <name>` | Search for executable names containing the supplied text, case-insensitively. | `find note` |
| `find <PID>` | Search for a process with the specified numeric process ID. | `find 1234` |
| `help` | Display the available commands. | `help` |
| `exit` | Exit the application. | `exit` |

Examples:
- `find notepad.exe` searches for names containing `notepad.exe`.
- `find note` can match an executable name such as `notepad.exe`.
- `find 1234` treats the argument as a PID, not as a name fragment.

The parser reads the command and one whitespace-separated argument. Names containing spaces are therefore not supported as a single search argument.

## Technology

- C++20
- Windows Tool Help API: `CreateToolhelp32Snapshot`, `Process32FirstW`, and `Process32NextW`
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
5. Enter `help` to see the available commands.

The repository configuration targets C++20. The build and runtime behavior have not been independently verified as part of this README update.

## Project structure

```text
Process_Manager/
├── Console_Process_Manager.slnx
├── README.md
└── Console_Process_Manager/
    ├── Console_Process_Manager.cpp
    ├── ProcessManager.hpp
    ├── ProcessManager.cpp
    ├── Console_Process_Manager.vcxproj
    └── Console_Process_Manager.vcxproj.filters
```

### Source files

- **`Console_Process_Manager.cpp`** — program entry point, input loop, command parsing, UTF-8-to-wide-string conversion, and command dispatch.
- **`ProcessManager.hpp`** — declarations for process listing and searching.
- **`ProcessManager.cpp`** — process snapshot creation, enumeration, output, name/PID matching, and Windows API error reporting.
- **`Console_Process_Manager.vcxproj`** — Visual Studio build configuration.
- **`Console_Process_Manager.vcxproj.filters`** — groups source and header files in Solution Explorer.

## Current limitations

- The parser accepts one whitespace-separated argument; executable names containing spaces are not supported.
- Console Unicode behavior can depend on the console environment and stream configuration.
- The program lists and searches processes only. Terminating or suspending processes, changing priority, sorting, and displaying live CPU or memory usage are not implemented.
- Build and runtime tests have not been confirmed as part of this README update.

## Purpose

This project is a learning exercise in C++, Windows process enumeration, basic command parsing, and separating declarations from implementations across source files.

---

<a id="русский"></a>
## Русский

Небольшое интерактивное консольное приложение на C++20 для Windows. Оно выводит список запущенных процессов и позволяет искать процессы по части имени исполняемого файла или по PID с помощью Windows Tool Help API.

## Возможности

- Интерактивный цикл команд: можно выполнять несколько команд без перезапуска приложения.
- Вывод списка процессов: PID, имя исполняемого файла, количество потоков, PID родительского процесса и базовый приоритет.
- Поиск по части имени исполняемого файла без учёта регистра.
- Поиск по PID, если аргумент состоит только из цифр.
- Вывод справки и сообщение о неизвестной команде.
- Вывод кодов ошибок Windows API при проблемах с созданием снимка или перечислением процессов.
- Закрытие дескрипторов снимка процессов после перечисления.

## Команды

| Команда | Описание | Пример |
|---|---|---|
| `list` | Вывести список процессов и доступные поля. | `list` |
| `find <name>` | Найти процессы, в имени которых содержится указанная строка, без учёта регистра. | `find note` |
| `find <PID>` | Найти процесс с указанным числовым идентификатором. | `find 1234` |
| `help` | Показать список доступных команд. | `help` |
| `exit` | Завершить работу приложения. | `exit` |

Примеры:
- `find notepad.exe` ищет имена, содержащие `notepad.exe`.
- `find note` может найти процесс с именем `notepad.exe`.
- `find 1234` трактует аргумент как PID, а не как часть имени.

Парсер считывает команду и один аргумент, разделённые пробельными символами. Поэтому имена, содержащие пробелы, нельзя передать как единый аргумент поиска.

## Технологии

- C++20
- Windows Tool Help API: `CreateToolhelp32Snapshot`, `Process32FirstW` и `Process32NextW`
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
5. Введите `help`, чтобы увидеть доступные команды.

В настройках проекта используется стандарт C++20. Сборка и запуск не проверялись отдельно в рамках этого обновления README.

## Структура проекта

```text
Process_Manager/
├── Console_Process_Manager.slnx
├── README.md
└── Console_Process_Manager/
    ├── Console_Process_Manager.cpp
    ├── ProcessManager.hpp
    ├── ProcessManager.cpp
    ├── Console_Process_Manager.vcxproj
    └── Console_Process_Manager.vcxproj.filters
```

### Исходные файлы

- **`Console_Process_Manager.cpp`** — точка входа, цикл ввода, разбор команд, преобразование UTF-8 в широкую строку и вызов нужной команды.
- **`ProcessManager.hpp`** — объявления функций вывода списка процессов и поиска.
- **`ProcessManager.cpp`** — создание снимка процессов, перечисление, вывод информации, поиск по имени/PID и обработка ошибок Windows API.
- **`Console_Process_Manager.vcxproj`** — настройки сборки Visual Studio.
- **`Console_Process_Manager.vcxproj.filters`** — группировка исходных файлов и заголовков в обозревателе решений.

## Текущие ограничения

- Парсер принимает один аргумент, разделённый пробелами; имена исполняемых файлов с пробелами не поддерживаются.
- Корректность Unicode-ввода и вывода может зависеть от среды консоли и настройки потоков.
- Программа только перечисляет и ищет процессы. Приостановка или завершение процессов, изменение приоритета, сортировка и отображение текущей загрузки CPU или использования памяти пока не реализованы.
- Сборка и тестирование во время обновления README не подтверждались.

## Цель проекта

Учебный проект для практики C++, перечисления процессов Windows, базового разбора команд и разделения объявлений и реализаций по нескольким файлам.
