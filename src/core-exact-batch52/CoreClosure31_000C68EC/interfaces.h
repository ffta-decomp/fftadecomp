typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct FollowupUnit;
struct FollowupRecord { struct FollowupUnit *unit; };
struct FollowupContext;
struct BattleFollowupState {
    u8 unknown_000[96];
    struct FollowupContext *context;
    struct FollowupUnit *selected_units[2];
    u8 unknown_108[13];
    u8 selected_count;
    u8 unknown_122[2];
    u16 phase;
    u16 phase_depth;
    u16 phase_stack[34];
};
typedef char FollowupSize[(sizeof(struct BattleFollowupState)==196)?1:-1];
typedef char FollowupCountOffset[((u32)&((struct BattleFollowupState*)0)->selected_count==121)?1:-1];
extern void (*const ClearFollowupMemory)(void *, s32);
extern s32 CollectFollowupRecords(struct FollowupContext *, struct FollowupRecord **);
extern u32 IsFollowupUnitInRoster(struct FollowupUnit *);
__asm__(".global ClearFollowupMemory\n.set ClearFollowupMemory,0x0836d4b8\n"
        ".global CollectFollowupRecords\n.thumb_set CollectFollowupRecords,0x08099cdd\n"
        ".global IsFollowupUnitInRoster\n.thumb_set IsFollowupUnitInRoster,0x08133bc5\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");
