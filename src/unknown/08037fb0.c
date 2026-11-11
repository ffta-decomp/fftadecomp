typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *gMenuContext;
struct SelectionControlView;
extern void SetSelectionControlMode(struct SelectionControlView *control,u32 mode);
extern void ConfigureSelectionMode(u32 ordinal,u8 mode);
asm(".global gMenuContext\n.set gMenuContext,0x03002810\n.global SetSelectionControlMode\n.thumb_set SetSelectionControlMode,0x08017509\n.global ConfigureSelectionMode\n.thumb_set ConfigureSelectionMode,0x080356a1\n");

void BeginPanelClose(u32 ordinal) __asm__("CoreRegion_00037FB0");
void BeginPanelClose(u32 ordinal)
{
    u8 **cell = &gMenuContext;
    u32 offset = ordinal * 204;
    SetSelectionControlMode((struct SelectionControlView *)
                            (offset + (u32)*cell + 0x9a0), 16);
    ConfigureSelectionMode(ordinal, 0);
    (*cell + offset)[0x98e] = 0;
}
