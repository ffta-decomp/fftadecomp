#include "ffta/unsigned_types.h"
/* Only the field consumed here is named; the same full context reaches the helper. */
struct EffectRateContext { u8 unknown_00[38]; u16 flags; };
u32 CalculateExistingEffectRate(struct EffectRateContext *) __asm__("RetailCall_08131220");
asm(".global RetailCall_08131220\n.thumb_set RetailCall_08131220,0x08131221\n");
