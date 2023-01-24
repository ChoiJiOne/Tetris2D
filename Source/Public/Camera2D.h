#pragma once

#include "Math.hpp"


/**
 * @brief 2D World에서 이동 가능한 카메라입니다.
 */
class Camera2D
{
public:
	/**
	 * @brief 2D World에서 이동 가능한 카메라의 생성자입니다.
	 * 
	 * @param Position 2D World의 카메라 위치입니다.
	 * @param Width 카메라의 가로 크기입니다.
	 * @param Height 카메라의 세로 크기입니다.
	 * @param Rotate 카메라의 이동 방향입니다. 이때 회전각은 라디안 각도 기준입니다.
	 * @param Velocity 카메라의 이동 속력입니다.
	 */
	Camera2D(
		const Vec2f& Position,
		const float& Width,
		const float& Height,
		const float& Rotate = 0.0f,
		const float& Velocity = 0.0f
	) : Position_(Position), 
		Width_(Width), 
		Height_(Height), 
		Rotate_(Rotate), 
		Velocity_(Velocity) {}


	/**
	 * @brief 2D World의 카메라 복사 생성자입니다.
	 *
	 * @param Instance 복사할 카메라 인스턴스입니다.
	 */
	Camera2D(Camera2D&& Instance) noexcept
		: Position_(Instance.Position_)
		, Width_(Instance.Width_)
		, Height_(Instance.Height_)
		, Rotate_(Instance.Rotate_)
		, Velocity_(Instance.Velocity_) {}


	/**
	 * @brief 2D World의 카메라 복사 생성자입니다.
	 *
	 * @param Instance 복사할 카메라 인스턴스입니다.
	 */
	Camera2D(const Camera2D& Instance) noexcept
		: Position_(Instance.Position_)
		, Width_(Instance.Width_)
		, Height_(Instance.Height_)
		, Rotate_(Instance.Rotate_)
		, Velocity_(Instance.Velocity_) {}


	/**
	 * @brief 2D World의 가상 소멸자입니다.
	 */
	virtual ~Camera2D() {}


	/**
	 * 2D World 카메라의 대입 연산자입니다..
	 *
	 * @param Instance 복사할 카메라 인스턴스입니다.
	 *
	 * @param 대입한 카메라의 참조자를 반환합니다.
	 */
	Camera2D& operator=(Camera2D&& Instance) noexcept
	{
		if (this == &Instance) return *this;

		Position_ = Instance.Position_;
		Width_ = Instance.Width_;
		Height_ = Instance.Height_;
		Rotate_ = Instance.Rotate_;
		Velocity_ = Instance.Velocity_;

		return *this;
	}


	/**
	 * 2D World 카메라의 대입 연산자입니다..
	 *
	 * @param Instance 복사할 카메라 인스턴스입니다.
	 *
	 * @param 대입한 카메라의 참조자를 반환합니다.
	 */
	Camera2D& operator=(const Camera2D& Instance) noexcept
	{
		if (this == &Instance) return *this;

		Position_ = Instance.Position_;
		Width_ = Instance.Width_;
		Height_ = Instance.Height_;
		Rotate_ = Instance.Rotate_;
		Velocity_ = Instance.Velocity_;

		return *this;
	}


	/**
	 * @brief 2D World의 카메라 위치를 얻습니다.
	 *
	 * @return 2D World의 카메라 위치를 반환합니다.
	 */
	Vec2f GetPosition() const { return Position_; }


	/**
	 * @brief 2D World의 카메라 위치를 설정합니다.
	 *
	 * @param Position 설정할 카메라 위치입니다.
	 */
	void SetPosition(const Vec2f& Position) { Position_ = Position; }


	/**
	 * @brief 2D World의 카메라 가로 크기를 얻습니다.
	 *
	 * @return 2D World의 카메라 가로 크기를 반환합니다.
	 */
	float GetWidth() const { return Width_; }


	/**
	 * @brief 2D World의 카메라 가로 크기를 설정합니다.
	 *
	 * @param Width 설정할 카메라의 가로 크기입니다.
	 */
	void SetWidth(const float& Width) { Width_ = Width; }


	/**
	 * @brief 2D World의 카메라 세로 크기를 얻습니다.
	 *
	 * @return 2D World의 카메라 세로 크기를 반환합니다.
	 */
	float GetHeight() const { return Height_; }


	/**
	 * @brief 2D World의 카메라 세로 크기를 설정합니다.
	 *
	 * @param Height 설정할 카메라의 세로 크기입니다.
	 */
	void SetHeight(const float& Height) { Height_ = Height; }


	/**
	 * @brief 2D World의 카메라 가로, 세로 크기를 얻습니다.
	 *
	 * @param Width[out] 2D World의 카메라 가로 크기입니다.
	 * @param Height[out] 2D World의 카메라 세로 크기입니다.
	 */
	template <typename T>
	void GetSize(T& Width, T& Height)
	{
		Width = static_cast<T>(Width_);
		Height = static_cast<T>(Height_);
	}


	/**
	 * @brief 2D World의 카메라 가로, 세로 크기를 설정합니다.
	 *
	 * @parma Width 설정할 카메라의 가로 크기입니다.
	 * @param Height 설정할 카메라의 세로 크기입니다.
	 */
	template <typename T>
	void SetSize(const T& Width, const T& Height)
	{
		Width_ = static_cast<float>(Width);
		Height_ = static_cast<float>(Height);
	}


	/**
	 * @brief 2D World의 카메라 방향 각도를 얻습니다.
	 *
	 * @return 2D World의 카메라 방향 각도를 반환합니다.
	 */
	float GetRotate() const { return Rotate_; }


	/**
	 * @brief 2D World의 카메라 방향 각도를 설정합니다.
	 *
	 * @note 각도는 라디안 각도 기준입니다.
	 * 
	 * @param Rotate 설정할 카메라의 방향 각도입니다.
	 */
	void SetRotate(const float& Rotate) { Rotate_ = Rotate; }


	/**
	 * @brief 2D World의 카메라의 속력을 얻습니다.
	 *
	 * @return 2D World의 카메라의 속력을 반환합니다.
	 */
	float GetVelocity() const { return Velocity_; }


	/**
	 * @brief 2D World의 카메라의 속력을 설정합니다.
	 *
	 * @param Velocity 설정할 카메라의 속력입니다.
	 */
	void SetVelocity(const float& Velocity) { Velocity_ = Velocity; }


	/**
	 * @brief 초단위 델타 시간값 만큼 카메라를 움직입니다.
	 *
	 * @param DeltaSeconds 카메라를 움직일 초단위 델타 시간 값입니다.
	 */
	void Move(float DeltaSeconds);


private:
	/**
	 * @biref 2D 월드 상의 카메라 현재 위치입니다.
	 */
	Vec2f Position_;


	/**
	 * @biref 카메라의 가로 크기입니다.
	 */
	float Width_ = 0.0f;


	/**
	 * @biref 카메라의 세로 크기입니다.
	 */
	float Height_ = 0.0f;


	/**
	 * @biref 카메라의 이동 방향 각입니다.
	 */
	float Rotate_ = 0.0f;


	/**
	 * @biref 카메라의 이동 속력입니다.
	 */
	float Velocity_ = 0.0f;
};