typedef unsigned char u8;
typedef unsigned short u16;

/* The source does not establish a conventional meaning for this unit byte. */
struct EffectUnit {
    u8 unknown00[0x104];
    u8 byte104;
};
struct EffectContext {
    void *unit_at_0;
    u8 unknown04[0x4];
    struct EffectUnit *unit_at_8;
    u8 unknown0C[0x4];
    u8 recorded_effect_bits[0x16];
    u16 flags;
};
typedef char EffectContextSizeCheck[sizeof(struct EffectContext) == 0x28 ? 1 : -1];
extern void EffectApplicationCall_081320E8(struct EffectContext *);
extern void WriteUnitCounterDC(void *, u8);
