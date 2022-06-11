#include "../Public/MathUtil.h"

LinearColor ColorUtil::Black   = LinearColor(0.0f, 0.0f, 0.0f, 1.0f);
LinearColor ColorUtil::Red     = LinearColor(1.0f, 0.0f, 0.0f, 1.0f);
LinearColor ColorUtil::Green   = LinearColor(0.0f, 1.0f, 0.0f, 1.0f);
LinearColor ColorUtil::Blue    = LinearColor(0.0f, 0.0f, 1.0f, 1.0f);
LinearColor ColorUtil::Yellow  = LinearColor(1.0f, 1.0f, 0.0f, 1.0f);
LinearColor ColorUtil::Magenta = LinearColor(1.0f, 0.0f, 1.0f, 1.0f);
LinearColor ColorUtil::Cyan    = LinearColor(0.0f, 1.0f, 1.0f, 1.0f);
LinearColor ColorUtil::White   = LinearColor(1.0f, 1.0f, 1.0f, 1.0f);

Vec2i operator+(const Vec2i& InLhs, const Vec2i& InRhs)
{
	return Vec2i(InLhs.x + InRhs.x, InLhs.y + InRhs.y);
}

Vec2i operator-(const Vec2i& InLhs, const Vec2i& InRhs)
{
	return Vec2i(InLhs.x - InRhs.x, InLhs.y - InRhs.y);
}

Vec2i operator*(const Vec2i& InLhs, const Vec2i& InRhs)
{
	return Vec2i(InLhs.x * InRhs.x, InLhs.y * InRhs.y);
}

Vec2i operator*(const Vec2i& InVec2i, const int32_t& InScale)
{
	return Vec2i(InVec2i.x * InScale, InVec2i.y * InScale);
}

Vec2i operator*(const int32_t& InScale, const Vec2i& InVec2i)
{
	return Vec2i(InScale * InVec2i.x, InScale * InVec2i.y);
}

Vec2f operator+(const Vec2f& InLhs, const Vec2f& InRhs)
{
	return Vec2f(InLhs.x + InRhs.x, InLhs.y + InRhs.y);
}

Vec2f operator-(const Vec2f& InLhs, const Vec2f& InRhs)
{
	return Vec2f(InLhs.x - InRhs.x, InLhs.y - InRhs.y);
}

Vec2f operator*(const Vec2f& InLhs, const Vec2f& InRhs)
{
	return Vec2f(InLhs.x * InRhs.x, InLhs.y * InRhs.y);
}

Vec2f operator*(const Vec2f& InVec2f, const float& InScale)
{
	return Vec2f(InVec2f.x * InScale, InVec2f.y * InScale);
}

Vec2f operator*(const float& InScale, const Vec2f& InVec2f)
{
	return Vec2f(InScale * InVec2f.x, InScale * InVec2f.y);
}

Vec3i operator+(const Vec3i& InLhs, const Vec3i& InRhs)
{
	return Vec3i(InLhs.x + InRhs.x, InLhs.y + InRhs.y, InLhs.z + InRhs.z);
}

Vec3i operator-(const Vec3i& InLhs, const Vec3i& InRhs)
{
	return Vec3i(InLhs.x - InRhs.x, InLhs.y - InRhs.y, InLhs.z - InRhs.z);
}

Vec3i operator*(const Vec3i& InLhs, const Vec3i& InRhs)
{
	return Vec3i(InLhs.x * InRhs.x, InLhs.y * InRhs.y, InLhs.z * InRhs.z);
}

Vec3i operator*(const Vec3i& InVec3i, const int32_t& InScale)
{
	return Vec3i(InVec3i.x * InScale, InVec3i.y * InScale, InVec3i.z * InScale);
}

Vec3i operator*(const int32_t& InScale, const Vec3i& InVec3i)
{
	return Vec3i(InScale * InVec3i.x, InScale * InVec3i.y, InScale * InVec3i.z);
}

Vec3f operator+(const Vec3f& InLhs, const Vec3f& InRhs)
{
	return Vec3f(InLhs.x + InRhs.x, InLhs.y + InRhs.y, InLhs.z + InRhs.z);
}

Vec3f operator-(const Vec3f& InLhs, const Vec3f& InRhs)
{
	return Vec3f(InLhs.x - InRhs.x, InLhs.y - InRhs.y, InLhs.z - InRhs.z);
}

Vec3f operator*(const Vec3f& InLhs, const Vec3f& InRhs)
{
	return Vec3f(InLhs.x * InRhs.x, InLhs.y * InRhs.y, InLhs.z * InRhs.z);
}

Vec3f operator*(const Vec3f& InVec3f, const float& InScale)
{
	return Vec3f(InVec3f.x * InScale, InVec3f.y * InScale, InVec3f.z * InScale);
}

Vec3f operator*(const float& InScale, const Vec3f& InVec3f)
{
	return Vec3f(InScale * InVec3f.x, InScale * InVec3f.y, InScale * InVec3f.z);
}

Vec4i operator+(const Vec4i& InLhs, const Vec4i& InRhs)
{
	return Vec4i(InLhs.x + InRhs.x, InLhs.y + InRhs.y, InLhs.z + InRhs.z, InLhs.w + InRhs.w);
}

Vec4i operator-(const Vec4i& InLhs, const Vec4i& InRhs)
{
	return Vec4i(InLhs.x - InRhs.x, InLhs.y - InRhs.y, InLhs.z - InRhs.z, InLhs.w - InRhs.w);
}

Vec4i operator*(const Vec4i& InLhs, const Vec4i& InRhs)
{
	return Vec4i(InLhs.x * InRhs.x, InLhs.y * InRhs.y, InLhs.z * InRhs.z, InLhs.w * InRhs.w);
}

Vec4i operator*(const Vec4i& InVec4i, const int32_t& InScale)
{
	return Vec4i(InVec4i.x * InScale, InVec4i.y * InScale, InVec4i.z * InScale, InVec4i.w * InScale);
}

Vec4i operator*(const int32_t& InScale, const Vec4i& InVec4i)
{
	return Vec4i(InScale * InVec4i.x, InScale * InVec4i.y, InScale * InVec4i.z, InScale * InVec4i.w);
}

Vec4f operator+(const Vec4f& InLhs, const Vec4f& InRhs)
{
	return Vec4f(InLhs.x + InRhs.x, InLhs.y + InRhs.y, InLhs.z + InRhs.z, InLhs.w + InRhs.w);
}

Vec4f operator-(const Vec4f& InLhs, const Vec4f& InRhs)
{
	return Vec4f(InLhs.x - InRhs.x, InLhs.y - InRhs.y, InLhs.z - InRhs.z, InLhs.w - InRhs.w);
}

Vec4f operator*(const Vec4f& InLhs, const Vec4f& InRhs)
{
	return Vec4f(InLhs.x * InRhs.x, InLhs.y * InRhs.y, InLhs.z * InRhs.z, InLhs.w * InRhs.w);
}

Vec4f operator*(const Vec4f& InVec4f, const float& InScale)
{
	return Vec4f(InVec4f.x * InScale, InVec4f.y * InScale, InVec4f.z * InScale, InVec4f.w * InScale);
}

Vec4f operator*(const float& InScale, const Vec4f& InVec4f)
{
	return Vec4f(InScale * InVec4f.x, InScale * InVec4f.y, InScale * InVec4f.z, InScale * InVec4f.w);
}