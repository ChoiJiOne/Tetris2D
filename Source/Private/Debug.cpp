#include "Debug.h"
#include "Text.hpp"
#include "CommandLineManager.h"

#include <windows.h>
#include <string>

void CreateDumpFileFromException(_EXCEPTION_POINTERS* InExceptionInfo)
{
	SYSTEMTIME CurrentSystemTime;
	GetLocalTime(&CurrentSystemTime);

	std::string DumpFile = Format(
		"%s%d-%d-%d-%d-%d-%d.dmp",
		CommandLineManager::Get().GetValue("-Dump").c_str(),
		CurrentSystemTime.wYear,
		CurrentSystemTime.wMonth,
		CurrentSystemTime.wDay,
		CurrentSystemTime.wHour,
		CurrentSystemTime.wMinute,
		CurrentSystemTime.wSecond
	);

	HANDLE  FileHandler = CreateFileA(
		DumpFile.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	_MINIDUMP_EXCEPTION_INFORMATION ExceptionInfo;
	ExceptionInfo.ThreadId = GetCurrentThreadId();
	ExceptionInfo.ExceptionPointers = InExceptionInfo;
	ExceptionInfo.ClientPointers = FALSE;

	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), FileHandler, MiniDumpNormal, &ExceptionInfo, NULL, NULL);
	CloseHandle(FileHandler);
}

LONG __stdcall UnhandledExceptionHandler(_EXCEPTION_POINTERS* ExceptionInfo)
{
	CreateDumpFileFromException(ExceptionInfo);
	return EXCEPTION_CONTINUE_SEARCH;
}