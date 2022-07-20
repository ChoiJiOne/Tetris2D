// @third party code
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// @third party code

#include "Game/Macro.h"
#include "Tetris2D.h"

Tetris2D::~Tetris2D()
{
	if (Window)
	{
		glfwDestroyWindow(Window);
		Window = nullptr;
	}

	glfwTerminate();
}

void Tetris2D::Initialize()
{
	CHECK((glfwInit() == GLFW_TRUE), "failed to initialize glfw");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	Window = glfwCreateWindow(WindowWidth, WindowHeight, "Tetris2D", nullptr, nullptr);
	CHECK((Window != nullptr), "failed to create glfw window");

	glfwMakeContextCurrent(Window);

	CHECK(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "failed to initialize glad");

	Graphics.Initialize();
}

void Tetris2D::Run()
{
	Timer.Reset();

	while (!glfwWindowShouldClose(Window))
	{
		Timer.Tick();

		ProcessInput();
		Update();
		Draw();
	}
}

void Tetris2D::ProcessInput()
{
	glfwPollEvents();

	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, true);
	}
}

void Tetris2D::Update()
{
}

void Tetris2D::Draw()
{
	Graphics.BeginFrame(Game::Color::Blue);


	Graphics.EndFrame();
}
