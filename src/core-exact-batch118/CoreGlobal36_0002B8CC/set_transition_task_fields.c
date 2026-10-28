typedef unsigned char u8;
typedef unsigned short u16;
struct TaskNode;
typedef struct { u8 prefix[21]; u8 flag; u16 value; } TransitionPayload;
extern TransitionPayload *GetTransitionPayload(struct TaskNode *);
asm(".thumb_set GetTransitionPayload, 0x08005BFD\n");
void CoreGlobal36_0002B8CC(struct TaskNode *node, u8 flag, u16 value)
{
    TransitionPayload *payload = GetTransitionPayload(node);
    payload->flag = flag;
    payload->value = value;
}
