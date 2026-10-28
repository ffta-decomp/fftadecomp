typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Access the active IWRAM OAM bank. */
void ToggleSharedOamBank(void)
{
    *(volatile u8 *)0x03002f58 ^= 1;
}
