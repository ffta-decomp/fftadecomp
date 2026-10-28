typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleResultWorkspace;
/* The native wrapper passes all three slots; the retained helper ignores the
 * third slot after replacing r2 with its own narrowed first argument. */
extern u32 PollBattleResultWorkspace(struct BattleResultWorkspace *workspace,
                                    u16 argument1, u16 reserved_argument2);
u32 PollMergedBattleResultWorkspace(struct BattleResultWorkspace *workspace,
                                    u32 argument1, u32 argument2)
{
    return (u8)PollBattleResultWorkspace(workspace, (u16)argument1,
                                        (u16)argument2);
}
asm(".global PollBattleResultWorkspace\n.thumb_set PollBattleResultWorkspace,0x080A75BD\n");
