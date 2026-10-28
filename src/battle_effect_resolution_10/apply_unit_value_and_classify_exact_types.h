#ifndef O2_UNIT_VALUE_INTERFACES_H
#define O2_UNIT_VALUE_INTERFACES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u32 UnitValueGate(void *unit) __asm__("RetailCall_080c8280");
extern u32 UnitStateE8Bit6(void *unit) __asm__("UnitHasPetrify");
extern u32 UnitStateEDBit4(void *unit) __asm__("RetailCall_080cdcbc");
extern u32 ReadUnitField(void *unit, u32 selector);
#endif
