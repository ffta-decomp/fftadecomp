#include "ffta/unsigned_types.h"

/* Access the active IWRAM OAM bank. */
void ToggleSharedOamBank(void)
{
    *(volatile u8 *)0x03002f58 ^= 1;
}
