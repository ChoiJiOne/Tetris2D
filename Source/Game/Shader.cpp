#include "Shader.h"

Shader::~Shader()
{
	glDeleteProgram(ProgramID);
}

bool Shader::Initialize(const std::string& InVertexShaderPath, const std::string& InFragmentShaderPath)
{
	int32_t VertexShaderID = 0, FragmentShaderID = 0;
	std::string VertexShaderSource, FragmentShaderSource;

	if (!LoadShaderFile(InVertexShaderPath, VertexShaderSource) ||
		!CreateShader(VertexShaderSource, Shader::EType::Vertex, VertexShaderID))
	{
		glDeleteShader(VertexShaderID);
		return false;
	}

	if (!LoadShaderFile(InFragmentShaderPath, FragmentShaderSource) ||
		!CreateShader(FragmentShaderSource, Shader::EType::Fragment, FragmentShaderID))
	{
		glDeleteShader(FragmentShaderID);
		return false;
	}

	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	int32_t IsSuccess;
	char InfoLog[1024];
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &IsSuccess);
	if (!IsSuccess)
	{
		glGetProgramInfoLog(ProgramID, 1024, nullptr, InfoLog);
		std::cout << InfoLog << '\n';
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return (IsSuccess != 0);
}

void Shader::Bind()
{
	glUseProgram(ProgramID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

bool Shader::LoadShaderFile(const std::string& InPath, std::string& OutShaderSource)
{
	std::ifstream ShaderFileStream(InPath);
	std::stringstream ShaderSourceStream;

	if (ShaderFileStream.is_open())
	{
		ShaderSourceStream << ShaderFileStream.rdbuf();
		OutShaderSource = ShaderSourceStream.str();

		ShaderFileStream.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool Shader::CreateShader(const std::string& InShaderSource, const EType& InShaderType, int32_t& OutShaderID)
{
	uint32_t ShaderID;
	GLenum ShaderType;
	const char* ShaderSource = InShaderSource.c_str();

	switch (InShaderType)
	{
	case EType::Vertex:
		ShaderType = GL_VERTEX_SHADER;
		break;

	case EType::Fragment:
		ShaderType = GL_FRAGMENT_SHADER;
		break;

	default:
		return false;
	}

	ShaderID = glCreateShader(ShaderType);
	glShaderSource(ShaderID, 1, &ShaderSource, nullptr);
	glCompileShader(ShaderID);

	int32_t IsSuccess;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &IsSuccess);
	if (!IsSuccess)
	{
		char InfoLog[1024];
		glGetShaderInfoLog(ShaderID, 1024, nullptr, InfoLog);
		std::cout << InfoLog << '\n';
		return false;
	}
	else
	{
		OutShaderID = ShaderID;
		return true;
	}
}