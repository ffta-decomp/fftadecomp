typedef unsigned int u32;
typedef signed int s32;
typedef signed short s16;

s32 CoreFrontier_00007A60(u32 index)
{
    register u32 offset asm("r0");
    register u32 base asm("r1");

    offset = index << 24;
    base = 0x08149568;
    __asm__ volatile ("" : "+r" (offset) : "r" (base));
    offset = offset >> 23;
    offset += 0x80;
    offset += base;
    return *(const s16 *)offset;
}
