#pragma once
#include "Vector.h"
#include "Vertex.h"
#include "Gradient.h"

typedef struct _ra_edge
{
	float x;
	float xStep;
	int yStart;
	int yEnd;

	ra_vector4f_t color;
	ra_vector4f_t colorStep;

	float texCoordX;
	float texCoordXStep;
	float texCoordY;
	float texCoordYStep;

	float oneOverZ;
	float oneOverZStep;

	float depth;
	float depthStep;
} ra_edge_t;

ra_edge_t CreateEdge(ra_gradients_t gradients, ra_vertex_t minYvert, ra_vertex_t maxYvert, int minYvertIndex);

void EdgeStep(ra_edge_t *edge);