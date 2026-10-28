typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SavedOptionContext { u16 state; };
extern struct SavedOptionContext *SavedOptionsContext;
extern void InitializeSavedOptionCells(void);
extern u32 AdvanceSavedOptionMenu(void);
extern void ReleaseSavedOptionMenu(void);
asm(".global SavedOptionsContext\n.set SavedOptionsContext,0x02009188\n"
    ".thumb_set InitializeSavedOptionCells,0x080088d9\n"
    ".thumb_set AdvanceSavedOptionMenu,0x08008955\n"
    ".thumb_set ReleaseSavedOptionMenu,0x08008939\n");

u32 RunSavedOptions(void)
{
    if (SavedOptionsContext == 0)
        return 1;
    switch (SavedOptionsContext->state) {
    case 0:
        InitializeSavedOptionCells();
        SavedOptionsContext->state = 1;
        break;
    case 1:
        if ((u8)AdvanceSavedOptionMenu() != 0)
            SavedOptionsContext->state = 2;
        break;
    case 2:
        ReleaseSavedOptionMenu();
        return 1;
    }
    return 0;
}
