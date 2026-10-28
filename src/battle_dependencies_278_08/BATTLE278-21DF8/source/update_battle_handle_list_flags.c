typedef unsigned short u16;
typedef unsigned int u32;
struct ListOwner;
struct BattleListFlagUpdate { u16 clear_mask, set_mask; };
union PackedFlagUpdate { u32 packed; struct BattleListFlagUpdate masks; };
struct FlagListHandle { u32 primary; struct ListOwner *list; };
typedef u32 (*FlagVisitor)(const struct ListOwner *, const struct BattleListFlagUpdate *);
extern u32 ApplyBattleListFlagUpdate(const struct ListOwner *, const struct BattleListFlagUpdate *);
extern void VisitBattleFlagNodes(const struct ListOwner *, FlagVisitor, const struct BattleListFlagUpdate *);
__asm__(".global ApplyBattleListFlagUpdate\n.thumb_set ApplyBattleListFlagUpdate,0x08022149\n.global VisitBattleFlagNodes\n.thumb_set VisitBattleFlagNodes,0x080c7cc1");

void UpdateBattleHandleListFlags(struct FlagListHandle *handle, u16 clear_mask, u16 set_mask)
{
    union PackedFlagUpdate update;
    if (handle != 0) {
        update.packed = ((u32)set_mask << 16) | clear_mask;
        if (handle->list != 0)
            VisitBattleFlagNodes(handle->list, ApplyBattleListFlagUpdate, &update.masks);
    }
}
