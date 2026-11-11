struct BattleFollowupState;
struct FollowupContext;
extern void InitializeBattleFollowup_080C68EC(struct BattleFollowupState *, struct FollowupContext *);
void BeginBattleFollowupSelection(struct BattleFollowupState *state, struct FollowupContext *context)
{
    InitializeBattleFollowup_080C68EC(state, context);
}
asm(".thumb_set InitializeBattleFollowup_080C68EC,0x080c68ed\n");
