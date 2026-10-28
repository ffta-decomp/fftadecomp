typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct TaskNode;
typedef u32 (*TaskCallback)(struct TaskNode*,u16*,void*);
extern TaskCallback GetDefinitionTaskCallback(struct TaskNode*);
extern s16 *GetDefinitionTaskPayload(struct TaskNode*);
extern u32 GetDefinitionTaskState(struct TaskNode*);
extern u32 AdvanceDefinitionTransition(struct TaskNode*,u16*,void*);
extern u32 AdvanceDefinitionPointTransition(struct TaskNode*,u16*,void*);
extern u32 AdvanceAlternateDefinitionTransition(struct TaskNode*,u16*,void*);
extern void SetDefinitionTaskState(struct TaskNode*,u32);
u32 RequestDefinitionTransitionAdvance(struct TaskNode*) __asm__("RemainingBand43_000D5C20");
u32 RequestDefinitionTransitionAdvance(struct TaskNode *task)
{
    TaskCallback original=GetDefinitionTaskCallback(task);
    if(original==AdvanceDefinitionTransition || original==AdvanceDefinitionPointTransition) {
        s16 *state=GetDefinitionTaskPayload(task);
        if(*state!=1)return 0;
        *state=2;
    }else if(original==AdvanceAlternateDefinitionTransition) {
        TaskCallback current=GetDefinitionTaskCallback(task);
        s32 payload_state;
        register u32 ready __asm__("r0");
        if(current==AdvanceDefinitionTransition) {
            payload_state=*GetDefinitionTaskPayload(task);
            goto compare_payload;
        }else if(current==AdvanceDefinitionPointTransition) {
            payload_state=*GetDefinitionTaskPayload(task);
compare_payload:
            if(payload_state==1) {
                ready=1;
                /* Preserve this native result definition before the next case. */
                __asm__("" : "+r"(ready));
            }else ready=0;
        }else if(current==original) {
            if((u16)GetDefinitionTaskState(task)==258)ready=1;
            else ready=0;
        }else ready=0;
        /* Every predecessor defines the real numeric predicate before this test. */
        __asm__("" : "+r"(ready));
        if(!ready)return 0;
        SetDefinitionTaskState(task,259);
    }
    return 1;
}
__asm__(".global GetDefinitionTaskCallback\n.thumb_set GetDefinitionTaskCallback,0x08005c01\n.global GetDefinitionTaskPayload\n.thumb_set GetDefinitionTaskPayload,0x08005bfd\n.global GetDefinitionTaskState\n.thumb_set GetDefinitionTaskState,0x08005bad\n.global AdvanceDefinitionTransition\n.thumb_set AdvanceDefinitionTransition,0x080d5129\n.global AdvanceDefinitionPointTransition\n.thumb_set AdvanceDefinitionPointTransition,0x080d5595\n.global AdvanceAlternateDefinitionTransition\n.thumb_set AdvanceAlternateDefinitionTransition,0x080d5a61");

__asm__(".global SetDefinitionTaskState\n.thumb_set SetDefinitionTaskState,0x08005ba9");
