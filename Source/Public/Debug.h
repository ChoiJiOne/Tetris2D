#pragma once

#include <Windows.h>
#include <Dbghelp.h>
#include <minidumpapiset.h>


/**
 * @brief 구조화 되지 않은 예외를 처리합니다.
 *
 * @param ExceptionInfo 예외가 발생한 지점의 관련된 정보입니다.
 *
 * @return EXCEPTION_CONTINUE_SEARCH 기본 값을 반환합니다.
 */
LONG WINAPI UnhandledExceptionHandler(struct _EXCEPTION_POINTERS* ExceptionInfo);