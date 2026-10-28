#ifndef SCRIPT_RECORD_H
#define SCRIPT_RECORD_H

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    const u8 *values;
    u8 unknown_20[2];
    u8 value22;
    u8 unknown_23[3];
    u8 value26;
    u8 unknown_27;
} ScriptRecord;

extern const ScriptRecord g_table_0854CD54[];

#endif
