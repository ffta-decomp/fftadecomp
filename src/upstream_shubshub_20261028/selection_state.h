#ifndef SELECTION_STATE_H
#define SELECTION_STATE_H

#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA0];
    u16 index;
    u16 override_index;
    u8 unknown_A4[2];
    u8 values[2];
    u8 record_indices[3];
} SelectionState;

extern SelectionState g_state_020020D0;

#endif
