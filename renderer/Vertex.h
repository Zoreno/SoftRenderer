#pragma once

#include "Vector.h"

class ra_matrix4f_t;

typedef struct _vertex
{
	ra_vector4f_t position;
	ra_vector4f_t color;

	ra_vector4f_t texCoords;
} ra_vertex_t;

float TriangleVertexArea(ra_vertex_t a, ra_vertex_t b, ra_vertex_t c);

ra_vertex_t Transform(const ra_vertex_t& v, const ra_matrix4f_t& ma);

ra_vertex_t PerspectiveDivide(const ra_vertex_t& v);

ra_vertex_t Lerp(const ra_vertex_t& first, const ra_vertex_t& second, float t);

float VertexGet(const ra_vertex_t&v, int index);

bool VertexIsInsideViewFrustum(const ra_vertex_t& v);