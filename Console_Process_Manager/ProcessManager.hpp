#pragma once 

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <iomanip>
#include <string>

void ListProcesses();
void FindProcesses(const std::wstring& searchName);