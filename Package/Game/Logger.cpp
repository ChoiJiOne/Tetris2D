#include "Logger.h"

void Game::Logger::ClearConsole()
{
	system("cls");
}

void Game::Logger::Message(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
	std::cout << "[MESSAGE] : " << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::Logger::Success(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightGreen);
	std::cout << "[SUCCESS] : " << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::Logger::Warning(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightYellow);
	std::cout << "[WARNING] : " << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::Logger::Error(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightRed);
	std::cout << "[ERROR] : " << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::Logger::SetConsoleTextColor(EConsoleTextColor InTextColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(InTextColor));
}

void Game::Logger::SetConsoleCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO CursorInfo = { 0 };

	CursorInfo.dwSize = 1;
	CursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}