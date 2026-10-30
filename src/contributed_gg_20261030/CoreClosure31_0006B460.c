/* Contributed by gg; original source and attribution follow. */
/* CoreClosure31_0006B460
   entry 0x0806B460, 100 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
/* ---- inlined task_tree_core.h ---- */
#ifndef TASK_TREE_CORE_H
#define TASK_TREE_CORE_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TaskNode TaskNode;
typedef struct TaskGroup TaskGroup;
typedef void (*TaskCallback)(TaskNode *, u16 *event, void *payload);

struct TaskNode {
    TaskCallback callback;
    TaskNode *previous;
    TaskNode *next;
    TaskNode *parent;
    TaskNode *first_child;
    u16 state;
    u16 phase;
};

struct TaskGroup {
    void *allocator;
    TaskNode *first_root;
    TaskNode *current;
    u16 phase;
};

extern void *Allocate_08007138(void *allocator, u32 bytes);
extern void Free_08007170(void *allocator, void *allocation);
extern void (*const gClearMemory)(void *, u32);

#define CURRENT_GROUP (*(TaskGroup * volatile *)0x02008ff0U)

void RemoveTaskSubtree_080058A4(TaskGroup *group, TaskNode *root);
TaskNode *CreateTaskNode_08005954(TaskGroup *group, TaskCallback callback,
                                  u32 payload_size_argument,
                                  const u32 *event_template, TaskNode *parent);
void RunTaskTree_08005A24(TaskGroup *group);

#endif

extern u8 *MenuResponseWorkspace;
extern u32 ReadMenuResponseState(const void *state);
extern void RequestMenuResponseDefinition(u32 index);

void f_target(u8 *controller_state)
{
    register u8 *first_destination asm("r4") = controller_state;
    register u8 *second_destination asm("r6") = first_destination;
    register u8 **workspace_cell asm("r5") = &MenuResponseWorkspace;
    /* Keep the original cell address, not a snapshot of its loaded workspace. */
    asm("" : "+r"(workspace_cell));
    /* Original entry retains both initialized destination aliases across calls. */
    asm("" : "+r"(first_destination), "+r"(second_destination));
    if ((u8)ReadMenuResponseState(*workspace_cell + 0x1a88) == 4) {
        RequestMenuResponseDefinition(100);
        *first_destination = 60;
    } else {
        /* The original queries again through a freshly loaded workspace. */
        if ((u8)ReadMenuResponseState(*workspace_cell + 0x1a88) != 1)
            return;
        RequestMenuResponseDefinition(104);
        *second_destination = 62;
    }
    (*workspace_cell)[0x446c] = 23;
}

asm(".global MenuResponseWorkspace\n.set MenuResponseWorkspace,0x0200f428\n"
    ".global ReadMenuResponseState\n.thumb_set ReadMenuResponseState,0x0806fe15\n"
    ".global RequestMenuResponseDefinition\n.thumb_set RequestMenuResponseDefinition,0x08141541\n");
