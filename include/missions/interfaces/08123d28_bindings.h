#ifndef STORY_CHOICE_BRANCH_H
#define STORY_CHOICE_BRANCH_H
#include "ffta/unsigned_types.h"
struct ChoiceScriptState { u16 offset; };
struct ChoiceBranchCommand { u8 opcode; u8 delta_low; u8 delta_high; };
extern u32 ReadConfirmedStoryChoice(void);
__asm__(".global ReadConfirmedStoryChoice\n.thumb_set ReadConfirmedStoryChoice,0x08013381");
#endif
