#pragma once

// @third party code - BEGIN stb
#include <stb/stb_rect_pack.h>
#include <stb/stb_truetype.h>
// @third party code - END

#include <string>
#include <cstdint>
#include <vector>
#include <memory>

struct SDL_Renderer;
struct SDL_Texture;


namespace Game
{
	/**
	 * 유니코드 텍스처 아틀라스의 클래스입니다.
	 */
	class UnicodeTextureAtlas
	{
	public:
		/**
		 * 유니코드 텍스처 아틀라스 클래스의 생성자입니다.
		 * @note 유니코드 텍스처 아틀라스를 사용하기 위해서는 반드시 Initialize 메서드를 호출해야 합니다.
		 */
		UnicodeTextureAtlas() = default;


		/**
		 * 유니코드 텍스처 아틀라스 클래스의 가상 소멸자입니다.
		 */
		virtual ~UnicodeTextureAtlas();

		
		/**
		 * 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다. 
		 */
		UnicodeTextureAtlas(UnicodeTextureAtlas&& InInstance) = delete;
		UnicodeTextureAtlas(const UnicodeTextureAtlas& InInstance) = delete;


		/**
		 * 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
		 */
		UnicodeTextureAtlas& operator=(UnicodeTextureAtlas&& InInstance) = delete;
		UnicodeTextureAtlas& operator=(const UnicodeTextureAtlas& InInstance) = delete;


		/**
		 * 유니코드 텍스처 아틀라스를 초기화합니다.
		 * 
		 * @param InRenderer - SDL_Renderer의 포인터입니다.
		 * @param InTTFBuffer - 트루 타입 폰트의 비트 정보입니다.
		 * @param InSize - 문자의 크기입니다.
		 * @param InStartUnicode - 생성할 폰트 텍스처 아틀라스의 시작 문자입니다. 
		 * @param InEndUnicode - 생성할 폰트 텍스처 아틀라스의 끝 문자입니다. 이때, 끝 문자를 포함합니다.
		 * 
		 * @throws 유니코드 텍스처 아틀라스 초기화에 실패할 경우, C++ 표준 예외를 던집니다.
		 */
		void Initialize(SDL_Renderer* InRenderer, const std::vector<uint8_t>& InTTFBuffer, float InSize, int32_t InStartUnicode, int32_t InEndUnicode);


		/**
		 * 유니코드 텍스처 아틀라스의 시작 문자를 반환합니다.
		 * 
		 * @return 유니코드 텍스처 아틀라스의 시작 문자를 반환합니다.
		 */
		int32_t GetStartUnicode() const { return StartUnicode; }


		/**
		 * 유니코드 텍스처 아틀라스의 끝 문자를 반환합니다.
		 * 
		 * @return 유니코드 텍스처 아틀라스의 끝 문자를 반환합니다.
		 */
		int32_t GetEndUnicode() const { return EndUnicode; }


		/**
		 * 유니코드 문자 집합의 정보를 반환합니다.
		 * 
		 * @return 유니코드 문자 집합의 정보를 반환합니다.
		 */
		const std::vector<stbtt_packedchar>& GetPackedchars() const { return Packedchars; }

		
		/**
		 * 유니코드 텍스처 아틀라스의 크기를 반환합니다.
		 * 
		 * @return 유니코드 텍스처 아틀라스의 크기를 반환합니다.
		 */
		int32_t GetTextureAtlasSize() const { return TextureAtlasSize; }


		/**
		 * 유니코드 텍스처 아틀라스를 반환합니다.
		 * 
		 * @return 유니코드 텍스처 아틀라스를 반환합니다.
		 */
		SDL_Texture* GetTextureAtlas() const { return TextureAtlas; }


		/**
		 * 유니코드가 현재의 텍스처 아틀라스 내의 문자 집합 범위 내에 있는지 확인합니다.
		 * 
		 * @param InUnicode - 범위 검사를 수행할 유니코드입니다.
		 * 
		 * @return 범위 내에 있다면 true, 그렇지 않다면 false 를 반환합니다.
		 */
		bool IsUnicodeInRange(const wchar_t& InUnicode) const;


	private:
		/**
		 * 문자 집합의 텍스처 아틀라스를 생성합니다.
		 * 
		 * @param InRenderer - SDL_Renderer의 포인터입니다.
		 * @param InTTFBuffer - 트루 타입 폰트의 비트 정보입니다.
		 * @param OutTextureAtlas - 생성한 텍스처 아틀라스입니다.
		 * @param OutPackedchars - 생성한 문자들의 위치 및 크기 정보들입니다.
		 * @param OutTextureSize - 생성한 텍스처 아틀라스의 크기입니다.
		 * 
		 * @throws 텍스처 생성에 실패할 경우, C++ 표준 예외를 던집니다.
		 */
		void GenerateUnicodeTextureAtlas(
			SDL_Renderer*                  InRenderer, 
			const std::vector<uint8_t>&    InTTFBuffer, 
			SDL_Texture*&                  OutTextureAtlas,
			std::vector<stbtt_packedchar>& OutPackedchars,
			int32_t&                       OutTextureSize
		);


	private:
		/**
		 * 유니코드 문자 집합의 시작점입니다.
		 */
		int32_t StartUnicode = 0;


		/**
		 * 유니코드 문자 집합의 끝점입니다
		 */
		int32_t EndUnicode = 0;


		/**
		 * 폰트의 크기입니다.
		 */
		float FontSize = 0.0f;


		/**
		 * 유니코드 문자 집합의 정보입니다.
		 */
		std::vector<stbtt_packedchar> Packedchars;


		/**
		 * 유니코드 문자 집합의 텍스처 아틀라스입니다.
		 */
		SDL_Texture* TextureAtlas = nullptr;


		/**
		 * 유니코드 문자 집합 텍스처 아틀라스의 크기입니다.
		 */
		int32_t TextureAtlasSize = 0;
	};

	
	/**
	 * 트루 타입 폰트 클래스입니다.
	 */
	class TTFont
	{
	public:
		/**
		 * 트루 타입 폰트 클래스의 생성자입니다.
		 * @note 트루 타입 폰트 클래스를 사용하기 위해서는 반드시 Initialize 메서드를 호출해야 합니다.
		 */
		TTFont() = default;


		/**
		 * 트루 타입 폰트 클래스의 가상 소멸자입니다.
		 */
		virtual ~TTFont();

		
		/**
		 * 폰트를 초기화합니다.
		 * 
		 * @param InRenderer - SDL_Renderer의 포인터입니다.
		 * @param InPath - 트루 타입 폰트의 리소스 경로입니다.
		 * @param InSize - 문자의 크기입니다.
		 * 
		 * @throws 
		 * - 트루 타입 폰트 로드에 실패할 경우 C++ 표준 예외를 반환합니다
		 * - 폰트 정보 생성에 실패할 경우 C++ 표준 예외를 반환합니다.
		 */
		void Initialize(SDL_Renderer* InRenderer, const std::string& InPath, float InFontSize);


		/**
		 * 트루 타입 폰트의 크기를 반환합니다.
		 * 
		 * @return 트루 타입 폰트의 크기를 반환합니다.
		 */
		float GetFontSize() const { return FontSize; }


		// 텍스처 아틀라스를 반환합니다.
		// 
		// @param InUnicode - 유니코드 문자입니다.
		// @return - 인자로 받은 유니코드를 포함하는 텍스처 아틀라스의 포인터를 반환합니다.
		SDL_Texture* GetTextureAtlas(const wchar_t& InUnicode) const;


		// stbtt_packedchar를 반환합니다.
		//
		// @param InUnicode - 유니코드 문자입니다.
		// @return - 인자로 받은 유니코드에 대응하는 stbtt_packedchar를 반환합니다.
		const stbtt_packedchar& GetPackedchar(const wchar_t& InUnicode) const;


	private:
		// 파일로부터 트루 타입 폰트를 불러옵니다.
		//
		// @param InPath - 트루 타입 폰트의 리소스 경로입니다.
		// @param OutBuffer - 트루 타입 폰트의 비트 정보를 저장할 버퍼입니다.
		// @param OutFontInfo - 폰트 정보입니다.
		// @throws 
		// - 트루 타입 폰트 로드에 실패할 경우, C++ 표준 예외를 반환합니다.
		// - 폰트 정보 생성에 실패할 경우 C++ 표준 예외를 반환합니다.
		void LoadTrueTypeFontFromFile(const std::string& InPath, std::vector<uint8_t>& OutBuffer, stbtt_fontinfo& OutFontInfo);


	private:
		/**
		 * 트루 타입 폰트의 크기입니다.
		 */
		float FontSize = 0.0f;


		/**
		 * ASCII 문자의 텍스처 아틀라스입니다.
		 */
		std::unique_ptr<UnicodeTextureAtlas> AsciiTextureAtlas = nullptr;


		/**
		 * HANGUL 문자의 텍스처 아틀라스입니다.
		 */
		std::unique_ptr<UnicodeTextureAtlas> HangulTextureAtlas = nullptr;
	};
}