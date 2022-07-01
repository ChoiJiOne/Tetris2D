#pragma once

// 문자열 관련 기능을 사용하기 위한 헤더 선언을 추가합니다.
#include "GameString.h"


// 강제로 C++ 표준 예외를 반환합니다.
// 
// @param MESSAGE - 예외 발생 시 콘솔 창에 표시될 메시지입니다.
// @throws - C++ 표준 예외를 반환합니다.
#ifndef ENFORCE_THROW_EXCEPTION
#define ENFORCE_THROW_EXCEPTION(MESSAGE)\
{\
    throw std::exception(\
        Game::String::Format("[File] : %s\n[Line] : %d\n[Function] : %s\n[Message] : %s\n", __FILE__, __LINE__, __FUNCTION__, MESSAGE).c_str()\
    );\
}
#endif


// 상태값이 거짓으로 평가되면 C++ 표준 예외를 반환합니다.
// 
// @param CONDITION - 예외를 반환할지 확인할 상태값입니다.
// @param MESSAGE - 예외 발생 시 콘솔 창에 표시될 메시지입니다.
// @throws - C++ 표준 예외를 반환합니다.
#ifndef CHECK_FAILED
#define CHECK_FAILED(CONDITION, MESSAGE)\
{\
    if(!CONDITION)\
    {\
        throw std::exception(\
            Game::String::Format("[File] : %s\n[Line] : %d\n[Function] : %s\n[Message] : %s\n", __FILE__, __LINE__, __FUNCTION__, MESSAGE).c_str()\
        );\
    }\
}
#endif


// SDL API 호출 값이 거짓으로 평가되면 C++ 표준 예외를 반환합니다.
// 
// @param CONDITION - 예외를 반환할지 확인할 상태값입니다.
// @throws - C++ 표준 예외를 반환합니다.
#ifndef CHECK_SDL_FAILED
#define CHECK_SDL_FAILED(CONDITION)\
{\
    if(!CONDITION)\
    {\
        throw std::exception(\
            Game::String::Format("[File] : %s\n[Line] : %d\n[Function] : %s\n[Message] : %s\n", __FILE__, __LINE__, __FUNCTION__, SDL_GetError()).c_str()\
        );\
    }\
}
#endif
