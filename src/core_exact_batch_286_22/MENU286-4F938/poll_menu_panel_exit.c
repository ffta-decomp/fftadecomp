typedef unsigned char u8;
typedef unsigned int u32;
extern u32 UpdateExitPanel(void *);
u32 PollMenuPanelExit(u8 *) __asm__("CoreRegion_0004F938");
u32 PollMenuPanelExit(u8 *context)
{
    return (u8)UpdateExitPanel(context + 28);
}
__asm__(".global UpdateExitPanel\n.thumb_set UpdateExitPanel,0x08017181\n");
