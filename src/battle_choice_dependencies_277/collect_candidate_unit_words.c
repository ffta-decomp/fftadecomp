typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* The loop count is a snapshot; the returned signed count is a fresh read. */
int CoreRegion30_000C486C(u8 *incoming_context, u32 *destination)
{
    u8 *context;
    u16 count;
    {
        register u8 *entry_context asm("r1") = incoming_context;
        /* Only entry transfer requires R1; the later pointer has ordinary lifetime. */
        asm("" : "+r" (entry_context));
        context = entry_context;
    }
    count = *(u16 *)(context + 0x2964);
    if (count != 0) {
        register u8 *source asm("r2") = context + 92;
        register u32 stride asm("r4") = 808;
        u32 remaining;
        /* Native makes the stride available before copying the loop-count snapshot. */
        asm("" : "+r" (source) : "r" (stride));
        remaining = count;
        do {
            *destination++ = *(u32 *)source;
            source += stride;
            --remaining;
        } while (remaining != 0);
    }
    return *(s16 *)(context + 0x2964);
}
