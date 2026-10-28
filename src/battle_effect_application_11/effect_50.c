#include "interfaces.h"

typedef struct {
    u8 bytes_000_3c2a[0x3c2b];
    u8 byte_3c2b;
} EwramCounterView;
extern EwramCounterView gEwramBase;

typedef struct {
    u8 bytes_000_0f0[241];
    u8 byte_0f1;
    u8 byte_0f2;
} UnitCounterView;

void ClearAffectedValueAndIncrementBattleCounters(volatile ApplicationContext *context)
{
    u16 flags;
    u32 count;
    u32 ewram_base;
    u32 counter_offset;
    u8 *global_counter;
    if (context->flags & 16) return;
    if ((u8)EffectResolutionCall_080CD8FC(context->affected)) {
        if (context->flags & 16) return;
        SetUnitStateE8Bit4(context->affected, 0);
        flags = context->flags;
        *(u16 *)((u8 *)context + 38) = flags | 256;
        return;
    }
    EffectApplicationCall_08131DD4(context, 0);
    if (context->flags & 16) return;
    ApplicationHalf(context->affected, 24) = 0;
    {
        register u8 *counter_address __asm__("r0") = (u8 *)context->actor + 241;
        register u32 count __asm__("r1") = *counter_address;
        if (count <= 254) count = count + 1;
        *counter_address = count;
    }
    if (!(u8)RetailCall_080cd8cc(context->affected)) {
        {
            register u8 *counter_address __asm__("r0") = (u8 *)context->affected + 242;
            register u32 count __asm__("r1") = *counter_address;
            if (count <= 254) count = count + 1;
            *counter_address = count;
        }
        if ((u8)RetailCall_080c8240(context->affected)) {
            ewram_base = (u32)&gEwramBase;
            counter_offset = 0x3c2b;
            global_counter = (u8 *)(ewram_base + counter_offset);
            count = *global_counter;
            *global_counter = count + 1;
        }
    }
    ResetBattleUnitTransientState(context->affected);
}
