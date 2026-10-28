typedef unsigned char u8;typedef unsigned short u16;
struct ActorSequence;
unsigned int AdvanceSequence(struct ActorSequence *,u16) __asm__("RetailCall_080bc584");
u8 CoreFrontier_000BCA40(struct ActorSequence *record,unsigned int input)
{
    return (u8)AdvanceSequence(record,(u16)input);
}
asm(".global RetailCall_080bc584\n.thumb_set RetailCall_080bc584,0x080bc585\n");
