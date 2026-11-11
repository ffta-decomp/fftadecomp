typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef void (*MemoryCopy)(void *, const void *, u32);
extern void *gUnitTaskContext;
extern MemoryCopy gMemoryCopy;
/* Blank leading slots remain untouched; preserve the observed divide/modulo call sequence. */
void FormatUnitTaskMagnitude(void *destination, s16 signed_value)
{
    const u8 *digits = (const u8 *)gUnitTaskContext + 1948;
    u8 *output = destination;
    int magnitude = signed_value;
    u32 digit_offset;
    if (magnitude < 0)
        magnitude = -magnitude;
    if (magnitude > 999)
        magnitude = 999;
    digit_offset = (magnitude / 100) << 5;
    if (digit_offset != 0)
        gMemoryCopy(output, digits + digit_offset, 32);
    digit_offset = ((magnitude / 10) % 10) << 5;
    if (magnitude > 99 || digit_offset != 0)
        gMemoryCopy(output + 32, digits + digit_offset, 32);
    digit_offset = (magnitude % 10) << 5;
    gMemoryCopy(output + 64, digits + digit_offset, 32);
}
asm(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200F440\n"
    ".global gMemoryCopy\n.set gMemoryCopy,0x0836D4BC\n"
    ".global __divsi3\n.thumb_set __divsi3,0x081426B9\n"
    ".global __modsi3\n.thumb_set __modsi3,0x08142951\n"
    ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224D\n");
