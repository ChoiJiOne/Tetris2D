#include "Logger.h"

void Logger::ClearConsole()
{
	system("cls");
}

void Logger::Message(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
	std::cout << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Logger::Warning(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightYellow);
	std::cout << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Logger::Error(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightRed);
	std::cout << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Logger::SetConsoleTextColor(EConsoleTextColor InTextColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(InTextColor));
}

void Logger::SetConsoleCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO CursorInfo = { 0 };

	CursorInfo.dwSize = 1;
	CursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
