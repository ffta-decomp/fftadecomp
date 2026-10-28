#ifndef WORKER3_EFFECT_132550_H
#define WORKER3_EFFECT_132550_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {
    u8 unknown00[0x26];
    u16 flags;
} EffectContext;
typedef char assert_flags_offset[((u32)&((EffectContext *)0)->flags==0x26)?1:-1];
#endif
