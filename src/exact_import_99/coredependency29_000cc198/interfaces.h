typedef unsigned char u8;typedef signed short s16;typedef unsigned int u32;
struct CategoryState {u8 prefix[0x2e5e];u8 active_a,active_b,upcoming_a,upcoming_b;};
extern struct CategoryState gCategoryState;extern u8 gUpcomingPair[2];extern u32 NRandom(void);
asm(".global gCategoryState\n.set gCategoryState,0x02000000\n.global gUpcomingPair\n.set gUpcomingPair,0x02002e60\n.global NRandom\n.thumb_set NRandom,0x08002805\n.global __modsi3\n.thumb_set __modsi3,0x08142951");
