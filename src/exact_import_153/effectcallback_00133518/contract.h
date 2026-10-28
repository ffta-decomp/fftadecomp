typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct EffectContext {
    u8 reserved_0[8];
    void *unit;
    u8 reserved_12[26];
    u16 flags;
} EffectContext;
extern void RecordEffectMetadata(EffectContext *context, s32 index);
extern void SetUnitStateEDBit1(void *unit, u32 value);
__asm__(".thumb_set RecordEffectMetadata, 0x08131dd5\n"
        ".thumb_set SetUnitStateEDBit1, 0x080ce2a9\n");
