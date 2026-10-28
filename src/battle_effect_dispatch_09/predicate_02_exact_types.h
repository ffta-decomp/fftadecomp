typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {u8 unknown00[42];u16 equipment[5];} EffectUnit;
typedef struct {void *previous;EffectUnit *unit;} EffectContext;
u32 UnitField19IsZero(EffectUnit *) __asm__("UnitField19IsZero");
u32 ItemProperty(u32,u32) __asm__("GetItemProperty");
typedef char CheckEquipment[(u32)&((EffectUnit*)0)->equipment==42?1:-1];
