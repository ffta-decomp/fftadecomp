typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Task;
struct Actor {u8 unknown0[31];u8 default_selector;};
struct Parameters {struct Actor *actor;u8 mode,selector;u16 value,extra,delay;};
struct Event {u16 state;u8 unknown2[2];struct Parameters *parameters;};
struct Work {struct Actor *actor;u8 mode,selector;u16 value,extra,delay;};
typedef char WorkSize[sizeof(struct Work)==12?1:-1];
extern void RequestActorValue(struct Actor*,u16,int);
extern void RequestActorValueWithExtra(struct Actor*,u16,u16,int);
extern u32 PollActorHandles(struct Actor*);
u32 AdvanceActorRequestTask(struct Task*,struct Event*,struct Work*) __asm__("RemainingBand43_000DD900");
u32 AdvanceActorRequestTask(struct Task *task,struct Event *event,struct Work *work)
{
    switch(event->state) {
    case 0: {
        struct Parameters *parameters=event->parameters;
        struct Actor *actor=parameters->actor;
        work->actor=actor;
        work->mode=parameters->mode;
        work->selector=parameters->selector;
        if((s8)work->selector==-1)
            work->selector=actor->default_selector;
        work->value=parameters->value;
        work->extra=parameters->extra;
        if((s16)work->extra==-1)
            work->extra=0;
        work->delay=parameters->delay;
        break;
    }
    case 1:break;
    case 256:
        if(work->delay!=0) {
            work->delay--;
            break;
        }
        if(work->mode==0)
            RequestActorValue(work->actor,work->value,(s8)work->selector);
        else
            RequestActorValueWithExtra(work->actor,work->value,work->extra,(s8)work->selector);
        event->state++;
        break;
    case 257:
        if((u8)PollActorHandles(work->actor)!=0)
            event->state=2;
        break;
    }
    return 0;
}
__asm__(".global RequestActorValue\n.thumb_set RequestActorValue,0x080de12d\n.global RequestActorValueWithExtra\n.thumb_set RequestActorValueWithExtra,0x080de169\n.global PollActorHandles\n.thumb_set PollActorHandles,0x080de1f1");
