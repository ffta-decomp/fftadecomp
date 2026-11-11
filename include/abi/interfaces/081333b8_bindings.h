typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
struct EffectContext {u8 unknown00[8];void *unit;u8 unknown0C[4];u8 metadata[22];u16 flags;};
extern void EffectApplicationCall_08131DD4(struct EffectContext *,int);
extern void SetUnitStateE9Bit6(void *,u8);
