#pragma once

// 트루 타입 폰트를 처리하기 위한 헤더 선언을 추가합니다.
#include <stb/stb_rect_pack.h>
#include <stb/stb_truetype.h>

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


// 문자 집합의 텍스처 아틀라스입니다.
class CharacterTextureAtlas
{
public:
	// 생성자입니다.
	CharacterTextureAtlas() = default;


	// 가상 소멸자입니다.
	virtual ~CharacterTextureAtlas();


	// 문자 집합의 텍스처 아틀라스를 생성합니다.
	// 
	// @param InBuffer - 트루 타입 폰트의 비트 정보입니다.
	// @param InSize - 문자의 크기입니다.
	// @param InStartUnicode - 생성할 폰트 텍스처 아틀라스의 시작 문자입니다. 
	// @param InEndUnicode - 생성할 폰트 텍스처 아틀라스의 끝 문자입니다. 이때, 끝 문자를 포함합니다.
	// @throws - 텍스처 생성에 실패할 경우, C++ 표준 예외를 반환합니다.
	void CreateCharacterTextureAtlas(const std::vector<uint8_t>& InBuffer, float InSize, int32_t InStartUnicode, int32_t InEndUnicode);


	// 문자 집합의 정보를 반환합니다.
	//
	// @return - 문자 집합의 정보를 반환합니다.
	const std::vector<stbtt_packedchar>& GetPackedchars() const { return Packedchars; }


	// 텍스처 아틀라스를 반환합니다.
	//
	// @return - 텍스처 아틀라스를 반환합니다.
	SDL_Texture* GetTextureAtlas() const { return TextureAtlas; }


private:
	// 문자 집합의 텍스처 아틀라스를 생성합니다.
	//
	// @param InRenderer - SDL_Renderer의 포인터입니다.
	// @param InBuffer - 트루 타입 폰트의 비트 정보입니다.
	// @param InSize - 문자의 크기입니다.
	// @throws - 텍스처 생성에 실패할 경우, C++ 표준 예외를 반환합니다.
	void CreateCharacterTextureAtlas(SDL_Renderer* InRenderer, const std::vector<uint8_t>& InBuffer, float InSize);


private:
	// 문자 집합의 시작점입니다.
	int32_t StartUnicode = 0;


	// 문자 집합의 끝점입니다.
	int32_t EndUnicode = 0;


	// 문자 집합의 정보입니다.
	std::vector<stbtt_packedchar> Packedchars;


	// 텍스처 아틀라스입니다.
	SDL_Texture* TextureAtlas = nullptr;


	// 텍스처 아틀라스의 크기입니다.
	int32_t TextureAtlasSize = 0;
};


// 게임 내에서 사용할 폰트 클래스입니다.
class GameFont
{
public:
	// 생성자입니다.
	GameFont() = default;


	// 가상 소멸자입니다.
	virtual ~GameFont();


	// 게임 폰트를 생성합니다.
	//
	// @param InPath - 트루 타입 폰트의 리소스 경로입니다.
	// @param InSize - 문자의 크기입니다.
	// @throws 
	// - 트루 타입 폰트 로드에 실패할 경우 C++ 표준 예외를 반환합니다
	// - 폰트 정보 생성에 실패할 경우 C++ 표준 예외를 반환합니다.
	void CreateGameFont(const std::string& InPath, float InSize);


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
	// 게임 폰트 초기화여부입니다.
	bool bIsInitialize = false;


	// 게임 폰트의 크기입니다.
	float FontSize = 0.0f;


	// ASCII 문자의 텍스처 아틀라스입니다.
	CharacterTextureAtlas AsciiTextureAtlas;


	// HANGUL 문자의 텍스처 아틀라스입니다.
	CharacterTextureAtlas HangulTextureAtlas;
};