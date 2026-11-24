#ifndef FFTA_MISSION_DEFINITION_H
#define FFTA_MISSION_DEFINITION_H

#include "ffta/unsigned_types.h"

/* Selector results can be scalar values or addresses encoded as u32. */
extern u32 GetMissionProperty(u16 mission_id, u8 selector);

#endif
