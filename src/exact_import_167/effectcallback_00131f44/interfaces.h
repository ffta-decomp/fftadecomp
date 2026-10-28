#ifndef WORKER3_EFFECT_131F44_H
#define WORKER3_EFFECT_131F44_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {
    u8 unknown00[0x104];
    u8 field104;
} EffectUnit;
typedef struct {
    EffectUnit *primary_unit;
    u32 unknown04;
    EffectUnit *effect_unit;
    u8 unknown0C[0x26-0xc];
    u16 flags;
} EffectContext;
typedef char assert_flags_offset[((u32)&((EffectContext *)0)->flags==0x26)?1:-1];
/* Callee CE1B0 consumes low8 internally, writes EA bit8; CE488 stores E6. */
void SetUnitFlagEA08(EffectUnit *unit, u32 enabled);
void SetUnitFieldE6(EffectUnit *unit, u32 value);
__asm__(".global SetUnitFlagEA08\n.thumb_set SetUnitFlagEA08,0x080ce1b1\n.global SetUnitFieldE6\n.thumb_set SetUnitFieldE6,0x080ce489\n");
#endif
