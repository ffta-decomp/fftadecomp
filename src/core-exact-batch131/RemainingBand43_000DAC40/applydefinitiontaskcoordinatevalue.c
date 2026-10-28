#include "../../../src/task_tree_core.h"

typedef signed short s16;

extern void *GetTaskPayload(TaskNode *);
extern u32 ReadDefinitionObjectDataWord(const void *);
extern void ApplyDefinitionCoordinates(s16,s16,u16,u32,u32);
void ApplyDefinitionTaskCoordinateValue(TaskNode *task,u16 x,u16 y,u16 value)
{
    void *payload = GetTaskPayload(task);
    u32 data = ReadDefinitionObjectDataWord(((const void *const *)payload)[1]);
    ApplyDefinitionCoordinates((s16)x,(s16)y,value,data,0);
}

asm(".global GetTaskPayload\n.thumb_set GetTaskPayload,0x8005bfd\n"
    ".global ReadDefinitionObjectDataWord\n.thumb_set ReadDefinitionObjectDataWord,0x800c615\n"
    ".global ApplyDefinitionCoordinates\n.thumb_set ApplyDefinitionCoordinates,0x80d9f61\n");
