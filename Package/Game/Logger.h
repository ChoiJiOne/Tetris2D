#pragma once

#include "Header.h"


namespace Game
{
	// 콘솔 화면에 로그를 출력하는 클래스입니다.
	class Logger
	{
	public:
		// 콘솔 텍스트의 색상 타입입니다.
		enum class EConsoleTextColor : int32_t
		{
			Black       = 0,
			Blue        = 1,
			Green       = 2,
			Aqua        = 3,
			Red         = 4,
			Purple      = 5,
			Yellow      = 6,
			White       = 7,
			Gray        = 8,
			LightBlue   = 9,
			LightGreen  = 10,
			LightAqua   = 11,
			LightRed    = 12,
			LightPurple = 13,
			LightYellow = 14,
			BrightWhite = 15
		};


	public:
		// 콘솔 화면을 초기화합니다.
		static void ClearConsole();


		// 콘솔 화면에 메시지를 출력합니다.
		// 이때, 텍스트의 색상은 흰색입니다.
		//
		// @param InMessage - 콘솔에 출력할 메시지입니다.
		static void Message(const std::string& InMessage);


		// 콘솔 화면에 성공 메시지를 출력합니다.
		// 이때, 텍스트의 색상은 초록색입니다.
		//
		// @param InMessage - 콘솔에 출력할 메시지입니다.
		static void Success(const std::string& InMessage);


		// 콘솔 화면에 경고 메시지를 출력합니다.
		// 이때, 텍스트의 색상은 노란색입니다.
		//
		// @param InMessage - 콘솔에 출력할 메시지입니다.
		static void Warning(const std::string& InMessage);


		// 콘솔 화면에 에러 메시지를 출력합니다.
		// 이때, 텍스트의 색상은 빨간색입니다.
		//
		// @param InMessage - 콘솔에 출력할 메시지입니다.
		static void Error(const std::string& InMessage);


	private:
		// 콘솔의 텍스트 색상을 설정합니다.
		//
		// @param InTextColor - 텍스트 색상값입니다.
		static void SetConsoleTextColor(EConsoleTextColor InTextColor);


		// 콘솔의 커서 보이기 효과를 설정합니다.
		//
		// @param bIsVisible - 콘솔의 커서 보이기 효과 설정값입니다. 참이면 커서가 화면에 보이고 거짓이면 화면에 보이지 않습니다.
		static void SetConsoleCursorVisible(bool bIsVisible);
	};
}