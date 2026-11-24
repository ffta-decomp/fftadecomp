typedef unsigned char u8;
typedef unsigned int u32;
extern void SetSelectionControlMode(void *,u32) asm("RetailCall_08017508");
extern void ReplaceRequestFlags(void *,u8) asm("RetailCall_08017d18");
void SetSelectionModeAndResetRequests(u8 *control,u32 mode) asm("SceneTaskDependency_0002A290");
void SetSelectionModeAndResetRequests(u8 *control,u32 mode) { SetSelectionControlMode(control,(u8)mode); ReplaceRequestFlags(control+76,0); ReplaceRequestFlags(control+96,0); }
asm(".global RetailCall_08017508\n.thumb_set RetailCall_08017508,0x08017509\n.global RetailCall_08017d18\n.thumb_set RetailCall_08017d18,0x08017d19\n");
