typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct DerivedFlagNode { const u8 *unit; u8 fields04[26]; u8 status; u8 fields1f[17]; u32 flags; };
extern u8 RetailCall_080cd944(const void *unit);
#define HasE8Bit7 RetailCall_080cd944
extern u8 UnitStateE9HasBit3(const void *unit);
#define HasE9Bit3 UnitStateE9HasBit3
extern u8 UnitStateE9HasBit1(const void *unit);
#define HasE9Bit1 UnitStateE9HasBit1
extern u8 UnitStateE9HasBit0(const void *unit);
#define HasE9Bit0 UnitStateE9HasBit0
extern u8 UnitStateE9HasBit7(const void *unit);
#define HasE9Bit7 UnitStateE9HasBit7
extern u8 RetailCall_080cda7c(const void *unit);
#define HasEABit2 RetailCall_080cda7c
extern u8 UnitStateE9HasBit4(const void *unit);
#define HasE9Bit4 UnitStateE9HasBit4
extern u8 UnitHasPetrify(const void *unit);
#define HasE8Bit6 UnitHasPetrify
extern u8 RetailCall_080cdcbc(const void *unit);
#define HasEDBit4 RetailCall_080cdcbc
extern u8 UnitStateEAHasBit7(const void *unit);
#define HasEABit7 UnitStateEAHasBit7
extern u8 UnitStateEBHasBit2(const void *unit);
#define HasEBBit2 UnitStateEBHasBit2
extern u8 RetailCall_080cdaac(const void *unit);
#define HasEABit5 RetailCall_080cdaac
extern u8 UnitStateEAHasBit6(const void *unit);
#define HasEABit6 UnitStateEAHasBit6
extern u8 HasE9Bit6(const void *unit) __asm__("0x080cd9ec");
extern u8 HasE9Bit5(const void *unit) __asm__("0x080cd9d4");
extern u8 BattleCalculationCall_080CDA4C(const void *unit);
#define HasECBit1 BattleCalculationCall_080CDA4C
extern u32 ReadUnitField(const void *unit,u8 selector);
extern void RetailCall_0809801c(struct DerivedFlagNode *node);
