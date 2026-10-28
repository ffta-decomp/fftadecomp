typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {u8 unknown00[32];s16 base_stat;u8 unknown34[8];u16 equipment[5];} UnitStatView;
u32 ItemProperty(u32,u32) __asm__("GetItemProperty");
typedef char CheckEquipment[(u32)&((UnitStatView*)0)->equipment==42?1:-1];
