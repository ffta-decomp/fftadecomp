typedef unsigned char u8;
struct ContentGameState {
    u8 unknown_0000[0x3c32];
    u8 field_3c32; /* Role beyond this content-action threshold remains unproved. */
};
extern struct ContentGameState ContentState __asm__("ContentStateBase");
__asm__(".set ContentStateBase, 0x02000000");
extern unsigned int CheckCurrentContentMode(u8) __asm__("0x080ced5c");
int IsContentActionGateOpen(void)
{
    int open;
    if ((u8)CheckCurrentContentMode(1))
        return 0;
    open = 0;
    if (ContentState.field_3c32 > 1)
        open = 1;
    return open;
}
