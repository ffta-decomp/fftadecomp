typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Task;
struct Request {void *actor;u8 mode,selector;u16 value,extra,delay;};
struct Event {u16 state;u8 unused2[2];struct Request *request;u8 unused8[20];};
extern struct Task *CreateTask(const void*,u32,struct Event*,struct Task*);
extern const u8 gActorRequestEntry[];
struct Task *CreateActorRequest(void*,u8,u16,u16,struct Task*) __asm__("RemainingBand43_000DE074");
struct Task *CreateActorRequest(void *actor,u8 mode,u16 value,u16 delay,struct Task *parent)
{
    struct Startup {struct Request request;struct Event event;} startup;
    startup.request.actor=actor;
    startup.request.mode=mode;
    startup.request.selector=255;
    startup.request.value=value;
    startup.request.extra=0;
    startup.request.delay=delay;
    startup.event.request=&startup.request;
    {
        register const void *callback __asm__("r0")=gActorRequestEntry;
        register u32 payload_size __asm__("r1")=12;
        register struct Event *event __asm__("r2")=&startup.event;
        /* Preserve the observed ordering of these three real call inputs. */
        __asm__("" : "+r"(callback),"+r"(payload_size),"+r"(event));
        return CreateTask(callback,payload_size,event,parent);
    }
}
__asm__(".global CreateTask\n.thumb_set CreateTask,0x08005b6d\n.global gActorRequestEntry\n.set gActorRequestEntry,0x080dd901");
