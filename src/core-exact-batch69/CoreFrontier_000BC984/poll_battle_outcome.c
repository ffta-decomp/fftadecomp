typedef unsigned char u8;
typedef unsigned int u32;

/* Retain the real outcome state machine and its side effects. */
extern u32 PollBattleOutcomeContext(void *context) __asm__("RetailCall_080bbe00");

__asm__(".global RetailCall_080bbe00\n.thumb_set RetailCall_080bbe00,0x080bbe01\n");

u8 PollBattleOutcomeByte(void *context)
{
    return (u8)PollBattleOutcomeContext(context);
}
