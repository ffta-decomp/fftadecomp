#ifndef SCRIPT_ENTRY_H
#define SCRIPT_ENTRY_H

#include "ffta.h"

typedef struct ScriptEntry {
    u8 unknown_00;
    u8 identifier;
    u16 value;
    u8 unknown_04[2];
    u8 selector;
    u8 unknown_07;
    u16 flags;
    u8 unknown_0A[2];
} ScriptEntry;

extern const ScriptEntry g_table_08563A70[];

#endif
