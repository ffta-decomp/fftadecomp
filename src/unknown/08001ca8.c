#include "ffta/unsigned_types.h"

typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 affine;
} OamEntry;

/* Access the active IWRAM OAM bank. */
OamEntry * GetOamBank128Buffer(void)
{
    return (OamEntry *)0x03000030 + (u32)*(volatile u8 *)0x03000028 * 128;
}
