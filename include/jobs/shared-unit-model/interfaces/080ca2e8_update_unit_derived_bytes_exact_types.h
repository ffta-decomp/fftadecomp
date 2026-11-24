typedef unsigned char u8;
typedef unsigned int u32;
typedef struct {u8 first,second,third,complement;} DerivedBytes;
typedef struct {u8 unknown[61];u8 mode;u8 unknown62[190];DerivedBytes derived;} Unit;
u32 UnitProperty(Unit*,u32) __asm__("RetailCall_080c92f0");
u32 StateGate(Unit*) __asm__("UnitStateE9HasBit0");
u32 EquipmentValue(Unit*,u32) __asm__("UnitModelCall_CA4F0");
