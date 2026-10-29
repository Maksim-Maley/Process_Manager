#pragma once

#define NOMINMAX
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

// Выводит список процессов и основные сведения о каждом из них.
void ListProcesses();

// Ищет процессы по части имени без учёта регистра или по числовому PID.
void FindProcesses(const std::wstring& searchName);
