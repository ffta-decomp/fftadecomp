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
extern void SetUnitStateEBBit0(void *unit, u32 value);
__asm__(".thumb_set RecordEffectMetadata, 0x08131dd5\n"
        ".thumb_set SetUnitStateEBBit0, 0x080ce071\n");

extern void WriteUnitByteDD(void *unit, u32 value);
__asm__(".thumb_set WriteUnitByteDD, 0x080ce441\n");
