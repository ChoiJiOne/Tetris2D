#pragma once

#include <string>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include <glm/glm.hpp>


/**
 * GLSL 셰이더 클래스입니다.
 */
class Shader
{
public:
	/**
	 * 셰이더 타입입니다.
	 */
	enum class EType
	{
		Vertex   = 0,
		Fragment = 1
	};

public:
	/**
	 * GLSL 셰이더 클래스의 생성자입니다.
	 * @note GLSL 셰이더 클래스를 초기화하기 위해서는 Initialize 메서드를 호출해야 합니다.
	 */
	Shader() = default;


	/**
	 * GLSL 셰이더 클래스의 가상 소멸자입니다.
	 */
	virtual ~Shader();


	/**
	 * 복사 생성자는 명시적으로 사용할 수 없도록 삭제합니다.
	 */
	Shader(Shader&& InInstance) = delete;
	Shader(const Shader& InInstance) = delete;


	/**
	 * 대입 연산자는 명시적으로 사용할 수 없도록 삭제합니다.
	 */
	Shader& operator=(Shader&& InInstance) = delete;
	Shader& operator=(const Shader& InInstance) = delete;


	/**
	 * GLSL 셰이더를 초기화합니다.
	 * 
	 * @param InVertexShaderPath - 버텍스 셰이더의 경로입니다.
	 * @param InFragmentShaderPath - 프레그먼트 셰이더의 경로입니다.
	 * 
	 * @return 초기화에 성공할 경우 true, 실패할 경우 false를 반환합니다.
	 */
	bool Initialize(const std::string& InVertexShaderPath, const std::string& InFragmentShaderPath);


	/**
	 * 셰이더를 렌더링 파이프라인에 바인딩합니다.
	 */
	void Bind();


	/**
	 * 셰이더를 렌더링 파이프라인에 바인딩 취소합니다.
	 */
	void Unbind();


	/**
	 * 셰이더의 bool 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InValue - 설정할 유니폼 버퍼의 값입니다. 
	 */
	void SetBool(const std::string& InName, bool InValue) const
	{
		glUniform1i(glGetUniformLocation(ProgramID, InName.c_str()), static_cast<int32_t>(InValue));
	}


	/**
	 * 셰이더의 int 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InValue - 설정할 유니폼 버퍼의 값입니다. 
	 */
	void SetInt(const std::string& InName, int32_t InValue) const
	{
		glUniform1i(glGetUniformLocation(ProgramID, InName.c_str()), InValue);
	}


	/**
	 * 셰이더의 float 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InValue - 설정할 유니폼 버퍼의 값입니다. 
	 */
	void SetFloat(const std::string& InName, float InValue) const
	{
		glUniform1f(glGetUniformLocation(ProgramID, InName.c_str()), InValue);
	}


	/**
	 * 셰이더의 vec2 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InValue - 설정할 유니폼 버퍼의 값입니다. 
	 */
	void SetVec2(const std::string& InName, const glm::vec2& InValue) const
	{
		glUniform2fv(glGetUniformLocation(ProgramID, InName.c_str()), 1, &InValue[0]);
	}


	/**
	 * 셰이더의 vec2 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param x - 설정할 유니폼 버퍼의 x값입니다. 
	 * @param y - 설정할 유니폼 버퍼의 y값입니다. 
	 */
	void SetVec2(const std::string& InName, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ProgramID, InName.c_str()), x, y);
	}


	/**
	 * 셰이더의 vec3 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InValue - 설정할 유니폼 버퍼의 값입니다. 
	 */
	void SetVec3(const std::string& InName, const glm::vec3& InValue) const
	{
		glUniform3fv(glGetUniformLocation(ProgramID, InName.c_str()), 1, &InValue[0]);
	}


	/**
	 * 셰이더의 vec3 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param x - 설정할 유니폼 버퍼의 x값입니다. 
	 * @param y - 설정할 유니폼 버퍼의 y값입니다.
	 * @param z - 설정할 유니폼 버퍼의 z값입니다. 
	 */
	void SetVec3(const std::string& InName, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ProgramID, InName.c_str()), x, y, z);
	}


	/**
	 * 셰이더의 vec4 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InValue - 설정할 유니폼 버퍼의 값입니다. 
	 */
	void SetVec4(const std::string& InName, const glm::vec4& InValue) const
	{
		glUniform4fv(glGetUniformLocation(ProgramID, InName.c_str()), 1, &InValue[0]);
	}


	/**
	 * 셰이더의 vec4 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param x - 설정할 유니폼 버퍼의 x값입니다. 
	 * @param y - 설정할 유니폼 버퍼의 y값입니다. 
	 * @param z - 설정할 유니폼 버퍼의 z값입니다. 
	 * @param w - 설정할 유니폼 버퍼의 w값입니다. 
	 */
	void SetVec4(const std::string& InName, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(ProgramID, InName.c_str()), x, y, z, w);
	}


	/**
	 * 셰이더의 mat2 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InMatrix - 설정할 유니폼 버퍼의 값입니다.
	 */
	void SetMat2(const std::string& InName, const glm::mat2& InMatrix) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ProgramID, InName.c_str()), 1, GL_FALSE, &InMatrix[0][0]);
	}


	/**
	 * 셰이더의 mat3 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InMatrix - 설정할 유니폼 버퍼의 값입니다.
	 */
	void SetMat3(const std::string& InName, const glm::mat3& InMatrix) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ProgramID, InName.c_str()), 1, GL_FALSE, &InMatrix[0][0]);
	}


	/**
	 * 셰이더의 mat4 타입의 uniform 버퍼를 설정합니다.
	 * 
	 * @param InName - 유니폼 버퍼의 이름입니다.
	 * @param InMatrix - 설정할 유니폼 버퍼의 값입니다.
	 */
	void SetMat4(const std::string& InName, const glm::mat4& InMatrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ProgramID, InName.c_str()), 1, GL_FALSE, &InMatrix[0][0]);
	}


private:
	/**
	 * GLSL 셰이더 파일을 불러옵니다.
	 * 
	 * @param InPath - 불러올 GLSL 셰이더 파일의 경로입니다.
	 * @param OutShaderSource - GLSL 셰이더 파일의 소스 문자열입니다.
	 * @return - GLSL 셰이더 파일 로딩의 성공 여부를 반환합니다.
	 */
	bool LoadShaderFile(const std::string& InPath, std::string& OutShaderSource);


	/**
	 * 셰이더를 생성합니다.
	 * 
	 * @param InShaderSource - 셰이더 소스입니다.
	 * @param InShaderType - 셰이더 타입입니다.
	 * @param OutShaderID - 생성된 셰이더의 아이디입니다.
	 * @return - GLSL 셰이더 생성 성공 여부를 반환합니다.
	 */
	bool CreateShader(const std::string& InShaderSource, const EType& InShaderType, int32_t& OutShaderID);


private:
	// GLSL 셰이더 프로그램 ID입니다.
	uint32_t ProgramID = 0;
};