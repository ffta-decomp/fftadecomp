#ifndef PAIR_STATE_FORWARD_INTERFACES_H
#define PAIR_STATE_FORWARD_INTERFACES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* Existing exact helper; unused words remain real ABI slots. */
extern u32 UpdateUnitPairCounters(void *unit, u32 related, u32 value,
    u32 tag, u32 adjustment, u32 payload, u8 mode,
    u32 unused_slot, u8 selector);
__asm__(".global UpdateUnitPairCounters\n.thumb_set UpdateUnitPairCounters, 0x08134a11");

#endif
