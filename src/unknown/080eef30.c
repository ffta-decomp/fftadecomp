typedef unsigned short u16;
typedef unsigned int u32;
struct Task;
extern u32 GetTaskState(struct Task*);
u32 IsActionEffectChildAtState258(struct Task*) __asm__("RemainingBand43_000EEF30");
u32 IsActionEffectChildAtState258(struct Task *task)
{
    if((u16)GetTaskState(task)==258)
        return 1;
    return 0;
}
__asm__(".global GetTaskState\n.thumb_set GetTaskState,0x08005bad");
