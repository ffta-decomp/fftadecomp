#ifndef FFTA_PLATFORM_GBA_BIOS_H
#define FFTA_PLATFORM_GBA_BIOS_H

#include "ffta/unsigned_types.h"

/* GBA BIOS SWI 0x0B. The control word selects width,
 * fixed-source mode and the number of transfer units. */
extern void BiosCpuSet(const void *source, void *destination, u32 control);

#endif
