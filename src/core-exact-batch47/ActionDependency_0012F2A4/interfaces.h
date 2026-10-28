typedef unsigned char u8;
typedef unsigned short u16;
extern u8 gBattleActionState[];
extern void InitializePreservedActionState(void *state, u16 first_id, u16 second_id, u8 mode);
__asm__(".global gBattleActionState\n.set gBattleActionState,0x0200f3f0\n.global InitializePreservedActionState\n.thumb_set InitializePreservedActionState,0x0812f231");
