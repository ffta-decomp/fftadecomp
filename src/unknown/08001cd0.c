#include "ffta/unsigned_types.h"

/* Access the active IWRAM OAM bank. */
void ToggleOamBank128(void)
{
    *(volatile u8 *)0x03000028 ^= 1;
}
