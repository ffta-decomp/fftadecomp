extern void FreeBattleAllocation(void *allocation);
asm(".global FreeBattleAllocation\n.thumb_set FreeBattleAllocation,0x08022855");
void ReleaseBattleOwnedPayload(void *allocation)
{
    FreeBattleAllocation(allocation);
}
