#pragma once

#include "Macro.h"

#include <memory>
#include <unordered_map>

class Config;
class Texture2D;
class Font;
class Sound;
struct ma_engine;


/**
 * @brief 컨텐트를 로딩하고 관리합니다.
 * 
 * @note 이 클래스는 싱글턴으로 헤더만 추가하면 바로 사용할 수 있습니다.
 */
class ContentManager
{
public:
	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ContentManager);


	/**
	 * @brief ContentManager의 인스턴스를 얻습니다.
	 * 
	 * @return ContentManager의 인스턴스 참조자를 반환합니다.
	 */
	static ContentManager& Get()
	{
		static ContentManager Instance;
		return Instance;
	}


	/**
	 * @brief 텍스처를 로딩합니다.
	 * 
	 * @note 경로를 전달하지 않고, 확장자를 포함한 이름을 인자로 전달해야 합니다.
	 * 
	 * @param Signature 텍스처를 구분하기 위한 시그니처 문자열입니다.
	 * @param FileName 텍스처 파일의 이름입니다. 이때, 이름은 확장자를 포함한 이름입니다.
	 * 
	 * @throws
	 * 텍스처를 구분하는 시그니처 값이 충돌하면 C++ 표준 예외를 던집니다.
	 * 올바른 경로를 전달하지 않으면 C++ 표준 예외를 던집니다.
	 * 텍스처 로딩에 실패하면 C++ 표준 예외를 던집니다.
	 * 텍스처 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 * 
	 * @return 생성한 텍스처 리소스의 참조자를 반환합니다.
	 */
	Texture2D& LoadTexture2D(const std::string& Signature, const std::string& FileName);


	/**
	 * @brief 컨텐츠 메니저가 관리하는 텍스처를 얻습니다.
	 * 
	 * @param Signature 컨텐츠 메니저가 관리하는 텍스처의 시그니처 값입니다.
	 * 
	 * @throws
	 * 시그니처 값에 대응하는 텍스처가 존재하지 않으면 C++ 표준 예외를 던집니다.
	 * 
	 * @return 시그니처 값에 대응하는 텍스처의 참조자를 반환합니다.
	 */
	Texture2D& GetTexture2D(const std::string& Signature);


	/**
	 * @brief 컨텐츠 메니저가 관리하는 텍스처를 삭제합니다.
	 * 
	 * @note 시그니처 값에 대응하는 텍스처가 존재하지 않으면 아무 동작도 수행하지 않습니다.
	 * 
	 * @param Signature 컨텐츠 메니저가 관리하는 텍스처의 시그니처 값입니다.
	 */
	void RemoveTexture2D(const std::string& Signature);


	/**
	 * @brief 트루 타입 폰트를 로딩합니다.
	 * 
	 * @note 경로를 전달하지 않고, 확장자를 포함한 이름을 인자로 전달해야 합니다.
	 * 
	 * @param Signature 폰트를 구분하기 위한 시그니처 문자열입니다.
	 * @param FileName 트루 타입 폰트 파일의 이름입니다. 이때, 이름은 확장자를 포함한 이름입니다. 
	 * @param BeginCodePoint 문자 텍스처 아틀라스의 코드 포인트 시작점입니다.
	 * @param EndCodePoint 문자 텍스처 아틀라스의 코드 포인트 끝점입니다.
	 * @param FontSize 폰트의 크기입니다.
	 * 
	 * @throws
	 * 폰트를 구분하는 시그니처 값이 충돌하면 C++ 표준 예외를 던집니다.
	 * 올바른 경로를 전달하지 않으면 C++ 표준 예외를 던집니다.
	 * 트루 타입 폰트 로딩에 실패하면 C++ 표준 예외를 던집니다.
	 * 폰트 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 * 
	 * @return 생성한 폰트 리소스의 참조자를 반환합니다.
	 */
	Font& LoadFont(const std::string& Signature, const std::string& FileName, int32_t BeginCodePoint, int32_t EndCodePoint, float FontSize);


	/**
	 * @brief 컨텐츠 메니저가 관리하는 폰트를 얻습니다.
	 *
	 * @param Signature 컨텐츠 메니저가 관리하는 폰트의 시그니처 값입니다.
	 *
	 * @throws
	 * 시그니처 값에 대응하는 폰트가 존재하지 않으면 C++ 표준 예외를 던집니다.
	 *
	 * @return 시그니처 값에 대응하는 폰트의 참조자를 반환합니다.
	 */
	Font& GetFont(const std::string& Signature);


	/**
	 * @brief 컨텐츠 메니저가 관리하는 폰트를 삭제합니다.
	 *
	 * @note 시그니처 값에 대응하는 폰트가 존재하지 않으면 아무 동작도 수행하지 않습니다.
	 *
	 * @param Signature 컨텐츠 메니저가 관리하는 폰트의 시그니처 값입니다.
	 */
	void RemoveFont(const std::string& Signature);


	/**
	 * @brief 사운드를 로딩합니다.
	 * 
	 * @note 경로를 전달하지 않고, 확장자를 포함한 이름을 인자로 전달해야 합니다.
	 * 
	 * @param Signature 사운드를 구분하기 위한 시그니처 문자열입니다.
	 * @param FileName 사운드 파일의 이름입니다. 이때, 이름은 확장자를 포함한 이름입니다. 
	 * 
	 * @throws
	 * 사운드를 구분하는 시그니처 값이 충돌하면 C++ 표준 예외를 던집니다.
	 * 올바른 경로를 전달하지 않으면 C++ 표준 예외를 던집니다.
	 * 사운드 로딩에 실패하면 C++ 표준 예외를 던집니다.
	 * 사운드 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 * 
	 * @return 생성한 사운드 리소스의 참조자를 반환합니다.
	 */
	Sound& LoadSound(const std::string& Signature, const std::string& FileName);


	/**
	 * @brief 컨텐츠 메니저가 관리하는 사운드를 얻습니다.
	 *
	 * @param Signature 컨텐츠 메니저가 관리하는 사운드의 시그니처 값입니다.
	 *
	 * @throws
	 * 시그니처 값에 대응하는 사운드가 존재하지 않으면 C++ 표준 예외를 던집니다.
	 *
	 * @return 시그니처 값에 대응하는 사운드의 참조자를 반환합니다.
	 */
	Sound& GetSound(const std::string& Signature);


	/**
	 * @brief 컨텐츠 메니저가 관리하는 사운드를 삭제합니다.
	 *
	 * @note 시그니처 값에 대응하는 사운드가 존재하지 않으면 아무 동작도 수행하지 않습니다.
	 *
	 * @param Signature 컨텐츠 메니저가 관리하는 사운드의 시그니처 값입니다.
	 */
	void RemoveSound(const std::string& Signature);


	/**
	 * @brief 설정 파일을 로딩합니다.
	 * 
	 * @param Signature 사운드를 구분하기 위한 시그니처 문자열입니다.
	 * @param FileName 사운드 파일의 이름입니다. 이때, 이름은 확장자를 포함한 이름입니다.
	 * 
	 * @throws
	 * 설정 오브젝트를 구분하는 시그니처 값이 충돌하면 C++ 표준 예외를 던집니다.
	 * 올바른 경로를 전달하지 않으면 C++ 표준 예외를 던집니다.
	 * 설정 파일 로딩에 실패하면 C++ 표준 예외를 던집니다.
	 *
	 * @return 생성한 설정 오브젝트 리소스의 참조자를 반환합니다.
	 */
	Config& LoadConfig(const std::string& Signature, const std::string& FileName);


	/**
	 * @brief 컨텐츠 메니저가 관리하는 설정 오브젝트를 얻습니다.
	 *
	 * @param Signature 컨텐츠 메니저가 관리하는 설정 오브젝트의 시그니처 값입니다.
	 *
	 * @throws
	 * 시그니처 값에 대응하는 설정 오브젝트가 존재하지 않으면 C++ 표준 예외를 던집니다.
	 *
	 * @return 시그니처 값에 대응하는 설정 오브젝트의 참조자를 반환합니다.
	 */
	Config& GetConfig(const std::string& Signature);


	/**
	 * @brief 컨텐츠 메니저가 관리하는 설정 오브젝트를 삭제합니다.
	 *
	 * @note 시그니처 값에 대응하는 설정 오브젝트가 존재하지 않으면 아무 동작도 수행하지 않습니다.
	 *
	 * @param Signature 컨텐츠 메니저가 관리하는 설정 오브젝트의 시그니처 값입니다.
	 */
	void RemoveConfig(const std::string& Signature);


private:
	/**
	 * @brief 컨텐츠를 관리하는 클래스의 생성자입니다.
	 */
	ContentManager();


	/**
	 * @brief 컨텐츠를 관리하는 클래스의 가상소멸자입니다.
	 */
	virtual ~ContentManager();


private:
	/**
	 * @brief 오디오 리소스 생성을 위한 miniaudio 엔진입니다.
	 */
	std::unique_ptr<ma_engine> AudioEngine_ = nullptr;


	/**
	 * @brief 모든 컨텐츠가 저장되어 있는 경로입니다.
	 */
	std::string ContentPath_;


	/**
	 * @brief 컨텐츠 메니저가 관리하는 텍스처입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<Texture2D>> Textures_;


	/**
	 * @brief 컨텐츠 메니저가 관리하는 폰트입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<Font>> Fonts_;


	/**
	 * @brief 컨텐츠 메니저가 관리하는 사운드입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<Sound>> Sounds_;


	/**
	 * @brief 컨텐츠 메니저가 관리하는 설정 오브젝트입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<Config>> Configs_;
};