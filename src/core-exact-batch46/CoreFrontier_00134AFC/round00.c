#include "interfaces.h"

/* Preserve the original forwarding slots, including the inserted zero word. */
u8 ForwardUnitPairCounterUpdate(void *unit, u32 related, u16 value,
    u8 tag, s16 adjustment, u32 payload, u8 mode, u8 selector)
    asm("CoreFrontier_00134AFC");
u8 ForwardUnitPairCounterUpdate(void *unit, u32 related, u16 value,
    u8 tag, s16 adjustment, u32 payload, u8 mode, u8 selector)
{
    return (u8)UpdateUnitPairCounters(unit, related, value, tag,
        adjustment, payload, mode, 0, selector);
}
