#pragma once

#include "ISystem.h"

#include <d3d11.h>
#include <unordered_map>

class Window;


/**
 * @brief 렌더링 처리를 수행하는 시스템입니다.
 */
class RenderSystem : public ISystem
{
public:
	/**
	 * 
	 */
	RenderSystem();


	/**
	 * 
	 */
	virtual ~RenderSystem();


	/**
	 * 
	 */
	DISALLOW_COPY_AND_ASSIGN(RenderSystem);

};