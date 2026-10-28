#pragma once 

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <iomanip>

void ListProcesses();
void FindProcesses(const std::wstring& searchName);