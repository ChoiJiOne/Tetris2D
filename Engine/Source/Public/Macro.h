#pragma once

#include "ErrorHandler.h"


/**
 * @brief Ŭ������ ���� ������ �� ���� �����ڸ� ������� ���ϵ��� �����մϴ�.
 *
 * @note �� ��ũ�θ� ������� �ʴ� Ŭ������ �ݵ�� ���������� ���� �����ڿ� ���� �����ڸ� �����ؾ� �մϴ�.
 *
 * @param CLASS - ���� ������ �� ���� �����ڸ� ������ Ŭ�����Դϴ�.
 */
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(CLASS)\
CLASS(CLASS&&) = delete;\
CLASS(const CLASS&) = delete;\
CLASS& operator=(CLASS&&) = delete;\
CLASS& operator=(const CLASS&) = delete;
#endif


 /**
 * @brief �򰡽��� �˻��ϰ� �������� �򰡵Ǹ� C++ ǥ�� ���ܸ� �����ϴ�.
 *
 * @param EXPRESSION �˻��� �򰡽��Դϴ�.
 * @param MESSAGE �򰡽��� �������� �򰡵� ����� �޽����Դϴ�.
 *
 * @throws �򰡽��� �������� �򰡵� ���, C++ ǥ�� ���ܸ� ������ ũ���� ������ �����մϴ�.
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