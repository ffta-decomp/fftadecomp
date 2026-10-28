typedef unsigned char u8;
typedef unsigned int u32;

/* Read the active 48-entry OAM bank's next free slot. */
u32 GetOamBank48Index(void)
{
    register volatile u32 *indices __asm__("r1") = (volatile u32 *)0x03002c50;
    u8 bank;
    /* Keep the retail base-load order before the volatile bank read. */
    __asm__ volatile ("" : "+r" (indices));
    bank = *(volatile u8 *)0x03000028;
    return indices[bank];
}
