#ifndef WORKER3_EFFECT_133244_H
#define WORKER3_EFFECT_133244_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {
    u8 unknown00[0x26];
    u16 flags;
} EffectContext;
typedef char assert_flags_offset[((u32)&((EffectContext *)0)->flags==0x26)?1:-1];
/* Existing equipment-selection effect; its frame and output remain untouched. */
void ApplyEquipmentSelectionEffect(EffectContext *context);
__asm__(".global ApplyEquipmentSelectionEffect\n.thumb_set ApplyEquipmentSelectionEffect,0x0813325d\n");
#endif
