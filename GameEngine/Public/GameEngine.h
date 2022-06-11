#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


// 게임 엔진 클래스입니다.
class GameEngine
{
public:
	// 게임 엔진을 초기화합니다.
	static void Init();


	// 게임 엔진 사용을 종료합니다.
	static void Release();




	// 게임 프레임워크가 소유하는 윈도우를 반환합니다.
	// 이때, 반환된 윈도우는 변경 가능합니다.
	//
	// @return - 윈도우의 참조자를 반환합니다.
	GameWindow& GetGameWindow();


	// 게임 프레임워크가 소유하는 입력 시스템을 반환합니다.
	// 이때, 반환된 입력 시스템은 변경 가능합니다.
	// 
	// @return - 입력 시스템의 참조자를 반환합니다.
	GameInput& GetGameInput();



	// 게임 프레임워크가 소유하는 렌더러를 반환합니다.
	// 이때, 반환된 렌더러는 변경 가능합니다.
	// 
	// @return - 렌더러의 참조자를 반환합니다.
	GameRenderer& GetGameRenderer();


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
	const std::string& GetEngineDirectory() const { return FrameworkDirectory; }


	// 게임 리소스 디렉토리 경로를 반환합니다.
	//
	// @return - 게임 리소스 디렉토리 경로를 반환합니다.
	const std::string& GetResourceDirectory() const { return ResourceDirectory; }


private:
	// 게임 프레임워크 초기화 여부입니다.
	static bool bIsInitialize;


	// 게임 프레임워크가 소유하는 윈도우입니다.
	static std::unique_ptr<class GameWindow> Window;


	// 게임 프레임워크가 소유하는 입력 시스템입니다.
	static std::unique_ptr<class GameInput> Input;


	// 게임 프레임워크가 소유하고 있는 렌더러 입니다.
	static std::unique_ptr<class GameRenderer> Renderer;


	// 실행 파일 경로입니다.
	static std::string ExecuteDirectory;


	// 게임 프로젝트의 루트 디렉토리입니다.
	static std::string ProjectRootDirectory;


	// 게임 프레임워크 디렉토리입니다.
	static std::string EngineDirectory;


	// 게임 리소스 디렉토리입니다.
	static std::string ResourceDirectory;


	// SDL2의 컴파일 버전입니다.
	static SDL_version CompiledVersion;


	// SDL2의 링크 버전입니다.
	static SDL_version LinkedVersion;
};