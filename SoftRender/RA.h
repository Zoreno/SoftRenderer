#pragma once

#include <RA_common.h>

typedef void(*ra_Initialize_f)(void);
typedef ra_uint32_t(*ra_GetMajorVersion_f)(void);
typedef ra_uint32_t(*ra_GetMinorVersion_f)(void);

ra_Initialize_f ra_Initialize;
ra_GetMajorVersion_f ra_GetMajorVersion;
ra_GetMinorVersion_f ra_GetMinorVersion;