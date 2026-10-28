#ifndef WORKER3_EFFECT_132520_H
#define WORKER3_EFFECT_132520_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct EffectUnit EffectUnit;
typedef struct {
    EffectUnit *primary_unit;
    u32 unknown04;
    EffectUnit *effect_unit;
    u32 unknown0C;
    u8 effect_metadata[0x26-0x10];
    u16 flags;
} EffectContext;
typedef char assert_metadata_offset[((u32)&((EffectContext *)0)->effect_metadata==0x10)?1:-1];
typedef char assert_flags_offset[((u32)&((EffectContext *)0)->flags==0x26)?1:-1];
/* The metadata helper uses index>>3 arithmetically; setters narrow internally. */
void RecordEffectMetadata(EffectContext *context, s32 index);
void SetUnitStateEABit1(EffectUnit *unit, u32 enabled);
__asm__(".global RecordEffectMetadata\n.thumb_set RecordEffectMetadata,0x08131dd5\n.global SetUnitStateEABit1\n.thumb_set SetUnitStateEABit1,0x080cdf9d\n");
#endif
