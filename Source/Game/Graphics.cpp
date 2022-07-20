// @third party code
#include <glad/glad.h>
#include <glfw/glfw3.h>
// @third party code

#include "Graphics.h"

Game::Graphics::~Graphics()
{
}

void Game::Graphics::Initialize()
{
}

void Game::Graphics::BeginFrame(const LinearColor& InColor)
{
	glClearColor(InColor.r, InColor.g, InColor.b, InColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::Graphics::EndFrame()
{
	GLFWwindow* CurrentContext = glfwGetCurrentContext();
	glfwSwapBuffers(CurrentContext);
}
