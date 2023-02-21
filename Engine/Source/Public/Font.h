#pragma once

#include "Macro.h"
#include "Vector.hpp"

#include <vector>
#include <string>
#include <memory>
#include <d3d11.h>


/**
 * @brief 텍스처 아틀라스에 표시된 문자 정보입니다.
 */
struct Glyph
{
	int32_t CodePoint;
	Vec2i Position0;
	Vec2i Position1;
	float XOffset;
	float YOffset;
	float XOffset2;
	float YOffset2;
	float XAdvance;
};


/**
 * @brief 트루 타입 폰트에 대응하는 문자들의 텍스처 아틀라스입니다.
 */
class Font
{
public:
	/**
	 * @brief 트루 타입 폰트를 로딩하고 텍스트 텍스처 아틀라스를 생성하는 폰트의 생성자입니다.
	 * 
	 * @param Device 텍스처 아틀라스를 생성하는 데 사용할 디바이스입니다.
	 * @param ResourcePath 트루 타입 폰트 파일의 경로입니다.
	 * @param BeginCodePoint 문자 텍스처 아틀라스의 코드 포인트 시작점입니다.
	 * @param EndCodePoint 문자 텍스처 아틀라스의 코드 포인트 끝점입니다.
	 * @param FontSize 폰트의 크기입니다.
	 * 
	 * @throws 
	 * 트루 타입 폰트 로딩에 실패하면 C++ 표준 예외를 던집니다.
	 * 텍스처 아틀라스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	Font(ID3D11Device* Device, const std::string& ResourcePath, int32_t BeginCodePoint, int32_t EndCodePoint, float FontSize);


	/**
	 * @brief 폰트의 가상 소멸자입니다.
	 */
	virtual ~Font();


	/**
	 * @brief 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Font);


	/**
	 * @brief 텍스처 아틀라스 데이터를 얻습니다.
	 * 
	 * @return 2D 텍스처 아틀라스 데이터를 얻습니다.
	 */
	ID3D11Texture2D* GetTextureAtlas() { return TextureAtlas_; }


	/**
	 * @brief 셰이더에 바인딩 할 텍스처 아틀라스 리소스 뷰를 얻습니다.
	 * 
	 * @return 셰이더에 바인딩 할 텍스처 아틀라스 리소스 뷰를 반환합니다.
	 */
	ID3D11ShaderResourceView* GetTextureAtlasView() { return TextureAtlasView_; }


	/**
	 * @brief 코드 포인트에 대응하는 문자 위치 및 크기 정보를 얻습니다.
	 *
	 * @param CodePoint 위치 및 정보를 알고 싶은 코드 포인트 값입니다.
	 *
	 * @throws 코드 포인트 값이 범위 내에 없으면 C++ 표준 예외를 던집니다.
	 *
	 * @return 코드 포인트에 대응하는 문자의 위치 및 크기 정보를 반환합니다.
	 */
	const Glyph& GetGlyph(int32_t CodePoint) const;


	/**
	 * @brief 텍스처 아틀라스의 크기를 얻습니다.
	 * 
	 * @return 텍스처 아틀라스의 크기를 반환합니다.
	 */
	int32_t GetAtlasSize() const { return AtlasSize_; }


	/**
	 * @brief 코드 포인트가 범위 내에 포함되는지 확인합니다.
	 *
	 * @param CodePoint 범위 검사를 수행할 코드 포인트 값입니다.
	 *
	 * @return 범위 내에 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool HasCodePointInRange(int32_t CodePoint) const;


	/**
	 * @brief 텍스트의 크기를 측정합니다.
	 * 
	 * @note 측정 단위는 픽셀 단위입니다.
	 *
	 * @param Text 측정할 텍스트입니다.
	 * @param Width[out] 측정한 텍스트의 가로 크기입니다.
	 * @param Height[out] 측정한 텍스트의 세로 크기입니다.
	 */
	template <typename T>
	void MeasureText(const std::wstring& Text, T& Width, T& Height) const
	{
		int32_t TextHeight = -1;
		int32_t TextWidth = 0;

		for (const auto& Unicode : Text)
		{
			const Glyph& UnicodeInfo = GetGlyph(static_cast<int32_t>(Unicode));

			int32_t CurrWidth = static_cast<int32_t>(UnicodeInfo.XAdvance);
			int32_t CurrHeight = UnicodeInfo.Position1.y - UnicodeInfo.Position0.y;

			TextWidth += CurrWidth;

			if (CurrHeight > TextHeight)
			{
				TextHeight = CurrHeight;
			}
		}

		Width = static_cast<T>(TextWidth);
		Height = static_cast<T>(TextHeight);
	}


private:
	/**
	 * @brief 텍스처 아틀라스 비트맵을 생성합니다.
	 * 
	 * @note 텍스처 아틀라스의 가로 세로 크기는 같습니다.
	 *
	 * @param Buffer 트루 타입 폰트 리소스 버퍼입니다.
	 * @param BeginCodePoint 문자 텍스처 아틀라스의 코드 포인트 시작점입니다.
	 * @param EndCodePoint 문자 텍스처 아틀라스의 코드 포인트 끝점입니다.
	 * @param FontSize 폰트의 크기입니다.
	 * @param Glyphs[out] 텍스처 아틀라스 상의 코드 포인트에 대응하는 문자 위치 및 크기 정보입니다.
	 * @param AtlasSize[out] 텍스처 아틀라스 크기입니다.
	 *
	 * @return 생성된 텍스처 아틀라스 비트맵을 반환합니다.
	 */
	std::shared_ptr<uint8_t[]> GenerateTextureAtlasBitmap(
		const std::vector<uint8_t>& Buffer,
		int32_t BeginCodePoint,
		int32_t EndCodePoint,
		float FontSize,
		std::vector<Glyph>& Glyphs,
		int32_t& AtlasSize
	);


	/**
	 * @brief 텍스처 아틀라스 비트맵으로 부터 텍스처 리소스를 생성합니다.
	 *
	 * @param Device 텍스처 리소스를 생성할 때 사용할 디바이스입니다.
	 * @param Bitmap 텍스처 아틀라스 비트맵입니다.
	 * @param AtlasSize 텍스처 아틀라스 비트맵의 가로 세로 크기입니다
	 *
	 * @throws 텍스처 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 *
	 * @return 텍스처 아틀라스 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않다면 그 외의 값을 반환합니다.
	 */
	HRESULT CreateTextureAtlasFromBitmap(
		ID3D11Device* Device,
		const std::shared_ptr<uint8_t[]>& Bitmap,
		const int32_t& AtlasSize
	);


private:
	/**
	 * @brief 문자 텍스처 아틀라스의 코드 포인트 시작점입니다.
	 * 
	 * @note 텍스처 아틀라스는 시작점을 포함합니다.
	 */
	int32_t BeginCodePoint_ = 0;


	/**
	 * @brief 문자 텍스처 아틀라스의 코드 포인트 끝점입니다.
	 * 
	 * @note 텍스처 아틀라스는 끝점을 포함합니다.
	 */
	int32_t EndCodePoint_ = 0;


	/**
	 * @brief 텍스처 아틀라스의 크기입니다.
	 */
	int32_t AtlasSize_ = 0;


	/**
	 * @brief 텍스처 아틀라스 상의 코드 포인트에 대응하는 문자 위치 및 크기 정보입니다.
	 */
	std::vector<Glyph> Glyphs_;


	/**
	 * @brief 텍스트 텍스처 아틀라스입니다.
	 */
	ID3D11Texture2D* TextureAtlas_ = nullptr;


	/**
	 * @brief 텍스트 텍스처 아틀라스 리소스 뷰입니다.
	 */
	ID3D11ShaderResourceView* TextureAtlasView_ = nullptr;
};