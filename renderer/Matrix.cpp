#include "Matrix.h"

#include <cmath>

ra_matrix4f_t Multiply(const ra_matrix4f_t& m1, const ra_matrix4f_t& m2)
{
	ra_matrix4f_t ret;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			ret.m[i][j] =
				m1.m[i][0] * m2.m[0][j] +
				m1.m[i][1] * m2.m[1][j] +
				m1.m[i][2] * m2.m[2][j] +
				m1.m[i][3] * m2.m[3][j];
		}
	}

	return ret;
}

ra_matrix4f_t InitIdentity()
{
	ra_matrix4f_t ret;

	ret.m[0][0] = 1;
	ret.m[0][1] = 0;
	ret.m[0][2] = 0;
	ret.m[0][3] = 0;

	ret.m[1][0] = 0;
	ret.m[1][1] = 1;
	ret.m[1][2] = 0;
	ret.m[1][3] = 0;

	ret.m[2][0] = 0;
	ret.m[2][1] = 0;
	ret.m[2][2] = 1;
	ret.m[2][3] = 0;

	ret.m[3][0] = 0;
	ret.m[3][1] = 0;
	ret.m[3][2] = 0;
	ret.m[3][3] = 1;

	return ret;
}

ra_matrix4f_t InitScreenSpaceTransform(float halfWidth, float halfHeight)
{
	ra_matrix4f_t ret;

	ret.m[0][0] = halfWidth;
	ret.m[0][1] = 0;
	ret.m[0][2] = 0;
	ret.m[0][3] = halfWidth;

	ret.m[1][0] = 0;
	ret.m[1][1] = -halfHeight;
	ret.m[1][2] = 0;
	ret.m[1][3] = halfHeight;

	ret.m[2][0] = 0;
	ret.m[2][1] = 0;
	ret.m[2][2] = 1;
	ret.m[2][3] = 0;

	ret.m[3][0] = 0;
	ret.m[3][1] = 0;
	ret.m[3][2] = 0;
	ret.m[3][3] = 1;

	return ret;
}

ra_matrix4f_t InitTranslation(float x, float y, float z)
{
	ra_matrix4f_t ret;

	ret.m[0][0] = 1;
	ret.m[0][1] = 0;
	ret.m[0][2] = 0;
	ret.m[0][3] = x;

	ret.m[1][0] = 0;
	ret.m[1][1] = 1;
	ret.m[1][2] = 0;
	ret.m[1][3] = y;

	ret.m[2][0] = 0;
	ret.m[2][1] = 0;
	ret.m[2][2] = 1;
	ret.m[2][3] = z;

	ret.m[3][0] = 0;
	ret.m[3][1] = 0;
	ret.m[3][2] = 0;
	ret.m[3][3] = 1;

	return ret;
}

ra_matrix4f_t InitRotation(float x, float y, float z)
{
	ra_matrix4f_t rx;
	ra_matrix4f_t ry;
	ra_matrix4f_t rz;

	x = (float)x * 3.14159f / 180.f;
	y = (float)y * 3.14159f / 180.f;
	z = (float)z * 3.14159f / 180.f;

	// Z axis rotation

	rz.m[0][0] = (float)std::cos(z);
	rz.m[0][1] = -(float)std::sin(z);
	rz.m[0][2] = 0;
	rz.m[0][3] = 0;

	rz.m[1][0] = (float)std::sin(z);
	rz.m[1][1] = (float)std::cos(z);
	rz.m[1][2] = 0;
	rz.m[1][3] = 0;

	rz.m[2][0] = 0;
	rz.m[2][1] = 0;
	rz.m[2][2] = 1;
	rz.m[2][3] = 0;

	rz.m[3][0] = 0;
	rz.m[3][1] = 0;
	rz.m[3][2] = 0;
	rz.m[3][3] = 1;

	// X axis rotation

	rx.m[0][0] = 1;
	rx.m[0][1] = 0;
	rx.m[0][2] = 0;
	rx.m[0][3] = 0;

	rx.m[1][0] = 0;
	rx.m[1][1] = (float)std::cos(x);
	rx.m[1][2] = -(float)std::sin(x);
	rx.m[1][3] = 0;

	rx.m[2][0] = 0;
	rx.m[2][1] = (float)std::sin(x);
	rx.m[2][2] = (float)std::cos(x);
	rx.m[2][3] = 0;

	rx.m[3][0] = 0;
	rx.m[3][1] = 0;
	rx.m[3][2] = 0;
	rx.m[3][3] = 1;

	// Y axis rotation

	ry.m[0][0] = (float)std::cos(y);
	ry.m[0][1] = 0;
	ry.m[0][2] = -(float)std::sin(y);
	ry.m[0][3] = 0;

	ry.m[1][0] = 0;
	ry.m[1][1] = 1;
	ry.m[1][2] = 0;
	ry.m[1][3] = 0;

	ry.m[2][0] = (float)std::sin(y);
	ry.m[2][1] = 0;
	ry.m[2][2] = (float)std::cos(y);
	ry.m[2][3] = 0;

	ry.m[3][0] = 0;
	ry.m[3][1] = 0;
	ry.m[3][2] = 0;
	ry.m[3][3] = 1;

	ry = Multiply(ry, rx);

	return Multiply(rz, ry);
}

ra_matrix4f_t InitScale(float x, float y, float z)
{
	ra_matrix4f_t ret;

	ret.m[0][0] = x;
	ret.m[0][1] = 0;
	ret.m[0][2] = 0;
	ret.m[0][3] = 0;

	ret.m[1][0] = 0;
	ret.m[1][1] = y;
	ret.m[1][2] = 0;
	ret.m[1][3] = 0;

	ret.m[2][0] = 0;
	ret.m[2][1] = 0;
	ret.m[2][2] = z;
	ret.m[2][3] = 0;

	ret.m[3][0] = 0;
	ret.m[3][1] = 0;
	ret.m[3][2] = 0;
	ret.m[3][3] = 1;

	return ret;
}

ra_matrix4f_t InitPerspective(float fov, float aspectRatio, float zNear, float zFar)
{
	ra_matrix4f_t ret;

	fov = (float)fov * 3.14159f / 180.f;

	float tanHalfFOV = (float)std::tan(fov / 2);
	float zRange = zNear - zFar;

	ret.m[0][0] = 1.0f / (tanHalfFOV * aspectRatio);
	ret.m[0][1] = 0;
	ret.m[0][2] = 0;
	ret.m[0][3] = 0;

	ret.m[1][0] = 0;
	ret.m[1][1] = 1.0f / tanHalfFOV;
	ret.m[1][2] = 0;
	ret.m[1][3] = 0;

	ret.m[2][0] = 0;
	ret.m[2][1] = 0;
	ret.m[2][2] = (-zNear - zFar) / zRange;
	ret.m[2][3] = 2 * zFar * zNear / zRange;

	ret.m[3][0] = 0;
	ret.m[3][1] = 0;
	ret.m[3][2] = 1;
	ret.m[3][3] = 0;

	return ret;

}

ra_matrix4f_t InitOrthographic(float left, float  right, float bottom, float top, float nearPlane, float farPlane)
{
	ra_matrix4f_t ret;

	float width = right - left;
	float height = top - bottom;
	float depth = farPlane - nearPlane;

	ret.m[0][0] = 2 / width;
	ret.m[0][1] = 0;
	ret.m[0][2] = 0;
	ret.m[0][3] = -(right + left) / width;

	ret.m[1][0] = 0;
	ret.m[1][1] = 2 / height;
	ret.m[1][2] = 0;
	ret.m[1][3] = -(top + bottom) / height;

	ret.m[2][0] = 0;
	ret.m[2][1] = 0;
	ret.m[2][2] = -2 / depth;
	ret.m[2][3] = -(farPlane + nearPlane) / depth;

	ret.m[3][0] = 0;
	ret.m[3][1] = 0;
	ret.m[3][2] = 0;
	ret.m[3][3] = 1;

	return ret;
}

ra_matrix4f_t InitRotation(const ra_vector4f_t& forward, const ra_vector4f_t& up, const ra_vector4f_t& right)
{

	ra_matrix4f_t ret;

	ra_vector4f_t f = forward;
	ra_vector4f_t r = right;
	ra_vector4f_t u = up;

	ret.m[0][0] = r.x;
	ret.m[0][1] = r.y;
	ret.m[0][2] = r.z;
	ret.m[0][3] = 0;

	ret.m[1][0] = u.x;
	ret.m[1][1] = u.y;
	ret.m[1][2] = u.z;
	ret.m[1][3] = 0;

	ret.m[2][0] = f.x;
	ret.m[2][1] = f.y;
	ret.m[2][2] = f.z;
	ret.m[2][3] = 0;

	ret.m[3][0] = 0;
	ret.m[3][1] = 0;
	ret.m[3][2] = 0;
	ret.m[3][3] = 1;

	return ret;
}

ra_matrix4f_t InitRotation(const ra_vector4f_t& forward, const ra_vector4f_t& up)
{
	ra_vector4f_t f = Normalized(forward);

	ra_vector4f_t r = Normalized(up);

	r = Cross(r, f);

	ra_vector4f_t u;

	u = Cross(f, r);

	return InitRotation(f, u, r);
}

ra_vector4f_t Transform(const ra_vector4f_t& vector, const ra_matrix4f_t& matrix)
{
	ra_vector4f_t ret;

	ret.x = matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z + matrix.m[0][3] * vector.w;
	ret.y = matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z + matrix.m[1][3] * vector.w;
	ret.z = matrix.m[2][0] * vector.x + matrix.m[2][1] * vector.y + matrix.m[2][2] * vector.z + matrix.m[2][3] * vector.w;
	ret.w = matrix.m[3][0] * vector.x + matrix.m[3][1] * vector.y + matrix.m[3][2] * vector.z + matrix.m[3][3] * vector.w;

	return ret;
}
