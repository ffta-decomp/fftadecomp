#include "../../../src/task_tree_core.h"
typedef signed short s16;
struct CoordinateTransitionParameters {
    void **object_cell;
    u16 start_x;
    u16 start_y;
    u16 end_x;
    u16 end_y;
    u16 start_y_offset;
    u16 end_y_offset;
    u16 count;
    u16 reserved18;
    s16 *x_values;
    s16 *y_values;
};
struct CoordinateTransitionEvent {
    u16 state;
    u16 reserved2;
    struct CoordinateTransitionParameters *parameters;
    void *override;
    u8 reserved12[8];
    u16 flags;
    u8 reserved22[6];
};
typedef char ParametersSize[sizeof(struct CoordinateTransitionParameters)==28?1:-1];
typedef char EventSize[sizeof(struct CoordinateTransitionEvent)==28?1:-1];
extern u32 CoordinateTransitionCallback(TaskNode *,u16 *,void *);
extern TaskNode *CreateDefinitionTask(TaskCallback,u16,const void *,TaskNode *);
TaskNode *CreateCoordinateTransitionRequest(void **object_cell,
    const u16 *start_point,const u16 *end_point,u32 start_y_offset,
    u32 end_y_offset,u16 count,s16 *x_values,s16 *y_values,u16 flags,
    TaskNode *parent)
{
    struct CoordinateTransitionParameters parameters;
    struct CoordinateTransitionEvent event;
    parameters.object_cell = object_cell;
    parameters.start_x = start_point[0];
    parameters.start_y = start_point[1];
    parameters.end_x = end_point[0];
    parameters.end_y = end_point[1];
    parameters.start_y_offset = start_y_offset;
    parameters.end_y_offset = end_y_offset;
    parameters.count = count;
    parameters.x_values = x_values;
    parameters.y_values = y_values;
    event.flags = flags;
    event.parameters = &parameters;
    event.override = 0;
    return CreateDefinitionTask((TaskCallback)CoordinateTransitionCallback,40,&event,parent);
}
asm(".global CoordinateTransitionCallback\n.thumb_set CoordinateTransitionCallback,0x080d5a61\n"
    ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x08005b6d\n");
