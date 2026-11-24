#ifndef SOURCE233_BC878_INTERFACES_H
#define SOURCE233_BC878_INTERFACES_H
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef void (*BattleContextClearFunction)(u8 *destination, s32 byte_count);
extern BattleContextClearFunction const gBattleCallbackContextClear;
extern void InitializeBattleCallbackContextBody(u8 *context, const void *record,
                                                u32 state_byte, u32 option_byte);
__asm__(".global gBattleCallbackContextClear\n.set gBattleCallbackContextClear,0x0836d4b8\n.global InitializeBattleCallbackContextBody\n.thumb_set InitializeBattleCallbackContextBody,0x080bb5c5");
#endif
