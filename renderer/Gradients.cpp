#include "Gradient.h"

#include "Vertex.h"

static float CalculateXStep(float *values, ra_vertex_t minYvert, ra_vertex_t midYvert, ra_vertex_t maxYvert, float oneOverdX)
{
	return
		((values[1] - values[2]) *
		(minYvert.position.y - maxYvert.position.y) -
			(values[0] - values[2]) *
			(midYvert.position.y - maxYvert.position.y)) * oneOverdX;
}

static float CalculateYStep(float *values, ra_vertex_t minYvert, ra_vertex_t midYvert, ra_vertex_t maxYvert, float oneOverdY)
{
	return
		((values[1] - values[2]) *
		(minYvert.position.x - maxYvert.position.x) -
			(values[0] - values[2]) *
			(midYvert.position.x - maxYvert.position.x)) * oneOverdY;
}

ra_gradients_t CreateGradients(ra_vertex_t minYvert, ra_vertex_t midYvert, ra_vertex_t maxYvert)
{
	ra_gradients_t grad;

	grad.color[0] = minYvert.color;
	grad.color[1] = midYvert.color;
	grad.color[2] = maxYvert.color;

	grad.oneOverZ[0] = 1.0f / minYvert.position.w;
	grad.oneOverZ[1] = 1.0f / midYvert.position.w;
	grad.oneOverZ[2] = 1.0f / maxYvert.position.w;

	grad.texCoordX[0] = minYvert.texCoords.x * grad.oneOverZ[0];
	grad.texCoordX[1] = midYvert.texCoords.x * grad.oneOverZ[1];
	grad.texCoordX[2] = maxYvert.texCoords.x * grad.oneOverZ[2];

	grad.texCoordY[0] = minYvert.texCoords.y * grad.oneOverZ[0];
	grad.texCoordY[1] = midYvert.texCoords.y * grad.oneOverZ[1];
	grad.texCoordY[2] = maxYvert.texCoords.y * grad.oneOverZ[2];

	grad.depth[0] = minYvert.position.z;
	grad.depth[1] = midYvert.position.z;
	grad.depth[2] = maxYvert.position.z;

	float oneOverdX = 1.0f /
		((midYvert.position.x - maxYvert.position.x) * (minYvert.position.y - maxYvert.position.y) -
		(minYvert.position.x - maxYvert.position.x) * (midYvert.position.y - maxYvert.position.y));

	float oneOverdY = -oneOverdX;

	ra_vector4f_t dCX = (grad.color[1] - grad.color[2]) * (minYvert.position.y - maxYvert.position.y) -
		(grad.color[0] - grad.color[2]) * (midYvert.position.y - maxYvert.position.y);

	ra_vector4f_t dCY = (grad.color[1] - grad.color[2]) * (minYvert.position.x - maxYvert.position.x) -
		(grad.color[0] - grad.color[2]) * (midYvert.position.x - maxYvert.position.x);

	grad.colorXStep = dCX * oneOverdX;
	grad.colorYStep = dCY * oneOverdY;

	grad.texCoordXXStep = CalculateXStep(grad.texCoordX, minYvert, midYvert, maxYvert, oneOverdX);
	grad.texCoordXYStep = CalculateYStep(grad.texCoordX, minYvert, midYvert, maxYvert, oneOverdY);
	grad.texCoordYXStep = CalculateXStep(grad.texCoordY, minYvert, midYvert, maxYvert, oneOverdX);
	grad.texCoordYYStep = CalculateYStep(grad.texCoordY, minYvert, midYvert, maxYvert, oneOverdY);

	grad.oneOverZXStep = CalculateXStep(grad.oneOverZ, minYvert, midYvert, maxYvert, oneOverdX);
	grad.oneOverZYStep = CalculateYStep(grad.oneOverZ, minYvert, midYvert, maxYvert, oneOverdY);

	grad.depthXStep = CalculateXStep(grad.depth, minYvert, midYvert, maxYvert, oneOverdX);
	grad.depthYStep = CalculateYStep(grad.depth, minYvert, midYvert, maxYvert, oneOverdY);

	return grad;
}
