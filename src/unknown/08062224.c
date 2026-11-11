typedef unsigned char u8;
struct LinkSelectionFlow {
    u8 fields_before_completion[76];
    u8 complete;
};
extern struct LinkSelectionFlow *gLinkSelectionFlow;
extern void SetSceneWindow(u8 x, u8 y, u8 width, u8 height);
extern void ResetSerialTransport(void);
__asm__(".global gLinkSelectionFlow\n.set gLinkSelectionFlow,0x0200f450\n.global SetSceneWindow\n.thumb_set SetSceneWindow,0x0802a2c1\n.global ResetSerialTransport\n.thumb_set ResetSerialTransport,0x08004c41");

/* Concrete scene terminal policy; transport and window mechanisms stay shared. */
void FinishLinkSelectionFlow(void)
{
    SetSceneWindow(0, 0, 0, 0);
    ResetSerialTransport();
    gLinkSelectionFlow->complete = 1;
}
