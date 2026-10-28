typedef unsigned short u16;
struct Actor;
struct Request {struct Actor *actor;void *task;u16 state,depth;u16 continuations[34];};
typedef void (*ClearFunction)(void *,unsigned int);
void InvokeCallback(void *,unsigned int,ClearFunction) __asm__("RetailCall_0814224c");
void CoreFrontier_000BC3B0(struct Request *request,struct Actor *actor)
{
    InvokeCallback(request,80,*(ClearFunction *)0x0836d4b8);
    request->actor=actor;
    request->state=6;
    request->continuations[request->depth++]=6;
    request->state=4;
    request->continuations[request->depth++]=4;
    request->state=2;
    request->continuations[request->depth++]=2;
    request->state=0;
}
asm(".global RetailCall_0814224c\n.thumb_set RetailCall_0814224c,0x0814224d\n");
