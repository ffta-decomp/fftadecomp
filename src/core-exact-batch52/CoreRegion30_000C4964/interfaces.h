typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;
struct ChoiceUnit { u8 unknown_000[246]; u8 x; u8 y; };
struct ChoiceOwner { struct ChoiceUnit *unit; };
struct BattleChoiceContext {
    struct ChoiceOwner *owner;
    struct ChoiceOwner *reference;
    struct ChoiceOwner **group_08;
    struct ChoiceOwner **group_0c;
    u16 count_10;
    u16 count_12;
};
extern u32 ReadRandomValue(void);
extern s32 DirectionFromCoordinateDelta(s8, s8);
__asm__(".global ReadRandomValue\n.thumb_set ReadRandomValue,0x08002805\n"
        ".global DirectionFromCoordinateDelta\n.thumb_set DirectionFromCoordinateDelta,0x0809d6bd\n");
