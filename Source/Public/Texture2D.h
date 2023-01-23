#pragma once

#include "Macro.h"

#include <vector>
#include <array>

#include <d3d11.h>


/**
 * @brief 2D 텍스처 리소스입니다.
 */
class Texture2D
{
public:
	/**
	 * @brief 텍스처의 크기입니다.
	 * 
	 * @see https://docs.unrealengine.com/4.27/en-US/RenderingAndGraphics/Textures/SupportAndSettings/
	 */
	enum class EResolution
	{
		SIZE_16X16     = 16,
		SIZE_32X32     = 32,
		SIZE_64X64     = 64,
		SIZE_128X128   = 128,
		SIZE_256X256   = 256,
		SIZE_512X512   = 512,
		SIZE_1024X1024 = 1024,
		SIZE_2048X2048 = 2048,
		SIZE_4096X4096 = 4096,
		SIZE_8192X8192 = 8192,
	};
	

public:
	/**
	 * @brief 2D 텍스처 리소스 생성자입니다.
	 * 
	 * @param Device 텍스처 리소스를 생성할 때 사용할 디바이스입니다.
	 * @param ResourcePath 텍스처 파일 경로입니다.
	 * 
	 * @throws 
	 * 텍스처 파일 로딩에 실패하면 C++ 표준 예외를 던집니다.
	 * 텍스처 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	Texture2D(ID3D11Device* Device, const std::string& ResourcePath);


	/**
	 * @brief 2D 텍스처 리소스의 가상 소멸자입니다.
	 */
	virtual ~Texture2D();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Texture2D);


	/**
	 * @brief 2D 텍스처 데이터를 얻습니다.
	 * 
	 * @return 2D 텍스처 데이터를 반환합니다.
	 */
	ID3D11Texture2D* GetTexture() { return Texture_; }


	/**
	 * @brief 셰이더에 바인딩할 2D 텍스처 리소스 뷰를 얻습니다.
	 * 
	 * @return 셰이더에 바인딩할 2D 텍스처 리소스 뷰를 반환합니다.
	 */
	ID3D11ShaderResourceView* GetTextureView() { return TextureView_; }


private:
	/**
	 * @brief 텍스처 파일을 로딩합니다.
	 * 
	 * @param ResourcePath 텍스처 파일의 경로입니다.
	 * @param Buffer[out] 텍스처 버퍼입니다.
	 * @param Format[out] 텍스처 픽셀 포멧입니다.
	 * @param Width[out] 텍스처의 가로 크기입니다.
	 * @param Height[out] 텍스처의 세로 크기입니다.
	 * 
	 * @return 텍스처 파일 로딩에 성공하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool LoadTextureFromFile(
		const std::string& ResourcePath, 
		std::vector<uint8_t>& Buffer, 
		int32_t& Format,
		int32_t& Width,
		int32_t& Height
	);


	/**
	 * @brief 텍스처 리소스를 생성합니다.
	 * 
	 * @param Device 텍스처 리소스를 생성할 때 사용할 디바이스입니다.
	 * @param Buffer 텍스처 버퍼입니다.
	 * @param Format 텍스처 픽셀 포멧입니다.
	 * @param Width 텍스처의 가로 크기입니다.
	 * @param Height 텍스처의 세로 크기입니다.
	 * 
	 * @return 텍스처 리소스 생성 결과를 반환합니다. 생성에 성공하면 S_OK, 그렇지 않으면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateTextureResource(ID3D11Device* Device, std::vector<uint8_t>& Buffer, int32_t Format, int32_t Width, int32_t Height);


	/**
	 * @brief 텍스처 크기로부터 해상도를 얻습니다.
	 * 
	 * @param 텍스처의 가로 크기입니다.
	 * @param 텍스처의 세로 크기입니다.
	 * 
	 * @return 텍스처의 해상도를 반환합니다.
	 */
	EResolution GetResolutionFromSize(int32_t Width, int32_t Height);


	/**
	 * @brief 텍스처 버퍼를 해상도를 기준으로 변경합니다.
	 * 
	 * @param OldBuffer 변경하기 이전의 버퍼입니다.
	 * @param OldWidth 변경하기 이전의 버퍼 가로 크기입니다.
	 * @param OldHeight 변경하기 이전의 버퍼 세로 크기입니다.
	 * @param NewBuffer[out] 변경 이후의 버퍼입니다.
	 * @param NewWidth[out] 변경 이후의 버퍼 가로 크기입니다.
	 * @param NewHeight[out] 변경 이후의 버퍼 세로 크기입니다.
	 * 
	 * @return 버퍼 변경에 성공하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool ResizeTextureBuffer(
		std::vector<uint8_t>& OldBuffer, int32_t OldWidth, int32_t OldHeight,
		std::vector<uint8_t>& NewBuffer, int32_t& NewWidth, int32_t& NewHeight
	);


private:
	/**
	 * @brief 2D 텍스처 데이터입니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11texture2d
	 */
	ID3D11Texture2D* Texture_ = nullptr;


	/**
	 * @brief 셰이더에 바인딩할 2D 텍스처 리소스 뷰입니다.
	 */
	ID3D11ShaderResourceView* TextureView_ = nullptr;


	/**
	 * @brief 텍스처의 해상도 크기입니다.
	 */
	static std::array<int32_t, 10> Resolutions_;
};