typedef unsigned char u8;
typedef unsigned short u16;
struct CurrentContentState {
    u8 unknown_0000[160];
    u16 current_index;
};
extern struct CurrentContentState gCurrentContentState;
asm(".global gCurrentContentState\n.set gCurrentContentState,0x020020d0");
u16 ReadCurrentContentIndex(void)
{
    return gCurrentContentState.current_index;
}
