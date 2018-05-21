#pragma once

// TODO: Vector2f

//=============================================================================
// Vector3f
//=============================================================================

class ra_vector3f_t
{
public:

	// Constructors
	ra_vector3f_t();
	explicit ra_vector3f_t(float f);
	ra_vector3f_t(float x, float y, float z);
	explicit ra_vector3f_t(const float *f);
	ra_vector3f_t(const ra_vector3f_t& other);
	explicit ra_vector3f_t(ra_vector3f_t&& other) noexcept;

	// Destructor

	virtual ~ra_vector3f_t();

	// Assignment operators

	ra_vector3f_t& operator=(float f) &;
	ra_vector3f_t& operator=(const ra_vector3f_t& other) &;
	ra_vector3f_t& operator=(ra_vector3f_t&& other) & noexcept;

	// Arithmetic operators

	ra_vector3f_t operator+(const ra_vector3f_t& other) const;
	ra_vector3f_t operator-(const ra_vector3f_t& other) const;

	friend ra_vector3f_t operator*(const ra_vector3f_t& v, float f);
	friend ra_vector3f_t operator*(float f, const ra_vector3f_t& v);

	friend ra_vector3f_t operator/(const ra_vector3f_t& v, float f);

	// Logical Operators

	// Compound operators

	ra_vector3f_t& operator+=(const ra_vector3f_t& other) &;
	ra_vector3f_t& operator-=(const ra_vector3f_t& other) &;

	ra_vector3f_t& operator*=(float f) &;
	ra_vector3f_t& operator/=(float f) &;

	// Member access

	float getX() const;
	float getY() const;
	float getZ() const;

	// Stream operators

	// Functions
	friend float Length(const ra_vector3f_t& v);
	friend float Dot(const ra_vector3f_t& v1, const ra_vector3f_t& v2);
	friend ra_vector3f_t Cross(const ra_vector3f_t& v1, const ra_vector3f_t& v2);
	friend ra_vector3f_t Normalized(const ra_vector3f_t& v1);
	friend ra_vector3f_t Multiply(const ra_vector3f_t& v, float f);
	friend ra_vector3f_t Add(const ra_vector3f_t& v1, const ra_vector3f_t& v2);
	friend ra_vector3f_t Add(const ra_vector3f_t& v1, float f);
	friend ra_vector3f_t Lerp(const ra_vector3f_t& a, const ra_vector3f_t& b, float t);
	friend void Swap(ra_vector3f_t& first, ra_vector3f_t& second) noexcept;

	// Members
	// There is no point in making these private.
	float x;
	float y;
	float z;
};

//=============================================================================
// Vector4f
//=============================================================================

class ra_vector4f_t
{
public:

	// Constructors
	ra_vector4f_t();
	explicit ra_vector4f_t(float f);
	ra_vector4f_t(float x, float y, float z, float w);
	explicit ra_vector4f_t(const float *f);
	ra_vector4f_t(const ra_vector4f_t& other);
	explicit ra_vector4f_t(ra_vector4f_t&& other) noexcept;

	// Destructor

	virtual ~ra_vector4f_t();

	// Assignment operators

	ra_vector4f_t& operator=(float f) &;
	ra_vector4f_t& operator=(const ra_vector4f_t& other) &;
	ra_vector4f_t& operator=(ra_vector4f_t&& other) & noexcept;

	// Arithmetic operators

	ra_vector4f_t operator+(const ra_vector4f_t& other) const;
	ra_vector4f_t operator-(const ra_vector4f_t& other) const;

	friend ra_vector4f_t operator*(const ra_vector4f_t& v, float f);
	friend ra_vector4f_t operator*(float f, const ra_vector4f_t& v);

	friend ra_vector4f_t operator/(const ra_vector4f_t& v, float f);

	// Logical operators

	// Compound operators

	ra_vector4f_t& operator+=(const ra_vector4f_t& other) &;
	ra_vector4f_t& operator-=(const ra_vector4f_t& other) &;

	ra_vector4f_t& operator*=(float f) &;
	ra_vector4f_t& operator/=(float f) &;

	// Member access

	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;

	// Stream operators

	// Functions
	friend float Length(const ra_vector4f_t& v);
	friend float Dot(const ra_vector4f_t& v1, const ra_vector4f_t& v2);
	friend ra_vector4f_t Cross(const ra_vector4f_t& v1, const ra_vector4f_t& v2);
	friend ra_vector4f_t Normalized(const ra_vector4f_t& v1);
	friend ra_vector4f_t Multiply(const ra_vector4f_t& v, float f);
	friend ra_vector4f_t Add(const ra_vector4f_t& v1, const ra_vector4f_t& v2);
	friend ra_vector4f_t Add(const ra_vector4f_t& v1, float f);
	friend ra_vector4f_t Lerp(const ra_vector4f_t& a, const ra_vector4f_t& b, float t);
	friend void Swap(ra_vector4f_t& first, ra_vector4f_t& second) noexcept;

	// Members
	// There is no point in making these private.
	float x;
	float y;
	float z;
	float w;
};

