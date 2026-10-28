#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

struct PositionedDefinitionStartup {
    u16 x;
    u16 y;
    u16 parameter;
    u16 definition_id;
    u8 mode;
    u8 reserved[3];
    void *output;
    const void *sequence;
};
typedef char PositionedDefinitionStartupMustBe20Bytes[
    sizeof(struct PositionedDefinitionStartup) == 20 ? 1 : -1];
extern void ReadCurrentDefinitionCoordinates(u16 *,u16 *);
extern TaskNode *CreateTaskInCurrentGroup(TaskCallback,u16,const u32 *,TaskNode *);
extern void PositionedDefinitionCallback(TaskNode *,u16 *,void *);
TaskNode *CreatePositionedDefinitionTask(int x, u16 y, int parameter, u8 flags,
                                        u32 definition_id, void *output,
                                        const void *sequence, TaskNode *parent)
{
    struct PositionedDefinitionStartup startup;
    u32 event[7];
    u16 offset_x, offset_y;
    startup.x = x;
    startup.y = y;
    startup.parameter = parameter;
    startup.mode = flags & 127;
    startup.definition_id = definition_id;
    startup.output = output;
    startup.sequence = sequence;
    if (startup.mode == 1 && (flags & 128) == 0) {
        u32 adjusted_x;
        struct PositionedDefinitionStartup *destination;
        register const struct PositionedDefinitionStartup *before asm("r1");
        ReadCurrentDefinitionCoordinates(&offset_x,&offset_y);
        destination = &startup;
        before = &startup;
        /* Retain the actual source address before loading the OUT value. */
        asm("" : : "r" (before));
        adjusted_x = offset_x + before->x;
        destination->x = adjusted_x;
        destination->y = startup.y + offset_y;
    }
    event[1] = (u32)&startup;
    return CreateTaskInCurrentGroup(PositionedDefinitionCallback,28,event,parent);
}

asm(".global ReadCurrentDefinitionCoordinates\n.thumb_set ReadCurrentDefinitionCoordinates,0x801e6f1\n"
    ".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x8005b6d\n"
    ".global PositionedDefinitionCallback\n.thumb_set PositionedDefinitionCallback,0x80d4ded\n");
