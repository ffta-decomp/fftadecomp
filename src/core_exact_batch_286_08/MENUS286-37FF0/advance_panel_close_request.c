typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *gMenuContext;
extern u32 AdvanceSelectionRequest(u8 *request);
asm(".global gMenuContext\n.set gMenuContext,0x03002810\n.global AdvanceSelectionRequest\n.thumb_set AdvanceSelectionRequest,0x08017181\n");

u32 AdvancePanelCloseRequest(u32 ordinal) __asm__("CoreRegion_00037FF0");
u32 AdvancePanelCloseRequest(u32 ordinal)
{
    u8 **cell = &gMenuContext;
    ordinal *= 204;
    return (u8)AdvanceSelectionRequest((u8 *)(ordinal + (u32)*cell + 0x9a0));
}
