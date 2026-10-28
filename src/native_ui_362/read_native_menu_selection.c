typedef unsigned char u8;
typedef signed short s16;

struct NativeMenuPanelSelection {
    u8 unknown00[20];
    s16 selection;
};
extern struct NativeMenuPanelSelection *gNativeMenuPanel;
__asm__(".global gNativeMenuPanel\n.set gNativeMenuPanel,0x0200F44C\n");
int ReadNativeMenuSelection(void) __asm__("CoreFrontier_00060DC4");
int ReadNativeMenuSelection(void)
{
    return gNativeMenuPanel->selection;
}
