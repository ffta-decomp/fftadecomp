typedef unsigned char u8;
extern u8 gPresentSaveSlots;
u8 ReadPresentSaveSlots(void)
{
    return gPresentSaveSlots;
}
asm(".global gPresentSaveSlots\n.set gPresentSaveSlots,0x030009c8\n");
