typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleResultList { u8 storage[193]; u8 count; };
extern u32 RetailCall_080a6f20(u32);
extern u32 GetGameFlag(u16);
extern void SetGameFlag(u16,u32);
extern u32 RetailCall_080a780c(void *,u32,u32,u32);
asm(".global RetailCall_080a6f20\n.thumb_set RetailCall_080a6f20,0x080a6f21\n.global GetGameFlag\n.thumb_set GetGameFlag,0x080c9541\n.global SetGameFlag\n.thumb_set SetGameFlag,0x080c9575\n.global RetailCall_080a780c\n.thumb_set RetailCall_080a780c,0x080a780d");
