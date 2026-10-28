typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
struct ChoicePayload { u8 before_mode[8]; u8 mode; u8 before_target[7]; struct TaskNode *target; };
struct ChoiceTaskEvent { u16 code; u8 unspecified2_27[26]; };
typedef char ChoiceTaskEventSize28[sizeof(struct ChoiceTaskEvent)==28?1:-1];
extern struct ChoicePayload *GetTaskPayload(struct TaskNode *);
extern u32 InvokeTaskCallback(struct TaskNode *,void *);
asm(".global GetTaskPayload\n.thumb_set GetTaskPayload,0x08005bfd\n.global InvokeTaskCallback\n.thumb_set InvokeTaskCallback,0x08005c05");
void AdvanceApplicationChildChoice(struct TaskNode *node)
{
    struct ChoicePayload *payload = GetTaskPayload(node);
    struct ChoiceTaskEvent event;
    if (payload->mode == 7)
        event.code = 259;
    else
        event.code = 262;
    InvokeTaskCallback(payload->target,&event);
}
