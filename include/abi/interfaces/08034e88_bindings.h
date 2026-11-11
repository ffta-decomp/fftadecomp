typedef unsigned char u8;
typedef unsigned int u32;
struct InventoryRequestState { u8 unknown_00[0x4b8]; u8 primary; u8 secondary; u8 tertiary; };
extern struct InventoryRequestState *InventoryRequestRoot;
extern void DispatchInventoryRequestControllers(void) __asm__("CoreRegion_00034E88");
extern void UpdateInventoryRequestInput(void);
extern void RunRequest43468(u32 phase);
extern void RunInventorySelection(u32 phase);
extern void RunRequest3BAE8(u32 phase);
extern void RunRequest39424(u32 phase);
extern void RunRequest3A07C(u32 phase);
extern void RunRemovalStaging(u32 phase);
extern void RunInventoryProgression(u32 phase);
extern void RunRequest3D550(u32 phase);
extern void RunRequest3DC1C(u32 phase);
extern void RunRequest3DE40(u32 phase);
extern void RunRequest4393C(u32 phase);
extern void RunRequest3C21C(u32 phase);
extern void RunRequest3CA18(u32 phase);
extern void RunRequest3F6F8(u32 phase);
extern void RunRequest49FB4(u32 phase);
extern void RunRequest4AFE0(u32 phase);
extern void RunRequest3D820(u32 phase);
extern void RunRequest4B7E8(u32 phase);
__asm__(".global InventoryRequestRoot\n.set InventoryRequestRoot, 0x03002810\n"
        ".thumb_set UpdateInventoryRequestInput, 0x08034c95\n"
        ".thumb_set RunRequest43468, 0x08043469\n"
        ".thumb_set RunInventorySelection, 0x0803ae81\n"
        ".thumb_set RunRequest3BAE8, 0x0803bae9\n"
        ".thumb_set RunRequest39424, 0x08039425\n"
        ".thumb_set RunRequest3A07C, 0x0803a07d\n"
        ".thumb_set RunRemovalStaging, 0x0803e3b5\n"
        ".thumb_set RunInventoryProgression, 0x08046a4d\n"
        ".thumb_set RunRequest3D550, 0x0803d551\n"
        ".thumb_set RunRequest3DC1C, 0x0803dc1d\n"
        ".thumb_set RunRequest3DE40, 0x0803de41\n"
        ".thumb_set RunRequest4393C, 0x0804393d\n"
        ".thumb_set RunRequest3C21C, 0x0803c21d\n"
        ".thumb_set RunRequest3CA18, 0x0803ca19\n"
        ".thumb_set RunRequest3F6F8, 0x0803f6f9\n"
        ".thumb_set RunRequest49FB4, 0x08049fb5\n"
        ".thumb_set RunRequest4AFE0, 0x0804afe1\n"
        ".thumb_set RunRequest3D820, 0x0803d821\n"
        ".thumb_set RunRequest4B7E8, 0x0804b7e9\n" );
