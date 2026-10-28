typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitRecord;
struct TaskNode;
struct TaskGroup;
struct UnitTaskRequest {
    u16 operation;
    u16 unused2;
    struct UnitRecord *unit;
    u8 unknown8[12];
    u16 flags;
    u8 unknown22[6];
};
struct UnitTaskContextView {
    struct TaskGroup *group;
    u32 unknown4;
    struct TaskNode *primary;
    struct TaskNode *secondary;
    u8 unknown16[897];
    u8 pending;
};
struct UnitTaskRingRecord;
typedef u32 (*UnitTaskCallback)(struct TaskNode *, u16 *, u8 *);
extern struct UnitTaskContextView *gUnitTaskContext;
extern void PrepareUnitTaskDisplay(void *ignored_request);
extern struct UnitTaskRingRecord *TakeUnitTaskRingRecord(void);
extern void ApplyUnitTaskVisualBuffer(struct UnitTaskRingRecord *);
extern u16 ReadTaskState(struct TaskNode *);
extern void WriteTaskState(struct TaskNode *, u16);
extern u32 InvokeTaskCallback(struct TaskNode *, const struct UnitTaskRequest *);
extern struct TaskNode *CreateTaskNode(struct TaskGroup *, UnitTaskCallback, u32,
                                       const u32 *, struct TaskNode *);
extern u32 PrimaryUnitTask(struct TaskNode *, u16 *, u8 *);
extern u32 SecondaryUnitTask(struct TaskNode *, u16 *, u8 *);
__asm__(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200f440\n.global PrepareUnitTaskDisplay\n.thumb_set PrepareUnitTaskDisplay,0x08022b25\n.global TakeUnitTaskRingRecord\n.thumb_set TakeUnitTaskRingRecord,0x0802ba09\n.global ApplyUnitTaskVisualBuffer\n.thumb_set ApplyUnitTaskVisualBuffer,0x0802b5a9\n.global ReadTaskState\n.thumb_set ReadTaskState,0x08005bad\n.global WriteTaskState\n.thumb_set WriteTaskState,0x08005ba9\n.global InvokeTaskCallback\n.thumb_set InvokeTaskCallback,0x08005c05\n.global CreateTaskNode\n.thumb_set CreateTaskNode,0x08005955\n.global PrimaryUnitTask\n.thumb_set PrimaryUnitTask,0x0802d0b1\n.global SecondaryUnitTask\n.thumb_set SecondaryUnitTask,0x0802d551");
typedef char request_size_check[sizeof(struct UnitTaskRequest)==28?1:-1];
typedef char request_flags_check[(u32)&((struct UnitTaskRequest *)0)->flags==20?1:-1];
typedef char pending_offset_check[(u32)&((struct UnitTaskContextView *)0)->pending==913?1:-1];
/* Separate branch continuations and every post-callback global/task reload
 * are part of this unit-task transaction. Unassigned request bytes stay so. */
struct TaskNode *CreateOrReuseUnitTask(struct UnitRecord *unit, u16 flags)
{
    u32 primary_flags = flags;
    u32 task_state;
    struct TaskNode *task;
    register struct TaskNode *created __asm__("r0");
    struct UnitTaskRingRecord *visual;
    struct UnitTaskRequest request;
    request.unit = unit;
    request.flags = flags;
    /* Actual callee ignores R0; the original caller still supplies this value. */
    PrepareUnitTaskDisplay(&request);
    if (flags & 1) {
        if (gUnitTaskContext->pending != 0) {
            visual = TakeUnitTaskRingRecord();
            TakeUnitTaskRingRecord();
            ApplyUnitTaskVisualBuffer(visual);
            gUnitTaskContext->pending = 0;
        }
        task = gUnitTaskContext->secondary;
        if (task != 0) {
            task_state = ReadTaskState(task);
            if ((flags & 32) && task_state == 0x102) {
                request.operation = 0x10a;
                InvokeTaskCallback(gUnitTaskContext->secondary, &request);
                WriteTaskState(gUnitTaskContext->secondary, 0x10b);
            } else {
                request.operation = 0;
                InvokeTaskCallback(gUnitTaskContext->secondary, &request);
                WriteTaskState(gUnitTaskContext->secondary, 0x10d);
            }
        } else {
            created = CreateTaskNode(gUnitTaskContext->group, SecondaryUnitTask,
                                  1576, (const u32 *)&request, task);
            __asm__("" : "+r"(created));
            gUnitTaskContext->secondary = created;
        }
        return gUnitTaskContext->secondary;
    } else {
        task = gUnitTaskContext->primary;
        if (task != 0) {
            task_state = ReadTaskState(task);
            if ((primary_flags & 32) &&
                (task_state == 0x102 || task_state == 0x10c)) {
                request.operation = 0x10a;
                InvokeTaskCallback(gUnitTaskContext->primary, &request);
                WriteTaskState(gUnitTaskContext->primary, 0x10b);
            } else {
                request.operation = 0x104;
                InvokeTaskCallback(gUnitTaskContext->primary, &request);
                WriteTaskState(gUnitTaskContext->primary, 0x10d);
            }
        } else {
            created = CreateTaskNode(gUnitTaskContext->group, PrimaryUnitTask,
                                  1576, (const u32 *)&request, task);
            __asm__("" : "+r"(created));
            gUnitTaskContext->primary = created;
        }
        return gUnitTaskContext->primary;
    }
}
