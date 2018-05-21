#pragma once

#include "Vector.h"
#include "Vertex.h"

typedef struct _ra_gradients
{
	ra_vector4f_t color[3];

	ra_vector4f_t colorXStep;
	ra_vector4f_t colorYStep;

	float texCoordX[3];
	float texCoordY[3];

	float texCoordXXStep;
	float texCoordXYStep;
	float texCoordYXStep;
	float texCoordYYStep;

	float oneOverZ[3];

	float oneOverZXStep;
	float oneOverZYStep;

	float depth[3];

	float depthXStep;
	float depthYStep;
} ra_gradients_t;

ra_gradients_t CreateGradients(ra_vertex_t minYvert, ra_vertex_t midYvert, ra_vertex_t maxYvert);