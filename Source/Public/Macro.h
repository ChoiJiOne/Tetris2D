#pragma once


/**
 * @brief COM ���ҽ��� �Ҵ� �����մϴ�.
 *
 * @param X �Ҵ� ������ COM ���ҽ��Դϴ�.
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