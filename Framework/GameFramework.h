#pragma once

// 게임 폰트를 사용하기 위한 헤더 선언을 추가합니다.
#include "GameFont.h"

// 게임 입력 처리를 수행하기 위한 헤더 선언을 추가합니다.
#include "GameInput.h"

// 게임 렌더링을 수행하기 위한 헤더 선언을 추가합니다.
#include "GameRenderer.h"

// 게임 텍스처를 사용하기 위한 헤더 선언을 추가합니다.
#include "GameTexture2D.h"

// 게임 타이머를 사용하기 위한 헤더 선언을 추가합니다.
#include "GameTimer.h"

// 게임 윈도우를 생성 및 관리하기 위한 헤더 선언을 추가합니다.
#include "GameWindow.h"

// Json 파일을 로드하고 사용하기 위한 헤더 선언을 추가합니다.
#include "JsonUtil.h"

// 로그 기능을 사용하기 위한 헤더 선언을 추가합니다.
#include "Logger.h"

// 문자열 기능을 사용하기 위한 헤더 선언을 추가합니다.
#include "StringUtil.h"


// 게임 진행에 필요한 요소들을 관리하는 클래스입니다.
class GameFramework
{
public:
	// 생성자입니다.
	GameFramework() = default;


	// 가상 소멸자입니다.
	virtual ~GameFramework();


	// 게임 프레임워크가 소유하는 윈도우를 반환합니다.
	// 이때, 반환된 윈도우는 변경 가능합니다.
	//
	// @return - 윈도우의 참조자를 반환합니다.
	GameWindow& GetGameWindow() { return Window; }


	// 게임 프레임워크가 소유하는 윈도우를 반환합니다.
	// 이때, 반환된 윈도우는 변경 불가능합니다.
	//
	// @return - 윈도우의 참조자를 반환합니다.
	const GameWindow& GetGameWindow() const { return Window; }


	// 게임 프레임워크가 소유하는 입력 시스템을 반환합니다.
	// 이때, 반환된 입력 시스템은 변경 가능합니다.
	// 
	// @return - 입력 시스템의 참조자를 반환합니다.
	GameInput& GetGameInput() { return Input; }


	// 게임 프레임워크가 소유하는 입력 시스템을 반환합니다.
	// 이때, 반환된 입력 시스템은 변경 불가능합니다.
	// 
	// @return - 입력 시스템의 참조자를 반환합니다.
	const GameInput& GetGameInput() const { return Input; }


	// 게임 프레임워크가 소유하는 렌더러를 반환합니다.
	// 이때, 반환된 렌더러는 변경 가능합니다.
	// 
	// @return - 렌더러의 참조자를 반환합니다.
	GameRenderer& GetGameRenderer() { return Renderer; }


	// 게임 프레임워크가 소유하는 렌더링 시스템을 반환합니다.
	// 이때, 반환된 렌더러는 변경 불가능합니다.
	// 
	// @return - 렌더러의 참조자를 반환합니다.
	const GameRenderer& GetGameRenderer() const { return Renderer; }


	// 게임 실행 파일 경로를 반환합니다.
	// 
	// @return - 게임 실행 파일 경로를 반환합니다.
	const std::string& GetExecuteDirectory() const { return ExecuteDirectory; }


	// 게임 프로젝트의 루트 디렉토리 경로를 반환합니다.
	//
	// @return - 게임 프로젝트의 루트 디렉토리 경로를 반환합니다.
	const std::string& GetProjectRootDirectory() const {return ProjectRootDirectory; }


	// 게임 프레임워크 디렉토리 경로를 반환합니다.
	//
	// @return - 게임 프레임워크 디렉토리 경로를 반환합니다.
	const std::string& GetFrameworkDirectory() const { return FrameworkDirectory; }


	// 게임 리소스 디렉토리 경로를 반환합니다.
	//
	// @return - 게임 리소스 디렉토리 경로를 반환합니다.
	const std::string& GetResourceDirectory() const { return ResourceDirectory; }


	// 전체 게임의 설정이 포함된 Json을 반환합니다.
	//
	// @return - 전체 게임의 설정이 포함된 Json을 반환합니다.
	const nlohmann::json& GetGameConfig() const { return GameConfig; }


	// 게임 프레임워크 및 전체 게임을 초기화합니다.
	virtual void Setup();


	// 게임을 실행합니다.
	virtual void Run() = 0;


private:
	// 게임 프레임워크 초기화 여부입니다.
	bool bIsInitialize = false;


	// 게임 프레임워크가 소유하는 윈도우입니다.
	GameWindow Window;


	// 게임 프레임워크가 소유하는 입력 시스템입니다.
	GameInput Input;


	// 게임 프레임워크가 소유하고 있는 렌더러 입니다.
	GameRenderer Renderer;


	// 실행 파일 경로입니다.
	std::string ExecuteDirectory;


	// 게임 프로젝트의 루트 디렉토리입니다.
	std::string ProjectRootDirectory;


	// 게임 프레임워크 디렉토리입니다.
	std::string FrameworkDirectory;


	// 게임 리소스 디렉토리입니다.
	std::string ResourceDirectory;


	// SDL2의 컴파일 버전입니다.
	SDL_version CompiledVersion;


	// SDL2의 링크 버전입니다.
	SDL_version LinkedVersion;


	// 전체 게임의 설정이 포함된 Json입니다.
	nlohmann::json GameConfig;
};