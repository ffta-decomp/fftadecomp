typedef unsigned char u8;
typedef unsigned int u32;

enum { BATTLE_OBJECT_STRIDE = 0x98a };

/* InitializeBattleObjectStatePool stores the active pool pointer here. */
u8 *GetBattleObjectStatePool(void)
{
    return *(u8 **)0x0300616c;
}

/* The same stride advances between objects during pool initialization. */
u32 BattleObjectIndexOffset(u8 index)
{
    return index * BATTLE_OBJECT_STRIDE;
}
