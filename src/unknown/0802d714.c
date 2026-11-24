typedef unsigned char u8;
typedef unsigned int u32;
struct UnitTaskCompletionView {
    u8 unaccessed_prefix[913];
    u8 completion_notification;
};
extern struct UnitTaskCompletionView *gUnitTaskContext;
typedef char NotificationOffset[(u32)&((struct UnitTaskCompletionView *)0)->completion_notification == 913 ? 1 : -1];
/* EndBattleActionWorkspace invokes this after releasing its record containers. */
void NotifyUnitTaskWorkspaceEnded(void)
{
    gUnitTaskContext->completion_notification = 1;
}
asm(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200F440\n");
