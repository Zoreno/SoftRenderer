#include "Color.h"


ra_color_t CreateColor(ra_uint8_t red, ra_uint8_t green, ra_uint8_t blue, ra_uint8_t alpha)
{
	ra_color_t color;

	color.red = red;
	color.green = green;
	color.blue = blue;
	color.alpha = alpha;

	return color;
}

ra_color_t CreateColor(ra_uint8_t greyScale, ra_uint8_t alpha)
{
	ra_color_t color;

	color.red = greyScale;
	color.green = greyScale;
	color.blue = greyScale;
	color.alpha = alpha;

	return color;
}
