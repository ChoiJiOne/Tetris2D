#pragma once


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