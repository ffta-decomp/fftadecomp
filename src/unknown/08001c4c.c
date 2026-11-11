#include "ffta/unsigned_types.h"

/* Access the active IWRAM OAM bank. */
void SetOamBank128Index(u32 next_index)
{
    register volatile u32 *indices __asm__("r2") = (volatile u32 *)0x03000020;
    u8 bank;
    /* Keep the retail base-load order before the volatile bank read. */
    __asm__ volatile ("" : "+r" (indices));
    bank = *(volatile u8 *)0x03000028;
    indices[bank] = next_index;
}
