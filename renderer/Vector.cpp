#include "Vector.h"

#include <cmath>
#include <algorithm>

//=============================================================================
// Vector3f
//=============================================================================

ra_vector3f_t::ra_vector3f_t()
	: x{}, y{}, z{} {}

ra_vector3f_t::ra_vector3f_t(
	float f)
	: x{ f }, y{ f }, z{ f } {}

ra_vector3f_t::ra_vector3f_t(
	float x,
	float y,
	float z)
	: x{ x }, y{ y }, z{ z } {}

ra_vector3f_t::ra_vector3f_t(
	const float *f)
	: x{ f[0] }, y{ f[1] }, z{ f[2] } {}

ra_vector3f_t::ra_vector3f_t(
	const ra_vector3f_t &other)
	: x{ other.x }, y{ other.y }, z{ other.z } {}

ra_vector3f_t::ra_vector3f_t(
	ra_vector3f_t &&other) noexcept
{
	Swap(*this, other);
}

ra_vector3f_t::~ra_vector3f_t() {}

ra_vector3f_t & ra_vector3f_t::operator=(
	float f) &
{
	x = f;
	y = f;
	z = f;

	return *this;
}

ra_vector3f_t & ra_vector3f_t::operator=(
	const ra_vector3f_t &other) &
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

ra_vector3f_t & ra_vector3f_t::operator=(
	ra_vector3f_t &&other) & noexcept
{
	Swap(*this, other);

	return *this;
}

ra_vector3f_t ra_vector3f_t::operator+(
	const ra_vector3f_t &other) const
{
	ra_vector3f_t ret;

	ret.x = x + other.x;
	ret.y = y + other.y;
	ret.z = z + other.z;

	return ret;
}

ra_vector3f_t ra_vector3f_t::operator-(
	const ra_vector3f_t &other) const
{
	ra_vector3f_t ret;

	ret.x = x - other.x;
	ret.y = y - other.y;
	ret.z = z - other.z;

	return ret;
}

ra_vector3f_t & ra_vector3f_t::operator+=(
	const ra_vector3f_t &other) &
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

ra_vector3f_t & ra_vector3f_t::operator-=(
	const ra_vector3f_t &other) &
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

ra_vector3f_t & ra_vector3f_t::operator*=(
	float f) &
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

ra_vector3f_t & ra_vector3f_t::operator/=(
	float f) &
{
	x /= f;
	y /= f;
	z /= f;

	return *this;
}

float ra_vector3f_t::getX() const
{
	return x;
}

float ra_vector3f_t::getY() const
{
	return y;
}

float ra_vector3f_t::getZ() const
{
	return z;
}

ra_vector3f_t operator*(
	const ra_vector3f_t &v,
	float f)
{
	ra_vector3f_t ret;

	ret.x = v.x * f;
	ret.y = v.y * f;
	ret.z = v.z * f;

	return ret;
}

ra_vector3f_t operator*(
	float f,
	const ra_vector3f_t &v)
{
	ra_vector3f_t ret;

	ret.x = v.x * f;
	ret.y = v.y * f;
	ret.z = v.z * f;

	return ret;
}

ra_vector3f_t operator/(
	const ra_vector3f_t &v,
	float f)
{
	ra_vector3f_t ret;

	ret.x = v.x / f;
	ret.y = v.y / f;
	ret.z = v.z / f;

	return ret;
}

float Length(const ra_vector3f_t& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float Dot(const ra_vector3f_t& v1, const ra_vector3f_t& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

ra_vector3f_t Cross(const ra_vector3f_t& v1, const ra_vector3f_t& v2)
{
	ra_vector3f_t ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.z - v1.y * v2.x;

	return ret;
}

ra_vector3f_t Normalized(const ra_vector3f_t& v1)
{
	ra_vector3f_t ret = v1;

	float length = Length(v1);

	ret.x /= length;
	ret.y /= length;
	ret.z /= length;

	return ret;
}

ra_vector3f_t Multiply(const ra_vector3f_t& v, float f)
{
	ra_vector3f_t ret = v;

	ret.x *= f;
	ret.y *= f;
	ret.z *= f;

	return ret;
}

ra_vector3f_t Add(const ra_vector3f_t& v1, const ra_vector3f_t& v2)
{
	ra_vector3f_t ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;

	return ret;
}

ra_vector3f_t Add(const ra_vector3f_t& v1, float f)
{
	ra_vector3f_t ret;

	ret.x = v1.x + f;
	ret.y = v1.y + f;
	ret.z = v1.z + f;

	return ret;
}

ra_vector3f_t Lerp(const ra_vector3f_t& a, const ra_vector3f_t& b, float t)
{
	return a + (b - a) * t;
}

void Swap(
	ra_vector3f_t &first,
	ra_vector3f_t &second) noexcept
{
	std::swap(first.x, second.x);
	std::swap(first.y, second.y);
	std::swap(first.z, second.z);
}


//=============================================================================
// Vector4f
//=============================================================================

ra_vector4f_t::ra_vector4f_t()
	: x{}, y{}, z{}, w{} {}

ra_vector4f_t::ra_vector4f_t(
	float f)
	: x{ f }, y{ f }, z{ f }, w{ f } {}

ra_vector4f_t::ra_vector4f_t(
	float x,
	float y,
	float z,
	float w)
	: x{ x }, y{ y }, z{ z }, w{ w } {}

ra_vector4f_t::ra_vector4f_t(
	const float *f)
	: x{ f[0] }, y{ f[1] }, z{ f[2] }, w{ f[3] } {}

ra_vector4f_t::ra_vector4f_t(
	const ra_vector4f_t &other)
	: x{ other.x }, y{ other.y }, z{ other.z }, w{ other.w } {}

ra_vector4f_t::ra_vector4f_t(
	ra_vector4f_t &&other) noexcept
{
	Swap(*this, other);
}

ra_vector4f_t::~ra_vector4f_t()
{}

ra_vector4f_t & ra_vector4f_t::operator=(
	float f) &
{
	x = f;
	y = f;
	z = f;
	w = f;

	return *this;
}

ra_vector4f_t & ra_vector4f_t::operator=(
	const ra_vector4f_t &other) &
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

ra_vector4f_t & ra_vector4f_t::operator=(
	ra_vector4f_t &&other) & noexcept
{
	Swap(*this, other);

	return *this;
}

ra_vector4f_t ra_vector4f_t::operator-(
	const ra_vector4f_t &other) const
{
	ra_vector4f_t ret;

	ret.x = x - other.x;
	ret.y = y - other.y;
	ret.z = z - other.z;
	ret.w = w - other.w;

	return ret;
}

ra_vector4f_t & ra_vector4f_t::operator+=(
	const ra_vector4f_t &other) &
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

ra_vector4f_t & ra_vector4f_t::operator-=(
	const ra_vector4f_t &other) &
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

ra_vector4f_t & ra_vector4f_t::operator*=(
	float f) &
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
}

ra_vector4f_t & ra_vector4f_t::operator/=(
	float f) &
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;

	return *this;
}

float ra_vector4f_t::getX() const
{
	return x;
}

float ra_vector4f_t::getY() const
{
	return y;
}

float ra_vector4f_t::getZ() const
{
	return z;
}

float ra_vector4f_t::getW() const
{
	return w;
}

ra_vector4f_t ra_vector4f_t::operator+(
	const ra_vector4f_t &other) const
{
	ra_vector4f_t ret;

	ret.x = x + other.x;
	ret.y = y + other.y;
	ret.z = z + other.z;
	ret.w = w + other.w;

	return ret;
}

ra_vector4f_t operator*(
	const ra_vector4f_t &v,
	float f)
{
	ra_vector4f_t ret;

	ret.x = v.x * f;
	ret.y = v.y * f;
	ret.z = v.z * f;
	ret.w = v.w * f;

	return ret;
}

ra_vector4f_t operator*(
	float f,
	const ra_vector4f_t &v)
{
	ra_vector4f_t ret;

	ret.x = v.x * f;
	ret.y = v.y * f;
	ret.z = v.z * f;
	ret.w = v.w * f;

	return ret;
}

ra_vector4f_t operator/(
	const ra_vector4f_t &v,
	float f)
{
	ra_vector4f_t ret;

	ret.x = v.x / f;
	ret.y = v.y / f;
	ret.z = v.z / f;
	ret.w = v.w / f;

	return ret;
}

float Length(const ra_vector4f_t& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float Dot(const ra_vector4f_t& v1, const ra_vector4f_t& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

ra_vector4f_t Cross(const ra_vector4f_t& v1, const ra_vector4f_t& v2)
{
	ra_vector4f_t ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.z - v1.y * v2.x;
	ret.w = 0;

	return ret;
}

ra_vector4f_t Normalized(const ra_vector4f_t& v1)
{
	ra_vector4f_t ret = v1;

	float length = Length(v1);

	ret.x /= length;
	ret.y /= length;
	ret.z /= length;
	ret.w /= length;

	return ret;
}

ra_vector4f_t Multiply(const ra_vector4f_t& v, float f)
{
	ra_vector4f_t ret = v;

	ret.x *= f;
	ret.y *= f;
	ret.z *= f;
	ret.w *= f;

	return ret;
}

ra_vector4f_t Add(const ra_vector4f_t& v1, const ra_vector4f_t& v2)
{
	ra_vector4f_t ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	ret.w = v1.w + v2.w;

	return ret;
}

ra_vector4f_t Add(const ra_vector4f_t& v1, float f)
{
	ra_vector4f_t ret;

	ret.x = v1.x + f;
	ret.y = v1.y + f;
	ret.z = v1.z + f;
	ret.w = v1.w + f;

	return ret;
}

ra_vector4f_t Lerp(const ra_vector4f_t& a, const ra_vector4f_t& b, float t)
{
	return a + (b - a) * t;
}

void Swap(
	ra_vector4f_t &first,
	ra_vector4f_t &second) noexcept
{
	std::swap(first.x, second.x);
	std::swap(first.y, second.y);
	std::swap(first.z, second.z);
	std::swap(first.w, second.w);
}
