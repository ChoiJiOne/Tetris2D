#include "ErrorHandler.h"
#include "Text.hpp"

std::string ErrorHandler::CrashDumpPath_;
std::string ErrorHandler::LastErrorMessage_;
std::string ErrorHandler::ErrorFileName_;
int32_t ErrorHandler::ErrorLine_;

LONG ErrorHandler::GenerateCrashDump(EXCEPTION_POINTERS* ExceptionInfo)
{
	SYSTEMTIME CurrentSystemTime;
	GetLocalTime(&CurrentSystemTime);

	std::string CrashDumpFile = Format(
		"%s%d-%d-%d-%d-%d-%d.dmp",
		CrashDumpPath_.c_str(),
		CurrentSystemTime.wYear,
		CurrentSystemTime.wMonth,
		CurrentSystemTime.wDay,
		CurrentSystemTime.wHour,
		CurrentSystemTime.wMinute,
		CurrentSystemTime.wSecond
	);

	HANDLE  FileHandle = CreateFileA(
		CrashDumpFile.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (FileHandle != INVALID_HANDLE_VALUE)
	{
		BOOL Successed = TRUE;

		_MINIDUMP_EXCEPTION_INFORMATION Exception;
		Exception.ThreadId = GetCurrentThreadId();
		Exception.ExceptionPointers = ExceptionInfo;
		Exception.ClientPointers = FALSE;

		Successed = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), FileHandle, MiniDumpNormal, &Exception, NULL, NULL);
		if (!Successed)
		{
#if defined(DEBUG) || defined(_DEBUG)
			OutputDebugStringA("failed to generate crash dump file");
#endif
		}

		Successed = CloseHandle(FileHandle);
		if (!Successed)
		{
#if defined(DEBUG) || defined(_DEBUG)
			OutputDebugStringA("failed to close crash dump file");
#endif
		}
	}
	else
	{
#if defined(DEBUG) || defined(_DEBUG)
		OutputDebugStringA("failed to generate crash dump file");
#endif
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

void ErrorHandler::ShowErrorMessageBox()
{
	std::string ShowErrorMessage = Format(
		"FILE: %s\nLINE: %d\nMESSAGE: %s",
		ErrorFileName_.c_str(),
		ErrorLine_,
		LastErrorMessage_.c_str()
	);

	int32_t Successed = MessageBoxA(nullptr, ShowErrorMessage.c_str(), "Error Message", MB_OK);
}
