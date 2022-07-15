#pragma once

// @third party code - stb
#include <stb/stb_image.h>
// @third party code - END

#include <string>
#include <cstdint>

struct SDL_Texture;
struct SDL_Renderer;


namespace Game
{
	/**
	 * 2D 텍스처 클래스입니다.
	 */
	class Texture2D
	{
	public:
		/**
		 * RGBA32 픽셀 포멧의 크기입니다. 
		 * @note 단위는 바이트 단위입니다.
		 */
		const static int32_t PIXEL_FORMAT_RGBA32 = 4;


		/**
		 * RGB24 픽셀 포멧의 크기입니다. 
		 * @note 단위는 바이트 단위입니다.
		 */
		const static int32_t PIXEL_FORMAT_RGB24 = 3;


	public:
		/**
		 * 2D 텍스처 클래스의 생성자입니다.
		 * @note 2D 텍스처 클래스를 사용하기 위해서는 반드시 Initialize를 호출해야 합니다.
		 */
		Texture2D() = default;


		// 가상 소멸자입니다.
		/**
		 * 
		 */
		virtual ~Texture2D();

		// 생성자입니다.
		// 
		// @param InRenderer - SDL 렌더러의 포인터입니다.
		// @param InPath - 텍스처 이미지의 리소스 경로입니다.
		// 
		// @throws 
		// - 이미지 파일 로딩을 실패할 경우, C++ 표준 예외를 던집니다.
		// - 텍스처 생성에 실패할 경우, C++ 표준 예외를 던집니다.
		Texture2D(SDL_Renderer* InRenderer, const std::string& InPath);


		// 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다.
		Texture2D(Texture2D&& InInstance) = delete;
		Texture2D(const Texture2D& InInstance) = delete;


		// 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
		Texture2D& operator=(Texture2D&& InInstance) = delete;
		Texture2D& operator=(const Texture2D& InInstance) = delete;


		// 텍스처의 가로 크기를 반환합니다.
		// 
		// @return - 텍스처의 가로 크기를 반환합니다.
		int32_t GetWidth() const { return Width; }


		// 텍스처의 세로 크기를 반환합니다.
		// 
		// @return - 텍스처의 세로 크기를 반환합니다.
		int32_t GetHeight() const { return Height; }


		// 텍스처의 픽셀 포멧 크기를 반환합니다.
		// 
		// @return - 텍스처의 픽셀 포멧 크기를 반환합니다.
		uint32_t GetPixelFormat() const { return PixelFormat; }


		// SDL_Texture의 포인터를 반환합니다.
		//
		// @return - SDL 텍스처의 포인터를 반환합니다.
		SDL_Texture* GetTexture() const { return Texture; }
		

	private:
		// 이미지 파일로부터 텍스처를 생성합니다.
		// 
		// @param InRenderer - SDL 렌더러의 포인터입니다.
		// @param InPath - 텍스처 이미지의 리소스 경로입니다.
		// 
		// @throws 
		// - 이미지 파일 로딩을 실패할 경우, C++ 표준 예외를 던집니다.
		// - 텍스처 생성에 실패할 경우, C++ 표준 예외를 던집니다.
		void CreateTextureFromFile(SDL_Renderer* InRenderer, const std::string& InPath);


		// 텍스처 이미지 파일로 부터 텍스처 버퍼를 로드합니다.
		// 
		// @param InRenderer - SDL 렌더러의 포인터입니다.
		// @param InPath - 텍스처 이미지의 리소스 경로입니다.
		// @param OutBuffer - 텍스처 버퍼입니다.
		// @param OutWidth - 텍스처 버퍼의 가로 길이입니다.
		// @param OutHeight - 텍스처 버퍼의 세로 길이입니다.
		// @param OutFormat - 텍스처 버퍼의 픽셀 포멧입니다.
		//
		// @thrors
		// - 텍스처 파일 로딩에 실패할 경우, C++ 표준 예외를 던집니다.
		void LoadTextureBufferFromFile(const std::string& InPath, uint8_t*& OutBuffer, int32_t& OutWidth, int32_t& OutHeight, int32_t& OutFormat);


		// 텍스처 버퍼로 부터 텍스처 리소스를 생성합니다.
		// 
		// @param InRenderer - SDL 렌더러의 포인터입니다.
		// @param InBuffer - 텍스처 버퍼입니다.
		// @param InWidth - 텍스처 버퍼의 가로 길이입니다.
		// @param InHeight - 텍스처 버퍼의 세로 길이입니다.
		// @param InFormat - 텍스처의 픽셀 포멧입니다.
		// 
		// @throws 이미지의 포멧이 지원하지 않는 포멧일 경우, C++ 표준 예외를 반환합니다.
		// 
		// @returen - SDL 텍스처 포인터를 반환합니다.
		SDL_Texture* CreateTextureFromBuffer(SDL_Renderer* InRenderer, uint8_t*& InBuffer, const int32_t& InWidth, const int32_t& InHeight, const int32_t& InFormat);


	private:
		// 텍스처의 가로 크기입니다. 이때, 단위는 픽셀 단위입니다.
		int32_t Width = 0;


		// 텍스처의 세로 크기입니다. 이때, 단위는 픽셀 단위입니다.
		int32_t Height = 0;


		// 텍스처의 포멧입니다. RGBA 는 32, RGB 는 24 입니다.
		int32_t PixelFormat = 0;


		// SDL_Texture의 포인터입니다.
		SDL_Texture* Texture = nullptr;
	};
}