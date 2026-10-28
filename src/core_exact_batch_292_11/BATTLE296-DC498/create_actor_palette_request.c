typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Task;
struct Parameters {void *actor;u32 duration:16;u32 palette:8;u32 preserved:8;};
struct Event {u16 state;u8 unused2[2];struct Parameters *parameters;u8 unused8[12];u16 delay;u8 unused22[6];};
extern struct Task *CreateTask(const void*,u32,struct Event*,struct Task*);
extern const u8 gActorPaletteEntry[];
struct Task *CreateActorPaletteRequest(void*,u16,u8,u16,struct Task*) __asm__("RemainingBand43_000DC498");
struct Task *CreateActorPaletteRequest(void *actor,u16 duration,u8 palette,u16 delay,struct Task *parent)
{
    struct Event event;
    struct Parameters parameters;
    parameters.actor=actor;
    parameters.duration=duration;
    parameters.palette=palette;
    event.delay=delay;
    event.parameters=&parameters;
    return CreateTask(gActorPaletteEntry,16,&event,parent);
}
__asm__(".global CreateTask\n.thumb_set CreateTask,0x08005b6d\n.global gActorPaletteEntry\n.set gActorPaletteEntry,0x080db775");
