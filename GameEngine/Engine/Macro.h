#pragma once

#include "StringHelper.h"


/**
 * 평가식이 거짓으로 평가되면 C++ 표준 예외를 던집니다.
 * @param EXPRESSION - 평가식입니다.
 * @param MESSAGE - 평가식이 거짓으로 평가될 경우의 메시지입니다.
 * @throws 평가식이 거짓으로 평가될 경우, C++ 표준 예외를 던집니다.
 */
#ifndef CHECK
#define CHECK(EXPRESSION, MESSAGE)\
{\
	if(!EXPRESSION)\
	{\
		throw std::exception(\
			Game::StringHelper::Format(\
				"[File] : %s\n[Line] : %d\n[Function] : %s\n[Message] : %s\n",\
				 __FILE__, __LINE__, __FUNCTION__, MESSAGE).c_str()\
		);\
	}\
}
#endif


/**
 * 강제로 C++ 표준 예외를 던집니다.
 * @param MESSAGE - 예외가 발생했을 때의 메시지입니다.
 * @throws C++ 표준 예외를 던집니다.
 */
#ifndef ENFORCE_THROW_EXCEPTION
#define ENFORCE_THROW_EXCEPTION(MESSAGE)\
{\
	throw std::exception(\
		Game::StringHelper::Format(\
			"[File] : %s\n[Line] : %d\n[Function] : %s\n[Message] : %s\n",\
				__FILE__, __LINE__, __FUNCTION__, MESSAGE).c_str()\
	);\
}
#endif