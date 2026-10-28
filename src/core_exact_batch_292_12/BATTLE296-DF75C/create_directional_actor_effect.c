typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Task;
struct Actor;
struct Parameters {struct Actor *source;struct Actor *target;u16 selector;u16 descriptor_value;u8 descriptor_mode;};
struct Event {u16 state;u8 unused2[2];struct Parameters *parameters;u8 unused8[12];u16 delay;u8 unused22[6];};
extern struct Task *CreateTask(const void *,u32,struct Event *,struct Task *);
extern const u8 gDirectionalActorEffectEntry[];
struct Task *CreateDirectionalActorEffect(struct Actor *source,struct Actor *target,u16 selector,u16 descriptor_value,u8 descriptor_mode,u16 delay,struct Task *parent)
{
    struct Event event;
    struct Parameters parameters;
    parameters.source=source;
    parameters.target=target;
    parameters.selector=selector;
    parameters.descriptor_value=descriptor_value;
    parameters.descriptor_mode=descriptor_mode;
    event.parameters=&parameters;
    event.delay=delay;
    return CreateTask(gDirectionalActorEffectEntry,108,&event,parent);
}
__asm__(".global RemainingBand43_000DF75C\n.thumb_set RemainingBand43_000DF75C, CreateDirectionalActorEffect\n.global CreateTask\n.thumb_set CreateTask, 0x08005b6d\n.global gDirectionalActorEffectEntry\n.set gDirectionalActorEffectEntry, 0x080de9e1");
