typedef unsigned short u16;
/* The consumer stores this low handle word; its wider identity is unproved. */
u16 GetBattleTargetHandleLowWord(const u16 *handle)
{
    return *handle;
}
