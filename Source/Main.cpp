#include "Game/GameString.h"

#include "SDL2/SDL.h"

int main(int argc, char* argv[])
{
	std::cout << Game::String::Format("Hello World Hash : %d\n", Game::String::GetHash("Hello World"));
	return 0;
}