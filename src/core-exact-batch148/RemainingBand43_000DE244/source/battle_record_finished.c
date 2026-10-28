typedef unsigned char u8;
typedef unsigned int u32;
struct Actor;
extern u32 HasPendingFlag(struct Actor *);
extern u32 PollBattleRecordHandles(struct Actor *);
__asm__(".global HasPendingFlag\n.thumb_set HasPendingFlag,0x08099c9d\n.global PollBattleRecordHandles\n.thumb_set PollBattleRecordHandles,0x08099c65");
u32 RemainingBand43_000DE244(struct Actor *actor)
{
 if((u8)HasPendingFlag(actor) != 0) return 0;
 return (u8)PollBattleRecordHandles(actor);
}
