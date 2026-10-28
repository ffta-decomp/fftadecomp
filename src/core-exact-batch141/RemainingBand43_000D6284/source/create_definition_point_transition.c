typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
typedef u32 (*TaskCallback)(struct TaskNode *,u16 *,void *);
struct DefinitionTransitionParameters {
    void *object;
    const u16 *first_point,*second_point;
    void *first_values,*second_values,*third_values;
    u16 mode,count;
};
struct DefinitionTransitionEvent {
    u16 state;u8 unused_02[2];
    struct DefinitionTransitionParameters *parameters;
    u8 unused_08[12];u16 flags;u8 unused_16[6];
};
typedef char ParametersSize[sizeof(struct DefinitionTransitionParameters)==28?1:-1];
typedef char EventSize[sizeof(struct DefinitionTransitionEvent)==28?1:-1];
extern u32 AdvanceDefinitionPointTransition(struct TaskNode *,u16 *,void *);
extern struct TaskNode *CreateDefinitionTask(TaskCallback,u16,const void *,struct TaskNode *);
struct TaskNode *CreateDefinitionPointTransition(void *object,const u16 *first_point,const u16 *second_point,u32 mode,void *first_values,void *second_values,void *third_values,u16 flags,struct TaskNode *parent) __asm__("RemainingBand43_000D6284");
struct TaskNode *CreateDefinitionPointTransition(void *object,const u16 *first_point,const u16 *second_point,u32 mode,void *first_values,void *second_values,void *third_values,u16 flags,struct TaskNode *parent)
{
    struct DefinitionTransitionParameters parameters;
    struct DefinitionTransitionEvent event;
    parameters.object=object;
    parameters.first_point=first_point;
    parameters.second_point=second_point;
    parameters.mode=mode;
    parameters.first_values=first_values;
    parameters.second_values=second_values;
    parameters.third_values=third_values;
    event.flags=flags;
    event.parameters=&parameters;
    return CreateDefinitionTask(AdvanceDefinitionPointTransition,76,&event,parent);
}
__asm__(".global AdvanceDefinitionPointTransition\n.thumb_set AdvanceDefinitionPointTransition,0x080d5595\n.global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x08005b6d");
