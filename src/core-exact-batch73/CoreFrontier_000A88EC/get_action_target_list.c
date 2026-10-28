typedef unsigned int u32;
void *GetBattleActionTargetList(void *root, u32 index)
    __asm__("CoreFrontier_000A88EC");

/* Keep the observed stride and native word wrapping without inventing bounds. */
void *GetBattleActionTargetList(void *root, u32 index)
{
    u32 list_offset = index * 708u;
    return (void *)((u32)root + list_offset);
}
