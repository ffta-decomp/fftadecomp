struct OwnerCommandSequence;
extern void ReleaseBattleRecordMemory(void *pointer);
__asm__(".global ReleaseBattleRecordMemory\n.thumb_set ReleaseBattleRecordMemory, 0x08022855");
void DestroyOwnerCommandSequence(struct OwnerCommandSequence *sequence)
{
    ReleaseBattleRecordMemory(sequence);
}
