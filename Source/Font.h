#pragma once

// 표준 라이브러리와 SDL2를 사용하기 위해서 헤더 파일을 추가합니다.
#include "Header.h"

// 트루 타입 폰트를 처리하기 위한 헤더 선언을 추가합니다.
#include <stb/stb_rect_pack.h>
#include <stb/stb_truetype.h>


namespace Game
{
	// 문자 집합의 텍스처 아틀라스입니다.
	class CharacterTextureAtlas
	{
	public:
		// 생성자입니다.
		//
		// @param InRenderer - SDL_Renderer의 포인터입니다.
		// @param InTTFBuffer - 트루 타입 폰트의 비트 정보입니다.
		// @param InSize - 문자의 크기입니다.
		// @param InStartUnicode - 생성할 폰트 텍스처 아틀라스의 시작 문자입니다. 
		// @param InEndUnicode - 생성할 폰트 텍스처 아틀라스의 끝 문자입니다. 이때, 끝 문자를 포함합니다.
		// 
		// @throws - 텍스처 생성에 실패할 경우, C++ 표준 예외를 반환합니다.
		CharacterTextureAtlas(
			SDL_Renderer* InRenderer,
			const std::vector<uint8_t>& InTTFBuffer,
			float InSize,
			int32_t InStartUnicode,
			int32_t InEndUnicode
		);


		// 가상 소멸자입니다.
		virtual ~CharacterTextureAtlas();

		
		// 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다. 
		CharacterTextureAtlas(CharacterTextureAtlas&& InInstance) = delete;
		CharacterTextureAtlas(const CharacterTextureAtlas& InInstance) = delete;


		// 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
		CharacterTextureAtlas& operator=(CharacterTextureAtlas&& InInstance) = delete;
		CharacterTextureAtlas& operator=(const CharacterTextureAtlas& InInstance) = delete;


		// 문자 집합의 시작 유니코드를 반환합니다.
		int32_t GetStartUnicode() const { return StartUnicode; }


		// 문자 집합의 끝 유니코드를 반환합니다.
		int32_t GetEndUnicode() const { return EndUnicode; }


		// 문자 집합의 정보를 반환합니다.
		//
		// @return - 문자 집합의 정보를 반환합니다.
		const std::vector<stbtt_packedchar>& GetPackedchars() const { return Packedchars; }


		// 텍스처 아틀라스의 크기를 반환합니다.
		//
		// @return - 텍스처 아틀라스의 크기를 반환합니다.
		int32_t GetTextureAtlasSize() const { return TextureAtlasSize; }


		// 텍스처 아틀라스를 반환합니다.
		//
		// @return - 텍스처 아틀라스를 반환합니다.
		SDL_Texture* GetTextureAtlas() const { return TextureAtlas; }


		// 특정 유니코드가 현재의 텍스처 아틀라스 내의 문자 집합 범위 내에 있는지 확인합니다.
		//
		// @param InUnicode - 범위 검사를 수행할 유니코드입니다.
		//
		// @return - 범위 내에 있다면 true, 그렇지 않다면 false 를 반환합니다.
		bool IsUnicodeInRange(const wchar_t& InUnicode) const;


	private:
		// 문자 집합의 텍스처 아틀라스를 생성합니다.
		//
		// @param InRenderer - SDL_Renderer의 포인터입니다.
		// @param InTTFBuffer - 트루 타입 폰트의 비트 정보입니다.
		// @param OutTextureAtlas - 생성한 텍스처 아틀라스입니다.
		// @param OutPackedchars - 생성한 문자들의 위치 및 크기 정보들입니다.
		// @param OutTextureSize - 생성한 텍스처 아틀라스의 크기입니다.
		// 
		// @throws - 텍스처 생성에 실패할 경우, C++ 표준 예외를 반환합니다.
		void CreateCharacterTextureAtlas(
			SDL_Renderer* InRenderer, 
			const std::vector<uint8_t>& InTTFBuffer, 
			SDL_Texture*& OutTextureAtlas,
			std::vector<stbtt_packedchar>& OutPackedchars,
			int32_t& OutTextureSize
		);


	private:
		// 문자 집합의 시작점입니다.
		int32_t StartUnicode = 0;


		// 문자 집합의 끝점입니다.
		int32_t EndUnicode = 0;


		// 폰트의 크기입니다.
		float FontSize = 0.0f;


		// 문자 집합의 정보입니다.
		std::vector<stbtt_packedchar> Packedchars;


		// 텍스처 아틀라스입니다.
		SDL_Texture* TextureAtlas = nullptr;


		// 텍스처 아틀라스의 크기입니다.
		int32_t TextureAtlasSize = 0;
	};

	
	// 폰트 클래스입니다.
	class Font
	{
	public:
		// 생성자입니다.
		//
		// @param InRenderer - SDL_Renderer의 포인터입니다.
		// @param InPath - 트루 타입 폰트의 리소스 경로입니다.
		// @param InSize - 문자의 크기입니다.
		// @throws 
		// - 트루 타입 폰트 로드에 실패할 경우 C++ 표준 예외를 반환합니다
		// - 폰트 정보 생성에 실패할 경우 C++ 표준 예외를 반환합니다.
		Font(SDL_Renderer* InRenderer, const std::string& InPath, float InFontSize);


		// 가상 소멸자입니다.
		virtual ~Font();


		// 폰트의 크기를 반환합니다.
		//
		// @return - 폰트의 크기를 반환합니다.
		float GetFontSize() const { return FontSize; }


		// 텍스처 아틀라스를 반환합니다.
		// 
		// @param InUnicode - 유니코드 문자입니다.
		// @return - 인자로 받은 유니코드를 포함하는 텍스처 아틀라스의 포인터를 반환합니다.
		SDL_Texture* GetAtlas(const wchar_t& InUnicode) const;


		// stbtt_packedchar를 반환합니다.
		//
		// @param InUnicode - 유니코드 문자입니다.
		// @return - 인자로 받은 유니코드에 대응하는 stbtt_packedchar를 반환합니다.
		const stbtt_packedchar& GetPackedchar(const wchar_t& InUnicode) const;


	private:
		// 트루 타입 폰트를 불러옵니다.
		//
		// @param InPath - 트루 타입 폰트의 리소스 경로입니다.
		// @param OutBuffer - 트루 타입 폰트의 비트 정보를 저장할 버퍼입니다.
		// @param OutFontInfo - 폰트 정보입니다.
		// @throws 
		// - 트루 타입 폰트 로드에 실패할 경우, C++ 표준 예외를 반환합니다.
		// - 폰트 정보 생성에 실패할 경우 C++ 표준 예외를 반환합니다.
		void LoadTrueTypeFont(const std::string& InPath, std::vector<uint8_t>& OutBuffer, stbtt_fontinfo& OutFontInfo);


	private:
		// 게임 폰트의 크기입니다.
		float FontSize = 0.0f;


		// ASCII 문자의 텍스처 아틀라스입니다.
		std::unique_ptr<CharacterTextureAtlas> AsciiTextureAtlas = nullptr;


		// HANGUL 문자의 텍스처 아틀라스입니다.
		std::unique_ptr<CharacterTextureAtlas> HangulTextureAtlas = nullptr;
	};
}