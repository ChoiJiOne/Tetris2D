#pragma once

// json을 사용하기 위한 헤더 선언을 추가합니다.
#include <json/json.hpp>

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


// Json 파일 관련 유틸리티 클래스입니다.
class JsonUtil
{
public:
	// Json 파일을 로드합니다.
	// 
	// @param InPath - UTF-8 기반의 Json 파일 경로입니다.
	// @throws - Json 파일 로드에 실패할 경우, C++ 표준 예외를 반환합니다.
	// @return - nlohmann::json를 반환합니다.
	static nlohmann::json LoadJsonFile(const std::string& InPath);


	// Json 파일을 로드합니다.
	// 
	// @param InPath - UTF-16 기반의 Json 파일 경로입니다.
	// @throws - Json 파일 로드에 실패할 경우, C++ 표준 예외를 반환합니다.
	// @param - nlohmann::json를 반환합니다.
	static nlohmann::json LoadJsonFile(const std::wstring& InPath);
};