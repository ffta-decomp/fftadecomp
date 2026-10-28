#include "../../../../src/task_tree_core.h"

struct DefinitionTransitionParameters {
    void *object;
    const u16 *first_point;
    const u16 *second_point;
    void *first_values;
    void *second_values;
    void *third_values;
    u16 mode;
    u16 count;
};

struct DefinitionTransitionEvent {
    u16 state;
    u8 unused_02[2];
    struct DefinitionTransitionParameters *parameters;
    u8 unused_08[12];
    u16 flags;
    u8 unused_16[6];
};
typedef char ParametersSize[sizeof(struct DefinitionTransitionParameters) == 28 ? 1 : -1];
typedef char EventSize[sizeof(struct DefinitionTransitionEvent) == 28 ? 1 : -1];

extern u32 AdvanceDefinitionTransition(TaskNode *, u16 *, void *);
extern TaskNode *CreateDefinitionTask(TaskCallback, u16, const void *, TaskNode *);

TaskNode *CreateDefinitionTransition(void *object, const u16 *first_point,
    const u16 *second_point, u32 mode, u32 count, void *first_values,
    void *second_values, void *third_values, u16 flags, TaskNode *parent)
{
    struct DefinitionTransitionParameters parameters;
    struct DefinitionTransitionEvent event;

    parameters.object = object;
    parameters.first_point = first_point;
    parameters.second_point = second_point;
    parameters.mode = mode;
    parameters.count = count;
    parameters.first_values = first_values;
    parameters.second_values = second_values;
    parameters.third_values = third_values;
    event.flags = flags;
    event.parameters = &parameters;
    return CreateDefinitionTask((TaskCallback)AdvanceDefinitionTransition,
                                84, &event, parent);
}

asm(".global AdvanceDefinitionTransition\n.thumb_set AdvanceDefinitionTransition,0x080d5129\n"
    ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x08005b6d\n");
