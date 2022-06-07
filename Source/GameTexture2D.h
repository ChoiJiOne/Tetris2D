#pragma once

#include "CommonHeader.h"


// 게임 내에서 사용할 텍스처 클래스입니다.
class GameTexture2D
{
public:
	// 생성자입니다.
	// 
	// @param InRenderer - SDL_Renderer의 포인터입니다.
	// @param InPath - 텍스처 이미지의 리소스 경로입니다.
	GameTexture2D(SDL_Renderer* InRenderer, const std::string& InPath);


	// 가상 소멸자입니다.
	virtual ~GameTexture2D();


	// 텍스처의 가로 크기를 반환합니다.
	// 
	// @return - 텍스처의 가로 크기를 반환합니다.
	int32_t GetWidth() const { return Width; }


	// 텍스처의 세로 크기를 반환합니다.
	// 
	// @return - 텍스처의 세로 크기를 반환합니다.
	int32_t GetHeight() const { return Height; }


	// SDL_Texture의 포인터를 반환합니다.
	//
	// @return - SDL 텍스처의 포인터를 반환합니다.
	SDL_Texture* GetTexture() const { return Texture; }


private:
	// 텍스처의 가로 크기입니다.
	// 이때, 단위는 픽셀 단위입니다.
	int32_t Width = 0;


	// 텍스처의 세로 크기입니다.
	// 이때, 단위는 픽셀 단위입니다.
	int32_t Height = 0;


	// SDL_Texture의 포인터입니다.
	SDL_Texture* Texture = nullptr;
};