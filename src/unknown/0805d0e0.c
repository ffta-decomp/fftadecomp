typedef unsigned char u8;typedef unsigned int u32;
extern void InitializePubPanelStorage(u32) asm("RetailCall_0805F3C4");
extern void ClosePubPanelStorage(void) asm("RetailCall_0805F414");
void AdvancePubPanelLifetime(void*,u8*) asm("SceneRegisteredRoot_0005D0E0");
void AdvancePubPanelLifetime(void *unused_context,u8 *state)
{
    switch(*state) {
    case 0:
        InitializePubPanelStorage(12288);
        *state=1;
        break;
    case 255:
        ClosePubPanelStorage();
        break;
    }
}
__asm__(".global RetailCall_0805F3C4\n.thumb_set RetailCall_0805F3C4,0x0805F3C5");
__asm__(".global RetailCall_0805F414\n.thumb_set RetailCall_0805F414,0x0805F415");
