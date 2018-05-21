#pragma once

#include "RA_common.h"

#pragma pack(push, 1)
typedef struct _ra_color
{
	ra_uint8_t red;
	ra_uint8_t green;
	ra_uint8_t blue;
	ra_uint8_t alpha;

} ra_color_t;
#pragma pack(pop)

ra_color_t CreateColor(ra_uint8_t red, ra_uint8_t green, ra_uint8_t blue, ra_uint8_t alpha = 0xFF);

ra_color_t CreateColor(ra_uint8_t greyScale, ra_uint8_t alpha);