typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct SceneOwner {u8 unknown0[6];u8 complete;};
struct SceneEvent {u16 phase;u16 unknown2;struct SceneOwner *scene;u8 unknown8[12];u16 actor;};
struct Actor {u8 unknown0[8];s16 x,height,y;u8 unknown14[34];u32 flags;};
struct Work {struct SceneOwner *scene;struct Actor *slots[13];struct Actor *actor;void *effect;u8 timer,count,cursor,padding;};
typedef char WorkSize[(sizeof(struct Work)==68)?1:-1];
extern struct Actor *ResolveSceneActor(u32);
extern void *CreateDefinition(u32,u32,u32);
extern u32 IsContinuationReady(void *);
extern void DispatchEnabled(u16);
extern void EmitProjected(void *,s16,s16,s16,u8,u8);
extern u32 PollEffect(void *);
extern void RemoveEffect(void *);
u32 AdvanceSceneActorEffect(void *unused,struct SceneEvent *event,struct Work *work) asm("CoreRegion_0012B7F0");
u32 AdvanceSceneActorEffect(void *unused,struct SceneEvent *event,struct Work *work)
{
    u16 phase=event->phase;
    switch(phase) {
    case 0:
        work->scene=event->scene;
        work->actor=ResolveSceneActor((u8)event->actor);
        work->count=1;
        work->cursor=phase;
        work->effect=CreateDefinition(347,0,0);
        break;
    case 1:
        break;
    case 256:
        if((u8)IsContinuationReady(work->effect))event->phase=257;
        break;
    case 257:
        DispatchEnabled(221);
        work->timer=0;
        event->phase=258;
        break;
    case 258: {
        register u32 selector asm("r4")=255;
        register struct Actor *actor asm("r2")=work->actor;
        register struct Actor *projected_actor asm("r3");
        u8 timer;
        u8 *timer_saved;
        asm("" : "+r" (actor));
        actor->flags^=1;
        timer=work->timer;
        /* Two real ordered definitions, no memory operation in this island.
         * Keep the saved timer address an ordinary pseudo after the high-reg
         * output, so normal C owns its later byte update and reload lifetime. */
        asm volatile("mov %0, %2\n\tadd %1, %3, #0"
                     : "=h" (timer_saved), "=l" (projected_actor)
                     : "l" (&work->timer), "l" (actor) : "cc");
        switch(timer) {
        case 0:selector=6;break;
        case 10:selector=5;break;
        case 20:selector=4;break;
        }
        selector <<= 24;
        /* Actual destructive working phase, restored to LOW8 only at SP0. */
        asm("" : "+r"(selector));
        if((int)selector>=0)
            EmitProjected(work->effect,projected_actor->x,projected_actor->height,projected_actor->y,selector>>24,2);
        if(++*timer_saved>31) {
            work->actor->flags|=1;
            event->phase=259;
        }
        break;
    }
    case 259:
        if(work->count==1)event->phase=260;
        else if(++work->cursor==work->count)event->phase=260;
        else {
            work->actor=work->slots[work->cursor];
            event->phase=257;
        }
        break;
    case 260:
        if((u8)PollEffect(work->effect)) {
            RemoveEffect(work->effect);
            work->effect=0;
            event->phase=261;
        }
        break;
    case 261:
        work->scene->complete=1;
        event->phase=3;
        break;
    }
    return 0;
}
asm(".global ResolveSceneActor\n.thumb_set ResolveSceneActor,0x081255c9\n.global CreateDefinition\n.thumb_set CreateDefinition,0x080d3509\n.global IsContinuationReady\n.thumb_set IsContinuationReady,0x080e2bdd\n.global DispatchEnabled\n.thumb_set DispatchEnabled,0x08141521\n.global EmitProjected\n.thumb_set EmitProjected,0x080e2c01\n.global PollEffect\n.thumb_set PollEffect,0x080d3879\n.global RemoveEffect\n.thumb_set RemoveEffect,0x080d3865\n");
