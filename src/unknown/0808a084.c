typedef unsigned char u8;
typedef unsigned int u32;

/* Original roster-root byte accessor; field meaning remains neutral. */
u32 CoreGlobal36_0008A084(void)
{
    u8 *root = *(u8 **)0x03002818;
    return root[0x987];
}
