typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef struct EffectContext {
    u8 *unit;
    u8 reserved[0x1c];
    s16 amounts[4];
    u8 selected_index;
} EffectContext;
extern u32 GetUnitProperty(const u8 *unit, u8 property);
__asm__(".thumb_set GetUnitProperty, 0x080c7ea5\n");
