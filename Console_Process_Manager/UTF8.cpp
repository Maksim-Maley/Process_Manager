#include "UTF8.hpp"

std::string WideToUtf8(const std::wstring& text)
{
    if (text.empty())
        return {};

    int size = WideCharToMultiByte(
        CP_UTF8,
        0,
        text.c_str(),
        -1,
        nullptr,
        0,
        nullptr,
        nullptr
    );

    if (size == 0)
        return {};

    std::string result(size, '\0');

    if (WideCharToMultiByte(
        CP_UTF8,
        0,
        text.c_str(),
        -1,
        result.data(),
        size,
        nullptr,
        nullptr
    ) == 0)
    {
        return {};
    }

    result.pop_back();

    return result;
}

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