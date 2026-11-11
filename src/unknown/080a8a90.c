typedef unsigned int u32;
struct OwnerRecord;
struct OwnerCommandSequence;
extern void *AllocateBattleRecordMemory(u32 bytes);
extern void InitializeOwnerCommandSequence(struct OwnerCommandSequence *sequence,
                                         struct OwnerRecord *owner);
__asm__(".global AllocateBattleRecordMemory\n.thumb_set AllocateBattleRecordMemory, 0x08022841\n.global InitializeOwnerCommandSequence\n.thumb_set InitializeOwnerCommandSequence, 0x080a7d61");
/* Retail passes allocation failure through to the initializer without a guard. */
struct OwnerCommandSequence *CreateOwnerCommandSequence(struct OwnerRecord *owner)
{
    struct OwnerCommandSequence *sequence = AllocateBattleRecordMemory(80);
    InitializeOwnerCommandSequence(sequence, owner);
    return sequence;
}
