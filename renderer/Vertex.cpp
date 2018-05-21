#include "Vertex.h"

#include "Matrix.h"

#include <cmath>
#include <stdexcept>

float TriangleVertexArea(ra_vertex_t a, ra_vertex_t b, ra_vertex_t c)
{
	float x1 = b.position.x - a.position.x;
	float y1 = b.position.y - a.position.y;
	float x2 = c.position.x - a.position.x;
	float y2 = c.position.y - a.position.y;

	return (x1 * y2 - x2 * y1) / 2.f;
}

ra_vertex_t Transform(const ra_vertex_t& v, const ra_matrix4f_t& ma)
{
	ra_vertex_t ret = v;

	ret.position = Transform(v.position, ma);

	return ret;
}

ra_vertex_t PerspectiveDivide(const ra_vertex_t& v)
{
	ra_vertex_t ret = v;

	ret.position.x /= ret.position.w;
	ret.position.y /= ret.position.w;
	ret.position.z /= ret.position.w;

	return ret;
}

ra_vertex_t Lerp(const ra_vertex_t& first, const ra_vertex_t& second, float t)
{
	ra_vertex_t ret;

	ret.position = Lerp(first.position, second.position, t);
	ret.color = Lerp(first.color, second.color, t);
	ret.texCoords = Lerp(first.texCoords, second.texCoords, t);

	return ret;
}

float VertexGet(const ra_vertex_t&v, int index)
{
	switch (index)
	{
	case 0:
		return v.position.x;
	case 1:
		return v.position.y;
	case 2:
		return v.position.z;
	case 3:
		return v.position.w;
	default:
		throw std::logic_error("Vertex index out of bounds.");
	}
}

bool VertexIsInsideViewFrustum(const ra_vertex_t& v)
{
	return abs(v.position.x) < abs(v.position.w) &&
		abs(v.position.y) < abs(v.position.w) &&
		abs(v.position.z) < abs(v.position.w);
}
