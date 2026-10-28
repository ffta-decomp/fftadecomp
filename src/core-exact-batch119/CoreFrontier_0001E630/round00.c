typedef unsigned char u8;
struct MapCornerState { u8 preceding[2]; u8 flag; };
extern struct MapCornerState MapCornerState;
u8 ReadMapQueryInitialState(void)
{
    return MapCornerState.flag;
}
asm(".set MapCornerState,0x02007f40\n");
