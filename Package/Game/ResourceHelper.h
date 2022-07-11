#pragma once

// 표준 라이브러리와 SDL2를 사용하기 위해서 헤더 파일을 추가합니다.
#include "Header.h"


namespace Game
{
	// 리소스를 관리하는 클래스입니다.
	class ResourceHelper
	{
	public:
		// 리소스를 정리합니다.
		static void Cleanup();


		// 텍스처 리소스를 생성합니다.
		// 
		// @param InRenderer - SDL 렌더러의 포인터입니다.
		// @param InHashKey - 텍스처 리소스의 해쉬 키값입니다.
		// @param InPath - 텍스처 이미지의 리소스 경로입니다.
		//
		// @throws 
		// - 키 값이 충돌할 경우, C++ 표준 예외를 던집니다.
		// - 텍스처 리소스 생성 실패 시, C++ 표준 예외를 던집니다.
		//
		// @return - 생성한 텍스처 리소스의 상수 참조자를 반환합니다.
		static const class Texture2D& CreateTexture2D(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const std::string& InPath);


		// 폰트 리소스를 생성합니다.
		//
		// @param InRenderer - SDL 렌더러의 포인터입니다.
		// @param InHashKey - 폰트 리소스의 해쉬 키값입니다.
		// @param InPath - 폰트 리소스의 경로입니다.
		// @param InFontSize - 폰트 리소스의 크기입니다.
		// 
		// @throws 
		// - 키 값이 충돌할 경우, C++ 표준 예외를 던집니다.
		// - 폰트 리소스 생성 실패 시, C++ 표준 예외를 던집니다.
		//
		// @return - 생성한 폰트 리소스의 상수 참조자를 반환합니다.
		static const class Font& CreateFont(SDL_Renderer* InRenderer, const std::size_t& InHashKey, const std::string& InPath, float InFontSize);

		
		// 리소스 헬퍼가 관리하는 텍스처를 반환합니다.
		//
		// @param InHashKey - 텍스처 리소스의 키값입니다.
		// 
		// @throws - 키 값에 대응하는 텍스처 리소스가 존재하지 않을 경우, C++ 표준 예외를 던집니다.
		//
		// @return - 키 값에 대응하는 텍스처 리소스의 상수 참조자를 반환합니다.
		static const class Texture2D& GetTexture2D(const std::size_t& InHashKey);


		// 리소스 헬퍼가 관리하는 폰트를 반환합니다.
		//
		// @param InHashKey - 폰트 리소스의 키값입니다.
		//
		// @throws - 키 값에 대응하는 폰트 리소스가 존재하지 않을 경우, C++ 표준 예외를 던집니다.
		//
		// @return - 키 값에 대응하는 폰트 리소스의 상수 참조자를 반환합니다.
		static const class Font& GetFont(const std::size_t& InHashKey);


	private:
		// 리소스 헬퍼가 관리하는 텍스처 캐쉬입니다.
		static std::unordered_map<std::size_t, std::shared_ptr<class Texture2D>> TextureCache;


		// 리스소 헬퍼가 관리하는 폰트 캐쉬입니다.
		static std::unordered_map<std::size_t, std::shared_ptr<class Font>> FontCache;
	};
}