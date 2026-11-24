typedef unsigned char u8;
typedef unsigned short u16;
struct SharedUpdateState { u8 unknown[44]; u16 flags; };
extern struct SharedUpdateState gSharedUpdateState;
__asm__(".global gSharedUpdateState\n.set gSharedUpdateState,0x02007f40");
void SetPrimaryUpdateFlag(void) __asm__("CoreGlobal36_0001B878");
void SetPrimaryUpdateFlag(void)
{
    gSharedUpdateState.flags = 1 | gSharedUpdateState.flags;
}
