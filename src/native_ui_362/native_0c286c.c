typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef struct UnitNode { void *unit; } UnitNode;
typedef struct Context {
    u8 unknown0[4];
    UnitNode *target;
    u8 unknown8[80];
    u16 count, ordinal;
    u8 primary_rows[0x2968-92];
    u8 alternate_rows[0x5270-0x2968];
    s16 rule_operand;
    u8 unknown5272[13];
    u8 next_candidate, phase;
} Context;
typedef char CheckPhase[((int)&((Context*)0)->phase==0x5280)?1:-1];
extern void RetailCall_0812f0d8(void *,u16 *);
extern u8 RetailCall_080c26ec(void *,UnitNode **,u16,int,int,int);
int AdvanceBattleCandidateSets(Context *context) __asm__("CoreRegion30_000C286C");
int AdvanceBattleCandidateSets(Context *context)
{
    u16 equipment;
    u16 *ordinal;
    u8 phase;
    RetailCall_0812f0d8(context->target->unit,&equipment);
    ordinal=&context->ordinal;
    if (*ordinal>=context->count) return 0;
    phase=context->phase;
    switch(phase) {
    case 0:
        context->next_candidate=RetailCall_080c26ec(context->alternate_rows,
            &context->target,equipment,0,context->rule_operand,context->next_candidate);
        if (context->next_candidate==255) {
            context->next_candidate=phase;
            context->phase=1;
        }
        break;
    case 1:
        context->next_candidate=RetailCall_080c26ec(context->primary_rows,
            &context->target,equipment,0,context->rule_operand,context->next_candidate);
        if (context->next_candidate==255) {
            register unsigned int reset __asm__("r0") = 0;
            /* Native post-sentinel definition, consumed only by this clear. */
            __asm__("" : "+r"(reset));
            context->next_candidate=reset;
            context->phase=phase;
            {
                unsigned int next_ordinal = *ordinal + 1;
                register unsigned int phase_zero __asm__("r1") = 0;
                /* Distinct native zero while the updated ordinal is live. */
                __asm__("" : "+r"(phase_zero));
                *ordinal=next_ordinal;
                context->phase=phase_zero;
            }
        }
        break;
    }
    return 1;
}
asm(".global RetailCall_0812f0d8\n.thumb_set RetailCall_0812f0d8,0x0812f0d9\n.global RetailCall_080c26ec\n.thumb_set RetailCall_080c26ec,0x080c26ed\n");
