# Windows Process Manager

[English](#english) | [Русский](#русский)

<a id="english"></a>
## English

A small Windows console program written in C++ that lists running processes using the Windows Tool Help API.

### Features currently implemented

- Read a command from the console.
- Use `CreateToolhelp32Snapshot` to obtain a process snapshot.
- Enumerate processes with `Process32First` and `Process32Next`.
- Display each process ID (PID) and executable name.

### Technology

- C++20
- Windows API: `CreateToolhelp32Snapshot`, `PROCESSENTRY32`, `Process32First`, and `Process32Next`
- Standard C++ input and string-stream utilities

### Requirements

- Windows
- Visual Studio with the C++ desktop development workload and a compatible toolset
- C++20 support

### Build and run

1. Clone or download this repository.
2. Open `Console_Process_Manager.slnx` in a compatible version of Visual Studio.
3. Select a configuration such as **Debug | x64**.
4. Build the solution and run the console application.

The build has not been independently verified as part of this README preparation.

### Commands

| Command | Description |
|---|---|
| `list` | Enumerate processes and print their PIDs and executable names. |
| `find process_name` | Recognized by the input parser, but process searching is not implemented yet. |

The current program reads a single command each time it starts. Run it again to issue another command.

### Current limitations

- The `find` branch checks whether an argument was supplied, but does not yet search the process list.
- The process snapshot handle is not closed after a successful enumeration in the current implementation.
- Error reporting can be improved by including `GetLastError()` details.
- Process termination, priority changes, and other management operations are not implemented.

### Project structure

```text
Console_Process_Manager/
├── Console_Process_Manager.cpp
└── Console_Process_Manager.vcxproj
```

### Purpose

This project is a practical introduction to enumerating Windows processes with the Tool Help API and presenting system information in a console.

---

<a id="русский"></a>
## Русский

Небольшая консольная программа на C++ для Windows, которая выводит список запущенных процессов с использованием Windows Tool Help API.

### Реализованные возможности

- Чтение команды из консоли.
- Получение снимка процессов через `CreateToolhelp32Snapshot`.
- Перебор процессов с помощью `Process32First` и `Process32Next`.
- Вывод идентификатора процесса (PID) и имени исполняемого файла.

### Технологии

- C++20
- Windows API: `CreateToolhelp32Snapshot`, `PROCESSENTRY32`, `Process32First` и `Process32Next`
- Стандартные средства C++ для ввода и работы со строковыми потоками

### Требования

- Windows
- Visual Studio с компонентом разработки классических приложений на C++ и совместимым toolset
- Поддержка C++20

### Сборка и запуск

1. Клонируйте репозиторий или скачайте архив.
2. Откройте `Console_Process_Manager.slnx` в совместимой версии Visual Studio.
3. Выберите конфигурацию, например **Debug | x64**.
4. Соберите решение и запустите консольное приложение.

Сборка не проверялась отдельно в рамках подготовки этого README.

### Команды

| Команда | Описание |
|---|---|
| `list` | Перечислить процессы и вывести их PID и имена исполняемых файлов. |
| `find process_name` | Команда распознаётся парсером, но поиск процессов пока не реализован. |

Текущая версия читает одну команду при каждом запуске программы. Чтобы выполнить другую команду, запустите её повторно.

### Текущие ограничения

- Ветка `find` проверяет наличие аргумента, но пока не выполняет поиск по списку процессов.
- После успешного перечисления текущая реализация не закрывает дескриптор снимка процессов.
- Обработку ошибок можно улучшить, выводя подробности через `GetLastError()`.
- Завершение процессов, изменение приоритета и другие операции управления не реализованы.

### Структура проекта

```text
Console_Process_Manager/
├── Console_Process_Manager.cpp
└── Console_Process_Manager.vcxproj
```

### Цель проекта

Практическое знакомство с перечислением процессов Windows через Tool Help API и выводом системной информации в консоль.
