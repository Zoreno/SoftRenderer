#include "Edge.h"

#include <cmath>

ra_edge_t CreateEdge(ra_gradients_t gradients, ra_vertex_t minYvert, ra_vertex_t maxYvert, int minYvertIndex)
{
	ra_edge_t edge;

	edge.yStart = static_cast<int>(std::ceil(minYvert.position.y));
	edge.yEnd = static_cast<int>(std::ceil(maxYvert.position.y));

	float yDist = maxYvert.position.y - minYvert.position.y;
	float xDist = maxYvert.position.x - minYvert.position.x;

	float yPrestep = edge.yStart - minYvert.position.y;

	edge.xStep = xDist / yDist;

	edge.x = minYvert.position.x + yPrestep * edge.xStep;

	float xPrestep = edge.x - minYvert.position.x;

	edge.color = gradients.color[minYvertIndex] + gradients.colorYStep * yPrestep + gradients.colorXStep * xPrestep;

	edge.colorStep = gradients.colorYStep + gradients.colorXStep * edge.xStep;

	edge.texCoordX = gradients.texCoordX[minYvertIndex] + gradients.texCoordXXStep * xPrestep + gradients.texCoordXYStep * yPrestep;
	edge.texCoordXStep = gradients.texCoordXYStep + gradients.texCoordXXStep * edge.xStep;

	edge.texCoordY = gradients.texCoordY[minYvertIndex] + gradients.texCoordYXStep * xPrestep + gradients.texCoordYYStep * yPrestep;
	edge.texCoordYStep = gradients.texCoordYYStep + gradients.texCoordYXStep * edge.xStep;

	edge.oneOverZ = gradients.oneOverZ[minYvertIndex] + gradients.oneOverZXStep * xPrestep + gradients.oneOverZYStep * yPrestep;
	edge.oneOverZStep = gradients.oneOverZYStep + gradients.oneOverZXStep * edge.xStep;

	edge.depth = gradients.depth[minYvertIndex] + gradients.depthXStep * xPrestep + gradients.depthYStep * yPrestep;
	edge.depthStep = gradients.depthYStep + gradients.depthXStep * edge.xStep;

	return edge;
}

void EdgeStep(ra_edge_t *edge)
{
	edge->x += edge->xStep;
	edge->color += edge->colorStep;
	edge->texCoordX += edge->texCoordXStep;
	edge->texCoordY += edge->texCoordYStep;
	edge->oneOverZ += edge->oneOverZStep;
	edge->depth += edge->depthStep;
}
