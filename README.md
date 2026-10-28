# Windows Process Manager

[English](#english) | [Русский](#русский)

<a id="english"></a>
## English

A small Windows console application written in C++20 that lists running processes and searches for a process by its executable name using the Windows Tool Help API.

## Features

- Interactive command loop: run multiple commands without restarting the application.
- List running processes with the following fields:
  - Process ID (PID)
  - Executable name
  - Number of threads
  - Parent process ID
  - Base priority
- Search for a process by its full executable name, using a case-insensitive comparison.
- Display command help and report unknown commands.
- Report Windows API error codes when snapshot creation or process enumeration fails.
- Close the process snapshot handle after enumeration.

## Commands

| Command | Description | Example |
|---|---|---|
| `list` | Display the process list and its available fields. | `list` |
| `find <name>` | Search by the full executable name, case-insensitively. | `find notepad.exe` |
| `help` | Display the available commands. | `help` |
| `exit` | Exit the application. | `exit` |

The current search expects a full executable name. For example, `find notepad.exe` can match `notepad.exe`, while `find note` does not perform a partial-name search. The command parser currently reads the command and one whitespace-separated argument.

## Technology

- C++20
- Windows API: Tool Help functions including `CreateToolhelp32Snapshot`, `Process32First`, and `Process32Next`
- Standard C++ streams and string utilities
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

The project configuration targets C++20. The build and runtime behavior have not been independently verified as part of this README update.

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
- **`ProcessManager.hpp`** — declarations for the process-listing and process-search functions.
- **`ProcessManager.cpp`** — process snapshot creation, enumeration, output, search, and Windows API error reporting.
- **`Console_Process_Manager.vcxproj`** — Visual Studio build configuration.
- **`Console_Process_Manager.vcxproj.filters`** — groups source and header files in Solution Explorer.

## Current limitations

- Search supports the full executable name only; partial-name and PID searches are not implemented.
- The command parser accepts one whitespace-separated argument, so more complex arguments are not supported.
- Console Unicode behavior may depend on the console environment and stream configuration; input/output handling can be made more consistent.
- The program lists and searches processes only. Terminating processes, changing priority, sorting, filtering by PID, and displaying live CPU or memory usage are not implemented.
- Build and runtime tests have not been confirmed for this README update.

## Purpose

This project is a learning exercise in C++, Windows process enumeration, basic command parsing, and separating declarations from implementation across multiple source files.

---

<a id="русский"></a>
## Русский

Небольшое консольное приложение на C++20 для Windows. Оно выводит список запущенных процессов и позволяет искать процесс по имени исполняемого файла с помощью Windows Tool Help API.

## Возможности

- Интерактивный цикл команд: можно выполнять несколько команд без перезапуска приложения.
- Вывод списка процессов со следующими полями:
  - Идентификатор процесса (PID)
  - Имя исполняемого файла
  - Количество потоков
  - PID родительского процесса
  - Базовый приоритет
- Поиск процесса по полному имени исполняемого файла без учёта регистра.
- Вывод справки и сообщение о неизвестной команде.
- Вывод кодов ошибок Windows API, если не удалось создать снимок или перечислить процессы.
- Закрытие дескриптора снимка процессов после перечисления.

## Команды

| Команда | Описание | Пример |
|---|---|---|
| `list` | Вывести список процессов и доступные поля. | `list` |
| `find <name>` | Найти процесс по полному имени исполняемого файла без учёта регистра. | `find notepad.exe` |
| `help` | Показать список доступных команд. | `help` |
| `exit` | Завершить работу приложения. | `exit` |

Поиск пока работает только по полному имени исполняемого файла. Например, `find notepad.exe` может найти `notepad.exe`, а `find note` не выполняет поиск по части имени. Парсер сейчас считывает команду и один аргумент, разделённые пробельными символами.

## Технологии

- C++20
- Windows API: функции Tool Help, включая `CreateToolhelp32Snapshot`, `Process32First` и `Process32Next`
- Стандартные потоки и строковые средства C++
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

В настройках проекта используется стандарт C++20. Сборка и работа приложения не проверялись отдельно в рамках обновления этого README.

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
- **`ProcessManager.hpp`** — объявления функций вывода списка процессов и поиска процесса.
- **`ProcessManager.cpp`** — создание снимка процессов, перечисление, вывод информации, поиск и обработка ошибок Windows API.
- **`Console_Process_Manager.vcxproj`** — настройки сборки Visual Studio.
- **`Console_Process_Manager.vcxproj.filters`** — группировка исходных файлов и заголовков в обозревателе решений.

## Текущие ограничения

- Поиск поддерживает только полное имя исполняемого файла; поиск по части имени и по PID пока не реализован.
- Парсер принимает один аргумент, отделённый пробелами, поэтому более сложные аргументы не поддерживаются.
- Корректность Unicode-ввода и вывода может зависеть от среды консоли и настройки потоков; обработку ввода/вывода можно сделать более согласованной.
- Программа только перечисляет и ищет процессы. Завершение процессов, изменение приоритета, сортировка, фильтрация по PID и отображение текущей загрузки CPU или использования памяти не реализованы.
- Сборка и тестирование во время обновления README не подтверждались.

## Цель проекта

Учебный проект для практики C++, перечисления процессов Windows, базового разбора команд и разделения объявлений и реализаций по нескольким файлам.
