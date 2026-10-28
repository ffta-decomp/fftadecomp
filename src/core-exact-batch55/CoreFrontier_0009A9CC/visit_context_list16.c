#include "interfaces.h"

asm(".global VisitLinkedNodes\n"
    ".thumb_set VisitLinkedNodes, 0x080c7cc1\n"
    ".global VisitListOwnerWord\n"
    ".thumb_set VisitListOwnerWord, 0x0809abe9\n"
    ".global CoreRegion30_0009ADDC\n"
    ".thumb_set CoreRegion30_0009ADDC, 0x0809addd\n");

void VisitBattlePhaseContextList16(struct BattlePhaseContext *context)
    __asm__("CoreFrontier_0009A9CC");

void VisitBattlePhaseContextList16(struct BattlePhaseContext *context)
{
    struct WordVisitor visitor;
    WordCallback callback;

    callback = CoreRegion30_0009ADDC;
    visitor.argument = 0;
    visitor.callback = callback;
    VisitLinkedNodes(context->list_owner_at_16, VisitListOwnerWord, &visitor);
}
