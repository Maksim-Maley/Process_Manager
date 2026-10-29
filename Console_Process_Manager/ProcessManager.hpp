#pragma once 

#define NOMINMAX
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <stdexcept>


void ListProcesses();
void FindProcesses(const std::wstring& searchName);