#ifndef WORKER3_EFFECT_132550_H
#define WORKER3_EFFECT_132550_H
#include "ffta/unsigned_types.h"
typedef struct {
    u8 unknown00[0x26];
    u16 flags;
} EffectContext;
typedef char assert_flags_offset[((u32)&((EffectContext *)0)->flags==0x26)?1:-1];
#endif
