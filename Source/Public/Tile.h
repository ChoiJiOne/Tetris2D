#pragma once

#include "Vector.hpp"


/**
 * @brief 2D Ÿ���Դϴ�.
 */
class Tile
{
public:
	/**
	 * @brief Ÿ���� �����Դϴ�.
	 */
	enum class EState
	{
		NONE  = 0,
		EMPTY = 1,
		FILL  = 2,
		WALL  = 3
	};


	/**
	 * @brief Ÿ���� �����Դϴ�.
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
	 * @brief 2D Ÿ���� �⺻ �������Դϴ�.
	 * 
	 * @note �� �����ڸ� �̿��� ���, �޼��带 ȣ���ؼ� ������ �ʱ�ȭ�� �������־�� �մϴ�.
	 */
	Tile()
		: PositionInMap_(Vec2i(0, 0))
		, State_(EState::NONE)
		, Color_(EColor::NONE) {}


	/**
	 * @brief 2D Ÿ���� �������Դϴ�.
	 * 
	 * @param PositionInMap Ÿ�ϸ� ���� Ÿ���� ��ġ�Դϴ�.
	 * @param State Ÿ���� �����Դϴ�.
	 * @param Color Ÿ���� �����Դϴ�.
	 */
	Tile(const Vec2i& PositionInMap, const EState& State, const EColor Color) noexcept
		: PositionInMap_(PositionInMap)
		, State_(State)
		, Color_(Color) {}


	/**
	 * @brief 2D Ÿ���� ���� �������Դϴ�.
	 * 
	 * @param Instance ���縦 ������ ��ü�Դϴ�.
	 */
	Tile(Tile&& Instance) noexcept
		: PositionInMap_(Instance.PositionInMap_)
		, State_(Instance.State_)
		, Color_(Instance.Color_) {}


	/**
	 * @brief 2D Ÿ���� ���� �������Դϴ�.
	 *
	 * @param Instance ���縦 ������ ��ü�Դϴ�.
	 */
	Tile(const Tile& Instance) noexcept
		: PositionInMap_(Instance.PositionInMap_)
		, State_(Instance.State_)
		, Color_(Instance.Color_) {}


	/**
	 * @brief 2D Ÿ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tile() = default;


	/**
	 * @brief 2D Ÿ���� ���� �������Դϴ�.
	 * 
	 * @param Instance ���縦 ������ ��ü�Դϴ�.
	 * 
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * @brief 2D Ÿ���� ���� �������Դϴ�.
	 *
	 * @param Instance ���縦 ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
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
	 * @brief 2D Ÿ���� �� �ǿ����ڰ� ��ġ�ϴ��� Ȯ���մϴ�.
	 * 
	 * @param Instance ��ġ�ϴ��� Ȯ���� �ǿ������Դϴ�.
	 * 
	 * @return �� �ǿ����ڰ� ��ġ�ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(Tile&& Instance)
	{
		return (PositionInMap_ == Instance.PositionInMap_) 
			&& (State_ == Instance.State_) 
			&& (Color_ == Instance.Color_);
	}


	/**
	 * @brief 2D Ÿ���� �� �ǿ����ڰ� ��ġ�ϴ��� Ȯ���մϴ�.
	 *
	 * @param Instance ��ġ�ϴ��� Ȯ���� �ǿ������Դϴ�.
	 *
	 * @return �� �ǿ����ڰ� ��ġ�ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool operator==(const Tile& Instance)
	{
		return (PositionInMap_ == Instance.PositionInMap_)
			&& (State_ == Instance.State_)
			&& (Color_ == Instance.Color_);
	}


	/**
	 * @brief 2D Ÿ���� �� �ǿ����ڰ� ��ġ���� �ʴ��� Ȯ���մϴ�.
	 *
	 * @param Instance ��ġ���� �ʴ��� Ȯ���� �ǿ������Դϴ�.
	 *
	 * @return �� �ǿ����ڰ� ��ġ���� ������ true, ��ġ�ϸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(Tile&& Instance)
	{
		return (PositionInMap_ != Instance.PositionInMap_)
			|| (State_ != Instance.State_)
			|| (Color_ != Instance.Color_);
	}


	/**
	 * @brief 2D Ÿ���� �� �ǿ����ڰ� ��ġ���� �ʴ��� Ȯ���մϴ�.
	 *
	 * @param Instance ��ġ���� �ʴ��� Ȯ���� �ǿ������Դϴ�.
	 *
	 * @return �� �ǿ����ڰ� ��ġ���� ������ true, ��ġ�ϸ� false�� ��ȯ�մϴ�.
	 */
	bool operator!=(const Tile& Instance)
	{
		return (PositionInMap_ != Instance.PositionInMap_)
			|| (State_ != Instance.State_)
			|| (Color_ != Instance.Color_);
	}


	/**
	 * @brief 2D Ÿ�ϸ� ���� ��ġ�� �����մϴ�.
	 * 
	 * @param PositionInMap ������ ��ġ�Դϴ�.
	 */
	void SetPositionInMap(const Vec2i& PositionInMap) { PositionInMap_ = PositionInMap; }


	/**
	 * @brief 2D Ÿ�ϸ� ���� ��ġ�� ����ϴ�.
	 * 
	 * @return 2D Ÿ�ϸ� ���� ��ġ�� ��ȯ�մϴ�.
	 */
	Vec2i GetPositionInMap() const { return PositionInMap_; }


	/**
	 * @brief 2D Ÿ���� ���¸� �����մϴ�.
	 * 
	 * @param State ������ �����Դϴ�.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief 2D Ÿ���� ���¸� ����ϴ�.
	 * 
	 * @return 2D Ÿ���� ���¸� ����ϴ�.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief 2D Ÿ���� ������ �����մϴ�.
	 * 
	 * @param Color ������ �����Դϴ�.
	 */
	void SetColor(const EColor& Color) { Color_ = Color; }


	/**
	 * @brief 2D Ÿ���� ������ ����ϴ�.
	 * 
	 * @return 2D Ÿ���� ������ ��ȯ�մϴ�.
	 */
	EColor GetColor() const { return Color_; }


private:
	/**
	 * @brief 2D Ÿ�ϸ� ���� ��ġ�Դϴ�.
	 */
	Vec2i PositionInMap_;


	/**
	 * @brief Ÿ���� �����Դϴ�.
	 */
	EState State_ = EState::NONE;


	/**
	 * @brief Ÿ���� �����Դϴ�.
	 */
	EColor Color_ = EColor::NONE;
};