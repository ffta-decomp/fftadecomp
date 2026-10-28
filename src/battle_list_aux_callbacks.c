typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ListOwner;
extern void *GetListOwnerWord0(const struct ListOwner *owner);

#ifdef BATTLE_LIST_FLAG_UPDATE
struct BattleListFlagUpdate {
    u16 clear_mask;
    u16 set_mask;
};

u32 ApplyBattleListFlagUpdate(const struct ListOwner *owner,
                              const struct BattleListFlagUpdate *update)
{
    u32 *flags = GetListOwnerWord0(owner);
    u16 clear_mask = update->clear_mask;
    u16 set_mask = update->set_mask;
    u32 next = *flags;
    next &= ~clear_mask;
    next |= set_mask;
    *flags = next;
    return 1;
}
#endif

#ifdef BATTLE_RECORD_ACTIVE_MARK
struct BattleRecord {
    u32 flags;
    u8 unknown_at_04[40];
    void *object;
};

u32 MarkActiveBattleRecord(const struct ListOwner *owner, u8 *active)
{
    const struct BattleRecord *record = GetListOwnerWord0(owner);
    if ((record->flags & 0x80000) == 0 && record->object != 0)
        *active = 0;
    return 1;
}
#endif
