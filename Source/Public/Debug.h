#pragma once

#include <Windows.h>
#include <Dbghelp.h>
#include <minidumpapiset.h>


/**
 * @brief ����ȭ ���� ���� ���ܸ� ó���մϴ�.
 *
 * @param ExceptionInfo ���ܰ� �߻��� ������ ���õ� �����Դϴ�.
 *
 * @return EXCEPTION_CONTINUE_SEARCH �⺻ ���� ��ȯ�մϴ�.
 */
LONG WINAPI UnhandledExceptionHandler(struct _EXCEPTION_POINTERS* ExceptionInfo);