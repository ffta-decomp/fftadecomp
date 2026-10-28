typedef unsigned short u16;
struct ActionDecision;
unsigned int AdvanceDecision(struct ActionDecision *,u16,u16) __asm__("RetailCall_080b5a08");
unsigned int CoreFrontier_000B7E08(struct ActionDecision *record,unsigned int first,unsigned int second)
{
    return AdvanceDecision(record,(u16)first,(u16)second);
}
asm(".global RetailCall_080b5a08\n.thumb_set RetailCall_080b5a08,0x080b5a09\n");
