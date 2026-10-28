#include "ProcessManager.hpp"

void ListProcesses()
{
	std::wcout << "PID | NAME | THREADS | PARENT PID | BASE PRIORITY" << std::endl;
	std::wcout << "--------------------------------------------------" << std::endl;

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "CreateToolhelp32Snapshot failed. Error code: "
			<< errorCode << '\n';
		return;
	}

	PROCESSENTRY32 process;
	process.dwSize = sizeof(process);

	BOOL result = Process32First(hProcessSnap, &process);

	if (!result)
	{
		DWORD errorCode = GetLastError();

		std::cerr << "Process32First failed. Error code: "
			<< errorCode << '\n';

		CloseHandle(hProcessSnap);
		return;
	}

	do
	{
		std::wcout << std::setw(5)
			<< process.th32ProcessID << L" | "
			<< std::setw(40)
			<< process.szExeFile << L" | "
			<< std::setw(3)
			<< process.cntThreads << L" | "
			<< std::setw(6)
			<< process.th32ParentProcessID << L" | "
			<< std::setw(3)
			<< process.pcPriClassBase << L" |\n";

		SetLastError(ERROR_SUCCESS);

		result = Process32Next(hProcessSnap, &process);

	} while (result);

	DWORD errorCode = GetLastError();

	if (errorCode != ERROR_NO_MORE_FILES)
	{
		std::cerr << "Process32Next failed. Error code: "
			<< errorCode << '\n';
	}

	CloseHandle(hProcessSnap);
}

void FindProcesses(const std::wstring& searchName)
{
	if (searchName.empty())
	{
		std::wcout << "Укажите процесс\n";
		return;
	}

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		DWORD errorCode = GetLastError();
		std::cerr << "CreateToolhelp32Snapshot failed. Error code: "
			<< errorCode << '\n';
		return;
	}

	PROCESSENTRY32W process;
	process.dwSize = sizeof(process);

	bool found = false;
	BOOL result = Process32FirstW(hProcessSnap, &process);


	if (!result)
	{
		DWORD errorCode = GetLastError();

		std::cerr << "Process32First failed. Error code: "
			<< errorCode << '\n';

		CloseHandle(hProcessSnap);
		return;
	}

	do
	{
		if (CompareStringOrdinal(
			process.szExeFile,
			-1,
			searchName.c_str(),
			-1,
			TRUE) == CSTR_EQUAL)
		{
			std::wcout
				<< L"PID: " << process.th32ProcessID
				<< L"\tИмя: " << process.szExeFile
				<< L'\n';

			found = true;
		}

		SetLastError(ERROR_SUCCESS);
		result = Process32NextW(hProcessSnap, &process);

	} while (result);

	DWORD errorCode = GetLastError();

	if (errorCode != ERROR_NO_MORE_FILES)
	{
		std::cerr << "Process32Next failed. Error code: "
			<< errorCode << '\n';
	}

	CloseHandle(hProcessSnap);

	if (!found)
	{
		std::wcout << L"Процесс не найден\n";
	}
}