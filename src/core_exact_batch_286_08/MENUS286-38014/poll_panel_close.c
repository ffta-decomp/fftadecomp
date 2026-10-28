typedef unsigned char u8;
typedef unsigned int u32;
extern u32 ReadPanelCloseState(u32 ordinal);
asm(".global ReadPanelCloseState\n.thumb_set ReadPanelCloseState,0x08037ff1\n");

u32 PollPanelClose(u32 ordinal) __asm__("CoreRegion_00038014");
u32 PollPanelClose(u32 ordinal)
{
    return (u8)ReadPanelCloseState(ordinal);
}
