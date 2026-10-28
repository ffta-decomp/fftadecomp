#ifndef BATTLE_TURN_SELECTION_21_H
#define BATTLE_TURN_SELECTION_21_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern void *AllocateBattleRecordBlock(unsigned int size);
extern void ReleaseBattleObject(void *allocation);
extern void InitializeBattleTurnState(u8 *state, const void *setup);
extern s32 RunBattleTurnManager(u8 *state);

#define TURN_WORD(base, offset) (*(volatile u32 *)((u8 *)(base) + (offset)))
#define TURN_HALF(base, offset) (*(volatile u16 *)((u8 *)(base) + (offset)))

#endif

__asm__(".global RetailCall_08096d7c\n.thumb_set RetailCall_08096d7c,0x08096d7d\n"
        ".global CollectBattleTurnUnitPointers_0809F78C\n.thumb_set CollectBattleTurnUnitPointers_0809F78C,0x0809f78d\n");
