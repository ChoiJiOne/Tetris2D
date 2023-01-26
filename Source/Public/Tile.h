#pragma once

#include "Vector.hpp"


/**
 * @brief 2D 타일입니다.
 */
class Tile
{
public:
	/**
	 * @brief 타일의 상태입니다.
	 */
	enum class EState
	{
		NONE  = 0,
		EMPTY = 1,
		FILL  = 2,
		WALL  = 3
	};


	/**
	 * @brief 타일의 색상입니다.
	 */
	enum class EColor
	{
		NONE   = 0,
		BLUE   = 1,
		CYAN   = 2,
		GRAY   = 3,
		GREEN  = 4,
		ORANGE = 5,
		PINK   = 6,
		PURPLE = 7,
		RED    = 8,
		YELLOW = 9
	};


public:
	/**
	 * @brief 2D 타일의 기본 생성자입니다.
	 * 
	 * @note 이 생성자를 이용할 경우, 메서드를 호출해서 적절히 초기화를 수행해주어야 합니다.
	 */
	Tile()
		: PositionInMap_(Vec2i(0, 0))
		, State_(EState::NONE)
		, Color_(EColor::NONE) {}


	/**
	 * @brief 2D 타일의 생성자입니다.
	 * 
	 * @param PositionInMap 타일맵 상의 타일의 위치입니다.
	 * @param State 타일의 상태입니다.
	 * @param Color 타일의 색상입니다.
	 */
	Tile(const Vec2i& PositionInMap, const EState& State, const EColor Color) noexcept
		: PositionInMap_(PositionInMap)
		, State_(State)
		, Color_(Color) {}


	/**
	 * @brief 2D 타일의 복사 생성자입니다.
	 * 
	 * @param Instance 복사를 수행할 객체입니다.
	 */
	Tile(Tile&& Instance) noexcept
		: PositionInMap_(Instance.PositionInMap_)
		, State_(Instance.State_)
		, Color_(Instance.Color_) {}


	/**
	 * @brief 2D 타일의 복사 생성자입니다.
	 *
	 * @param Instance 복사를 수행할 객체입니다.
	 */
	Tile(const Tile& Instance) noexcept
		: PositionInMap_(Instance.PositionInMap_)
		, State_(Instance.State_)
		, Color_(Instance.Color_) {}


	/**
	 * @brief 2D 타일의 가상 소멸자입니다.
	 */
	virtual ~Tile() = default;


	/**
	 * @brief 2D 타일의 대입 연산자입니다.
	 * 
	 * @param Instance 복사를 수행할 객체입니다.
	 * 
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Tile& operator=(Tile&& Instance) noexcept
	{
		if (this == &Instance) return *this;

		PositionInMap_ = Instance.PositionInMap_;
		State_ = Instance.State_;
		Color_ = Instance.Color_;

		return *this;
	}


	/**
	 * @brief 2D 타일의 대입 연산자입니다.
	 *
	 * @param Instance 복사를 수행할 객체입니다.
	 *
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Tile& operator=(const Tile& Instance) noexcept
	{
		if (this == &Instance) return *this;

		PositionInMap_ = Instance.PositionInMap_;
		State_ = Instance.State_;
		Color_ = Instance.Color_;

		return *this;
	}


	/**
	 * @brief 2D 타일의 두 피연산자가 일치하는지 확인합니다.
	 * 
	 * @param Instance 일치하는지 확인할 피연산자입니다.
	 * 
	 * @return 두 피연산자가 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(Tile&& Instance)
	{
		return (PositionInMap_ == Instance.PositionInMap_) 
			&& (State_ == Instance.State_) 
			&& (Color_ == Instance.Color_);
	}


	/**
	 * @brief 2D 타일의 두 피연산자가 일치하는지 확인합니다.
	 *
	 * @param Instance 일치하는지 확인할 피연산자입니다.
	 *
	 * @return 두 피연산자가 일치하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool operator==(const Tile& Instance)
	{
		return (PositionInMap_ == Instance.PositionInMap_)
			&& (State_ == Instance.State_)
			&& (Color_ == Instance.Color_);
	}


	/**
	 * @brief 2D 타일의 두 피연산자가 일치하지 않는지 확인합니다.
	 *
	 * @param Instance 일치하지 않는지 확인할 피연산자입니다.
	 *
	 * @return 두 피연산자가 일치하지 않으면 true, 일치하면 false를 반환합니다.
	 */
	bool operator!=(Tile&& Instance)
	{
		return (PositionInMap_ != Instance.PositionInMap_)
			|| (State_ != Instance.State_)
			|| (Color_ != Instance.Color_);
	}


	/**
	 * @brief 2D 타일의 두 피연산자가 일치하지 않는지 확인합니다.
	 *
	 * @param Instance 일치하지 않는지 확인할 피연산자입니다.
	 *
	 * @return 두 피연산자가 일치하지 않으면 true, 일치하면 false를 반환합니다.
	 */
	bool operator!=(const Tile& Instance)
	{
		return (PositionInMap_ != Instance.PositionInMap_)
			|| (State_ != Instance.State_)
			|| (Color_ != Instance.Color_);
	}


	/**
	 * @brief 2D 타일맵 상의 위치를 설정합니다.
	 * 
	 * @param PositionInMap 설정할 위치입니다.
	 */
	void SetPositionInMap(const Vec2i& PositionInMap) { PositionInMap_ = PositionInMap; }


	/**
	 * @brief 2D 타일맵 상의 위치를 얻습니다.
	 * 
	 * @return 2D 타일맵 상의 위치를 반환합니다.
	 */
	Vec2i GetPositionInMap() const { return PositionInMap_; }


	/**
	 * @brief 2D 타일의 상태를 설정합니다.
	 * 
	 * @param State 설정할 상태입니다.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief 2D 타일의 상태를 얻습니다.
	 * 
	 * @return 2D 타일의 상태를 얻습니다.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief 2D 타일의 색상을 설정합니다.
	 * 
	 * @param Color 설정할 색상입니다.
	 */
	void SetColor(const EColor& Color) { Color_ = Color; }


	/**
	 * @brief 2D 타일의 색상을 얻습니다.
	 * 
	 * @return 2D 타일의 색상을 반환합니다.
	 */
	EColor GetColor() const { return Color_; }


private:
	/**
	 * @brief 2D 타일맵 상의 위치입니다.
	 */
	Vec2i PositionInMap_;


	/**
	 * @brief 타일의 상태입니다.
	 */
	EState State_ = EState::NONE;


	/**
	 * @brief 타일의 색상입니다.
	 */
	EColor Color_ = EColor::NONE;
};