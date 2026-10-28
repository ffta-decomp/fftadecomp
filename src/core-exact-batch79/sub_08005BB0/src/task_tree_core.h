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
