#pragma once

#include "Vector.h"

// TODO: Implement class functionality

class ra_matrix4f_t
{
public:
	// Constructors

	// Destructor

	// Assignment operators

	// Arithmetic operators

	// Compound operators

	// Member access

	// Stream operators

	// Functions

	// Inverse
	// Transpose

	// Members
	float m[4][4];
};

ra_matrix4f_t Multiply(const ra_matrix4f_t& m1, const ra_matrix4f_t& m2);

ra_matrix4f_t InitIdentity();

ra_matrix4f_t InitScreenSpaceTransform(float halfWidth, float halfHeight);

ra_matrix4f_t InitTranslation(float x, float y, float z);

ra_matrix4f_t InitRotation(float x, float y, float z);

ra_matrix4f_t InitScale(float x, float y, float z);

ra_matrix4f_t InitPerspective(float fov, float aspectRatio, float zNear, float zFar);

ra_matrix4f_t InitOrthographic(float left, float  right, float bottom, float top, float nearPlane, float farPlane);

ra_matrix4f_t InitRotation(const ra_vector4f_t& forward, const ra_vector4f_t& up, const ra_vector4f_t& right);

ra_matrix4f_t InitRotation(const ra_vector4f_t& forward, const ra_vector4f_t& up);

ra_vector4f_t Transform(const ra_vector4f_t& vector, const ra_matrix4f_t& matrix);
