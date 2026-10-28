typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TaskGroup;
struct TaskNode;
struct ActionContext { u16 result; u8 ready, active, mode; u8 unknown[27]; struct TaskGroup *group; };
struct Request { u32 unknown[5]; u16 payload; u16 tail[3]; };
extern struct ActionContext *gActionContext;
extern u32 AdvanceActionChoice(struct TaskNode *, u16 *, u8 *);
extern struct TaskNode *CreateTaskNode(struct TaskGroup *, u32 (*)(struct TaskNode *,u16 *,u8 *),u32,const u32 *,struct TaskNode *);
__asm__(".global gActionContext\n.set gActionContext,0x0200f438\n.global AdvanceActionChoice\n.thumb_set AdvanceActionChoice,0x080293dd\n.global CreateTaskNode\n.thumb_set CreateTaskNode,0x08005955");
typedef char request_size_check[sizeof(struct Request)==28?1:-1];
typedef char group_offset_check[(u32)&((struct ActionContext *)0)->group==32?1:-1];
void BeginBattleActionChoice(void) __asm__("CoreGlobal36_00025720");
void BeginBattleActionChoice(void)
{
    struct Request request;
    gActionContext->active = 0;
    gActionContext->mode = 11;
    gActionContext->result = 0;
    /* Only payload is initialized in the native 28-byte event template. */
    request.payload = 10;
    CreateTaskNode(gActionContext->group, AdvanceActionChoice,164,(const u32 *)&request,0);
}
