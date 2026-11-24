typedef unsigned char u8;
typedef unsigned short u16;
struct SharedUpdateState {
    u8 unknown_0000[44];
    u16 flags;
};
extern struct SharedUpdateState gSharedUpdateState;
asm(".global gSharedUpdateState\n.set gSharedUpdateState,0x02007f40");
void SetSharedUpdateFlagTwo(void)
{
    gSharedUpdateState.flags = 2 | gSharedUpdateState.flags;
}
