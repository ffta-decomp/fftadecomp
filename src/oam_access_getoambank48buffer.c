typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 affine;
} OamEntry;

/* Access the active IWRAM OAM bank. */
OamEntry * GetOamBank48Buffer(void)
{
    return (OamEntry *)0x03002c58 + (u32)*(volatile u8 *)0x03000028 * 48;
}
