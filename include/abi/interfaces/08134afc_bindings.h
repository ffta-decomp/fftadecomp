#ifndef PAIR_STATE_FORWARD_INTERFACES_H
#define PAIR_STATE_FORWARD_INTERFACES_H

#include "ffta/unsigned_types.h"
typedef signed short s16;

/* Existing exact helper; unused words remain real ABI slots. */
extern u32 UpdateUnitPairCounters(void *unit, u32 related, u32 value,
    u32 tag, u32 adjustment, u32 payload, u8 mode,
    u32 unused_slot, u8 selector);
__asm__(".global UpdateUnitPairCounters\n.thumb_set UpdateUnitPairCounters, 0x08134a11");

#endif
