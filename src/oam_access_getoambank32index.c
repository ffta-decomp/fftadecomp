typedef unsigned char u8;
typedef unsigned int u32;

/* Read the active 32-entry OAM bank's next free slot. */
u32 GetOamBank32Index(void)
{
    register volatile u32 *indices __asm__("r1") = (volatile u32 *)0x03002f60;
    u8 bank;
    /* Keep the retail base-load order before the volatile bank read. */
    __asm__ volatile ("" : "+r" (indices));
    bank = *(volatile u8 *)0x03002f58;
    return indices[bank];
}
