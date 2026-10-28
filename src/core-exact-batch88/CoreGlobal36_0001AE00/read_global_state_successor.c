typedef unsigned short u16;

/* The global state's wider meaning is unknown; preserve the low-halfword wrap. */
u16 ReadGlobalStateSuccessor(void) __asm__("CoreGlobal36_0001AE00");
u16 ReadGlobalStateSuccessor(void)
{
    return (u16)(*(u16 *)0x02007f10 + 1);
}
