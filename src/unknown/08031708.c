typedef unsigned char u8;
extern u8 gSharedPanelState;
/* Numeric modes remain neutral; callers save/restore this panel state. */
void SetSharedPanelState(u8 state) { gSharedPanelState=state; }
asm(".global gSharedPanelState\n.set gSharedPanelState,0x030027a4");
