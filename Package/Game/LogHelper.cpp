#include "LogHelper.h"

void Game::LogHelper::ClearConsole()
{
	system("cls");
}

void Game::LogHelper::Message(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
	std::cout << "[MESSAGE] : " << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::LogHelper::Success(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightGreen);
	std::cout << "[SUCCESS] : " << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::LogHelper::Warning(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightYellow);
	std::cout << "[WARNING] : " << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::LogHelper::Error(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightRed);
	std::cout << "[ERROR] : " << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::LogHelper::SetConsoleTextColor(EConsoleTextColor InTextColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(InTextColor));
}

void Game::LogHelper::SetConsoleCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO CursorInfo = { 0 };

	CursorInfo.dwSize = 1;
	CursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}