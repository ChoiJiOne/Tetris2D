#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


// 글로벌 요소들을 관리하는 클래스입니다.
class GlobalProperty
{
public:
	// 글로벌 요소들을 초기화합니다.
	static void Initialize();


	// 글로벌 요소들의 리소스를 해제합니다.
	static void Release();


	// GlobalProperty 초기화 여부를 반환합니다.
	//
	// @return - GlobalProperty 초기화 여부를 반환합니다.
	static bool IsInitialize() noexcept { return bIsInitialize; }


	// 실행 파일 경로를 반환합니다.
	//
	// @return - 실행 파일 경로를 반환합니다.
	static std::string GetExecuteDirectory() noexcept { return ExecuteDirectory; }


	// 게임 프로젝트의 루트 디렉토리를 반환합니다.
	//
	// @return - 게임 프로젝트의 루트 디렉토리를 반환합니다.
	static std::string GetProjectRootDirectory() noexcept { return ProjectRootDirectory; }


	// 게임 소스 코드 디렉토리를 반환합니다.
	//
	// @return - 게임 소스 코드 디렉토리를 반환합니다.
	static std::string GetSourceCodeDirectory() noexcept { return SourceCodeDirectory; }


	// 게임 리소스 디렉토리를 반환합니다.
	//
	// @return - 게임 리소스 디렉토리를 반환합니다.
	static std::string GetResourceDirectory() noexcept { return ResourceDirectory; }


private:
	// GlobalProperty 초기화 여부입니다.
	static bool bIsInitialize;


	// 실행 파일 경로입니다.
	static std::string ExecuteDirectory;

	
	// 게임 프로젝트의 루트 디렉토리입니다.
	static std::string ProjectRootDirectory;


	// 게임 소스 코드 디렉토리입니다.
	static std::string SourceCodeDirectory;


	// 게임 리소스 디렉토리입니다.
	static std::string ResourceDirectory;
};