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
u32 IsDefinitionTransitionComplete(struct TaskNode*) __asm__("RemainingBand43_000D6478");
u32 IsDefinitionTransitionComplete(struct TaskNode *task)
{
    TaskCallback callback=GetDefinitionTaskCallback(task);
    if(callback==AdvanceDefinitionTransition || callback==AdvanceDefinitionPointTransition) {
        s16 *state=GetDefinitionTaskPayload(task);
        if(*state>2)return 1;
    }else if(callback==AdvanceAlternateDefinitionTransition) {
        if((u16)GetDefinitionTaskState(task)>259)return 1;
    }
    return 0;
}
__asm__(".global GetDefinitionTaskCallback\n.thumb_set GetDefinitionTaskCallback,0x08005c01\n.global GetDefinitionTaskPayload\n.thumb_set GetDefinitionTaskPayload,0x08005bfd\n.global GetDefinitionTaskState\n.thumb_set GetDefinitionTaskState,0x08005bad\n.global AdvanceDefinitionTransition\n.thumb_set AdvanceDefinitionTransition,0x080d5129\n.global AdvanceDefinitionPointTransition\n.thumb_set AdvanceDefinitionPointTransition,0x080d5595\n.global AdvanceAlternateDefinitionTransition\n.thumb_set AdvanceAlternateDefinitionTransition,0x080d5a61");
