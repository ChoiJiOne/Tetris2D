#include <Windows.h>
#include <iostream>

#include "Logging.h"

void Game::Logging::ClearConsole()
{
	system("cls");
}

void Game::Logging::Message(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
	std::cout << "[MESSAGE]\n" << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::Logging::Success(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightGreen);
	std::cout << "[SUCCESS]\n" << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::Logging::Warning(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightYellow);
	std::cout << "[WARNING]\n" << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::Logging::Error(const std::string& InMessage)
{
	SetConsoleTextColor(EConsoleTextColor::LightRed);
	std::cout << "[ERROR]\n" << InMessage << '\n';
	SetConsoleTextColor(EConsoleTextColor::BrightWhite);
}

void Game::Logging::SetConsoleTextColor(EConsoleTextColor InTextColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(InTextColor));
}

void Game::Logging::SetConsoleCursorVisible(bool bIsVisible)
{
	CONSOLE_CURSOR_INFO CursorInfo = { 0 };

	CursorInfo.dwSize = 1;
	CursorInfo.bVisible = bIsVisible ? TRUE : FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}