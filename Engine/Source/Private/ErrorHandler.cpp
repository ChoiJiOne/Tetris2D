#include "ErrorHandler.h"
#include "CommandLineManager.h"
#include "Text.hpp"

std::string ErrorHandler::LastErrorMessage_;
std::string ErrorHandler::ErrorFileName_;
int32_t ErrorHandler::ErrorLine_;

LONG ErrorHandler::GenerateCrashDump(EXCEPTION_POINTERS* ExceptionInfo)
{
	SYSTEMTIME CurrentSystemTime;
	GetLocalTime(&CurrentSystemTime);

	std::string CrashDumpFile = Format(
		"%s%d-%d-%d-%d-%d-%d.dmp",
		CommandLineManager::Get().GetValue("-Dump").c_str(),
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
#if defined(SHIPPING) // Shipping 모드 시 소스 코드에 대한 정보 유출 방지
	std::string ShowErrorMessage = Format(
		"MESSAGE: %s",
		LastErrorMessage_.c_str()
	);
#else
	std::string ShowErrorMessage = Format(
		"FILE: %s\nLINE: %d\nMESSAGE: %s",
		ErrorFileName_.c_str(),
		ErrorLine_,
		LastErrorMessage_.c_str()
	);
#endif

	int32_t Successed = MessageBoxA(nullptr, ShowErrorMessage.c_str(), "Error Message", MB_OK);
	if (!Successed)
	{
#if defined(DEBUG) || defined(_DEBUG)
		OutputDebugStringA("failed to show message box");
#endif
	}
}