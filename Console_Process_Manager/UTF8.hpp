#pragma once

#include <string>
#include <windows.h>

std::string WideToUtf8(const std::wstring& text);
std::wstring Utf8ToWide(const std::string& text);