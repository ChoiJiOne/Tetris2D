#pragma once

#include <windows.h>
#include <dbghelp.h>
#include <string>
#include <minidumpapiset.h>


/**
 * @brief 에러 처리를 수행하는 핸들러입니다.
 *
 * @see https://learn.microsoft.com/ko-kr/windows/win32/debug/about-structured-exception-handling
 */
class ErrorHandler
{
public:
	/**
	 * @brief 에러 정보를 설정합니다.
	 *
	 * @param ErrorFile 에러가 발생한 파일 정보입니다.
	 * @param ErrorLine 에러가 발생한 파일 내의 소스 코드 라인입니다.
	 * @param ErrorMessage 에러 메시지입니다.
	 */
	static void SetErrorInfo(const std::string& ErrorFile, const int32_t& ErrorLine, const std::string& ErrorMessage)
	{
		ErrorFileName_ = ErrorFile;
		ErrorLine_ = ErrorLine;
		LastErrorMessage_ = ErrorMessage;
	}


	/**
	 * @brief 에러가 발생한 파일 이름을 얻습니다.
	 *
	 * @return 에러가 발생한 파일 이름을 반환합니다.
	 */
	static const std::string& GetErrorFileName() { return ErrorFileName_; }


	/**
	 * @brief 에러가 발생한 파일의 라인 수를 얻습니다.
	 *
	 * @return 에러가 발생한 파일의 라인 수를 반환합니다.
	 */
	static int32_t GetErrorLine() { return ErrorLine_; }


	/**
	 * @brief 가장 최근에 발생한 에러의 메시지를 얻습니다.
	 *
	 * @return 가장 최근에 발생한 에러의 메시지를 반환합니다.
	 */
	static const std::string& GetLastErrorMessage() { return LastErrorMessage_; }


	/**
	 * @brief 현재의 예외 정보를 기반으로 크래시 덤프 파일을 생성합니다.
	 *
	 * @param ExceptionInfo 발생한 예외 정보에 대한 포인터 값입니다.
	 *
	 * @return 예외에 대한 코드 값을 반환합니다.
	 */
	static LONG GenerateCrashDump(EXCEPTION_POINTERS* ExceptionInfo);


	/**
	 * @brief 현재의 예외 정보를 메시지 박스에 표시합니다.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/winuser/nf-winuser-messageboxa
	 */
	static void ShowErrorMessageBox();


private:
	/**
	 * @brief 가장 최근의 에러 메시지입니다.
	 */
	static std::string LastErrorMessage_;


	/**
	 * @brief 에러가 발생한 경로의 파일 이름입니다.
	 */
	static std::string ErrorFileName_;


	/**
	 * @brief 에러가 발생한 경로의 라인 수입니다.
	 */
	static int32_t ErrorLine_;
};