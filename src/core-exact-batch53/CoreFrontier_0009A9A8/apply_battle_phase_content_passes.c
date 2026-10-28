#include "interfaces.h"

asm(".global SortBattlePhaseContent\n"
    ".thumb_set SortBattlePhaseContent, 0x08098c21\n"
    ".global ApplyBattlePhaseStatePass\n"
    ".thumb_set ApplyBattlePhaseStatePass, 0x08098ce9\n");

void ApplyBattlePhaseContentPasses(void *content)
    __asm__("CoreFrontier_0009A9A8");

void ApplyBattlePhaseContentPasses(void *content)
{
    SortBattlePhaseContent(content);
    ApplyBattlePhaseStatePass(content);
}
