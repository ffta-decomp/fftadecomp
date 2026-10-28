#ifndef CRITICAL_HEALTH_EFFECT_INTERFACES_H
#define CRITICAL_HEALTH_EFFECT_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct UnitHealthView {
    u8 unknown_00[24];
    u16 current_health;
    u16 maximum_health;
} UnitHealthView;
extern u32 DivideUnsigned(u32 dividend, u32 divisor);
extern u32 ApplyEffectMode(UnitHealthView *unit, void *other, u32 mode, u32 flags);
/* Stable retail interfaces; these declarations introduce no helper bodies. */
__asm__(".global DivideUnsigned\n.thumb_set DivideUnsigned, 0x08142ab1");
__asm__(".global ApplyEffectMode\n.thumb_set ApplyEffectMode, 0x0812c8dd");
#endif
