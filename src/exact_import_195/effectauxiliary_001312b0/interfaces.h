typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Only the field consumed here is named; the same full context reaches the helper. */
struct EffectRateContext { u8 unknown_00[38]; u16 flags; };
u32 CalculateExistingEffectRate(struct EffectRateContext *) __asm__("RetailCall_08131220");
asm(".global RetailCall_08131220\n.thumb_set RetailCall_08131220,0x08131221\n");
