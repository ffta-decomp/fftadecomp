typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct TaskNode;
typedef u32 (*TaskCallback)(struct TaskNode*,u16*,void*);
extern TaskCallback GetDefinitionTaskCallback(struct TaskNode*);
extern s16 *GetDefinitionTaskPayload(struct TaskNode*);
extern u32 GetDefinitionTaskState(struct TaskNode*);
extern u32 AdvanceDefinitionTransition(struct TaskNode*,u16*,void*);
extern u32 AdvanceDefinitionPointTransition(struct TaskNode*,u16*,void*);
extern u32 AdvanceAlternateDefinitionTransition(struct TaskNode*,u16*,void*);
extern void ReleaseDefinitionTask(struct TaskNode*);
struct TaskNode *ReleaseFinishedDefinitionTransition(struct TaskNode*) __asm__("RemainingBand43_000D6530");
struct TaskNode *ReleaseFinishedDefinitionTransition(struct TaskNode *task)
{
    if(task) {
        TaskCallback callback=GetDefinitionTaskCallback(task);
        register u32 finished __asm__("r0");
        if(callback==AdvanceDefinitionTransition || callback==AdvanceDefinitionPointTransition) {
            s16 *state=GetDefinitionTaskPayload(task);
            if(*state==4) {
                finished=1;
                /* This path has its own native numeric-result definition before
                   the callback literal pool; retain that defined lifetime. */
                __asm__("" : "+r"(finished));
            }
            else finished=0;
        }else if(callback==AdvanceAlternateDefinitionTransition) {
            if((u16)GetDefinitionTaskState(task)==260)finished=1;
            else finished=0;
        }else finished=0;
        /* The native join holds a defined numeric 0/1 before the cleanup test.
           This instruction-free constraint preserves that value/lifetime. */
        __asm__("" : "+r"(finished));
        if(finished) {
            ReleaseDefinitionTask(task);
            return 0;
        }
    }
    return task;
}
__asm__(".global GetDefinitionTaskCallback\n.thumb_set GetDefinitionTaskCallback,0x08005c01\n.global GetDefinitionTaskPayload\n.thumb_set GetDefinitionTaskPayload,0x08005bfd\n.global GetDefinitionTaskState\n.thumb_set GetDefinitionTaskState,0x08005bad\n.global AdvanceDefinitionTransition\n.thumb_set AdvanceDefinitionTransition,0x080d5129\n.global AdvanceDefinitionPointTransition\n.thumb_set AdvanceDefinitionPointTransition,0x080d5595\n.global AdvanceAlternateDefinitionTransition\n.thumb_set AdvanceAlternateDefinitionTransition,0x080d5a61");

__asm__(".global ReleaseDefinitionTask\n.thumb_set ReleaseDefinitionTask,0x08005b59");
