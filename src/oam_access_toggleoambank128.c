typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Access the active IWRAM OAM bank. */
void ToggleOamBank128(void)
{
    *(volatile u8 *)0x03000028 ^= 1;
}
