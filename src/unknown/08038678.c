typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { unsigned char before[0x1f3c]; u16 slots[20]; } SaveBank;
extern SaveBank gSavedCategoryBank;
void ClearSavedCategorySlot(u16 slot) asm("CoreFrontier_00038678");
void ClearSavedCategorySlot(u16 slot) { gSavedCategoryBank.slots[slot] = 0; }
asm(".global gSavedCategoryBank\n.set gSavedCategoryBank, 0x02000000\n");
