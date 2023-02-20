#pragma once

#include "ErrorHandler.h"


/**
 * @brief 클래스의 복사 생성자 및 대입 연산자를 사용하지 못하도록 삭제합니다.
 *
 * @note 이 매크로를 사용하지 않는 클래스는 반드시 명시적으로 대입 연산자와 복사 생성자를 정의해야 합니다.
 *
 * @param CLASS - 복사 생성자 및 대입 연산자를 삭제할 클래스입니다.
 */
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(CLASS)\
CLASS(CLASS&&) = delete;\
CLASS(const CLASS&) = delete;\
CLASS& operator=(CLASS&&) = delete;\
CLASS& operator=(const CLASS&) = delete;
#endif


 /**
 * @brief 평가식을 검사하고 거짓으로 평가되면 C++ 표준 예외를 던집니다.
 *
 * @param EXPRESSION 검사할 평가식입니다.
 * @param MESSAGE 평가식이 거짓으로 평가될 경우의 메시지입니다.
 *
 * @throws 평가식이 거짓으로 평가될 경우, C++ 표준 예외를 던지고 크래시 덤프를 생성합니다.
 */
#ifndef CHECK
#define CHECK(EXPRESSION, MESSAGE)\
{\
	if(!EXPRESSION)\
	{\
		ErrorHandler::SetErrorInfo(__FILE__, __LINE__, MESSAGE);\
		throw std::exception();\
	}\
}
#endif


/**
 * @brief COM 리소스를 할당 해제합니다.
 *
 * @param X 할당 해제할 COM 리소스입니다.
 */
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(X)\
{\
	if(X)\
	{\
		X->Release();\
		X = nullptr;\
	}\
}
#endif