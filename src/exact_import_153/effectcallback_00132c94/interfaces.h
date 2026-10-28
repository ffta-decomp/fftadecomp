typedef unsigned char u8;
typedef unsigned short u16;

/* Only the observed effect-context fields are interpreted. */
struct EffectContext {
    u8 unknown00[0x8];
    void *affected_unit;
    u8 unknown0C[0x4];
    u8 recorded_effect_bits[0x16];
    u16 flags;
};
typedef char EffectContextSizeCheck[sizeof(struct EffectContext) == 0x28 ? 1 : -1];

/* The metadata helper uses an arithmetic signed index shift before byte OR. */
extern void EffectApplicationCall_08131DD4(struct EffectContext *, int);
extern void SetUnitStateE9Bit7(void *, u8);
