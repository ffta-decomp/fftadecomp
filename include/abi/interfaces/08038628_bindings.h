typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
struct CategoryBankState {u8 unknown00[0x1f3c];u16 entries[20];};
extern struct CategoryBankState gCategoryBankState;
asm(".global gCategoryBankState\n.set gCategoryBankState,0x02000000");
