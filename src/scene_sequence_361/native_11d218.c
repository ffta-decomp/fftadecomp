typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *actor;};
struct EffectChannel {u16 value;u8 unknown02[10];};
struct ActorEffectWork {
    u16 timer;s16 x,y;u8 ready,unknown07;
    void *actor,*resource,*positioned,*positioned_output;
    struct EffectChannel channel_a,channel_b;
    void *effect_a,*effect_b,*transition,*overlay;
};
struct DisplayShadow {
    u16 flags;u8 unknown02[56];
    volatile u8 boundary58,boundary59,boundary60,boundary61;
    u8 boundary62;
    volatile u8 boundary63;
    volatile s8 boundary64;
    volatile u8 boundary65,mask66,mask67,mask68;
};
extern struct DisplayShadow gDisplayShadow;
extern const u8 gEffectProgram[],gEffectResource[],gPositionedSequence[],gEffectOverlay[];
extern void ReadActorCoordinates(void*,s16*,s16*) asm("RetailCall_080dbdc8");
extern void SetActorPose(void*,u32) asm("RetailCall_080de10c");
extern void *StartDirectActorTransition(void*,u8*,u32,u32,u32,u32,u32,void*) asm("RetailCall_080de4b0");
extern void StartEffectProgram(const void*,u32,u32,u32,u32,u32) asm("RetailCall_080d7220");
extern void *StartEffectResource(const void*,void*) asm("RetailCall_080d3e9c");
extern void SetEffectResourceRange(void*,u32,u32) asm("RetailCall_080d3f84");
extern void *StartPositionedSequence(s32,s32,s32,u8,u32,void*,const void*,void*) asm("RetailCall_080d6098");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080dfd8c");
extern u32 ReadLayerMask(u32) asm("RetailCall_080035d0");
extern void InitEffectChannel(struct EffectChannel*,u32,u32,u32) asm("RetailCall_080e0608");
extern void *CreateActorEffect(u32,u32,u32,void*) asm("RetailCall_080dab84");
extern void SetActorEffectState(void*,u32) asm("RetailCall_080d9ba8");
extern void AdvanceEffectChannel(struct EffectChannel*) asm("RetailCall_080e064c");
extern void AdvanceActorEffect(void*) asm("RetailCall_080dadfc");
extern void PositionActorEffect(void*,s32,s32,u32) asm("RetailCall_080dac40");
extern u8 IsEffectChannelFinished(struct EffectChannel*) asm("RetailCall_080e0690");
extern u32 ReadLayerDisableMask(u32) asm("RetailCall_080035a8");
extern void *PollEffectResource(void*) asm("RetailCall_080d3f08");
extern void *PollPositionedSequence(void*) asm("RetailCall_080d6134");
extern void *PollActorEffect(void*) asm("RetailCall_080d9b64");
extern void CloseEffectResource(void) asm("RetailCall_080d4020");
typedef char WorkSize[(sizeof(struct ActorEffectWork)==64)?1:-1];
typedef char ChannelSize[(sizeof(struct EffectChannel)==12)?1:-1];
typedef char RawDisplayOffset[((u32)&((struct DisplayShadow*)0)->boundary63==63)?1:-1];
u32 AdvanceActorEffectDefinition392(void*,struct SceneContext*,struct ActorEffectWork*) asm("RemainingBand43_0011D218");
u32 AdvanceActorEffectDefinition392(void *owner,struct SceneContext *context,struct ActorEffectWork *work)
{
    s32 state=context->state;
    switch(state) {
    case 0:
        work->actor=context->actor;
        ReadActorCoordinates(work->actor,&work->x,&work->y);
        work->y-=32;
        SetActorPose(work->actor,60);
        work->transition=StartDirectActorTransition(work->actor,&work->ready,3,2,state,state,state,owner);
        work->timer=20;
        break;
    case 256: {
        u32 zero;
        void *resource;
        if(!work->ready) break;
        if(work->timer && --work->timer) break;
        {
            register const u8 *program asm("r0")=gEffectProgram;
            asm("" : "+r"(program));
            zero=0;
            StartEffectProgram(program,1,3,0,zero,zero);
        }
        resource=StartEffectResource(gEffectResource,owner);
        work->resource=resource;
        SetEffectResourceRange(resource,8,255);
        work->positioned=StartPositionedSequence(work->x,work->y,0,0,1,&work->positioned_output,gPositionedSequence,owner);
        work->overlay=StartSceneOverlay(gEffectOverlay,1,4,0,owner);
        gDisplayShadow.mask66=63 & ~ReadLayerMask(3);
        gDisplayShadow.mask67=63;
        gDisplayShadow.mask68=63 & ~ReadLayerMask(3);
        gDisplayShadow.boundary59=zero;
        gDisplayShadow.boundary58=zero;
        gDisplayShadow.boundary63=zero;
        gDisplayShadow.boundary62=255;
        gDisplayShadow.boundary61=zero;
        gDisplayShadow.boundary60=zero;
        gDisplayShadow.boundary65=zero;
        gDisplayShadow.boundary64=-1;
        gDisplayShadow.flags|=0x6000;
        InitEffectChannel(&work->channel_a,24,0,28);
        InitEffectChannel(&work->channel_b,16,0,28);
        work->effect_a=CreateActorEffect(1,0,0,owner);
        work->effect_b=CreateActorEffect(0,0,0,owner);
        SetActorEffectState(work->effect_a,1);
        SetActorEffectState(work->effect_b,1);
        context->state++;
        break;
    }
    case 257: {
        u32 mask;
        AdvanceEffectChannel(&work->channel_a);
        AdvanceEffectChannel(&work->channel_b);
        AdvanceActorEffect(work->effect_a);
        AdvanceActorEffect(work->effect_b);
        PositionActorEffect(work->effect_a,work->x,work->y,work->channel_a.value);
        PositionActorEffect(work->effect_b,work->x,work->y,work->channel_b.value);
        if(!IsEffectChannelFinished(&work->channel_a)) break;
        if(!IsEffectChannelFinished(&work->channel_b)) break;
        mask=ReadLayerDisableMask(3);
        {
            register u32 control asm("r1")=gDisplayShadow.flags & ~mask;
            asm("" : "+r"(control));
            control &=0x9fff;
            gDisplayShadow.flags=control;
        }
        context->state++;
        break;
    }
    case 258:
        work->resource=PollEffectResource(work->resource);
        if(work->resource) break;
        work->positioned=PollPositionedSequence(work->positioned);
        if(work->positioned) break;
        work->effect_a=PollActorEffect(work->effect_a);
        if(work->effect_a) break;
        work->effect_b=PollActorEffect(work->effect_b);
        if(work->effect_b) break;
        CloseEffectResource();
        context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080dbdc8\n.thumb_set RetailCall_080dbdc8,0x080dbdc9");
__asm__(".global RetailCall_080de10c\n.thumb_set RetailCall_080de10c,0x080de10d");
__asm__(".global RetailCall_080de4b0\n.thumb_set RetailCall_080de4b0,0x080de4b1");
__asm__(".global RetailCall_080d7220\n.thumb_set RetailCall_080d7220,0x080d7221");
__asm__(".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d");
__asm__(".global RetailCall_080d3f84\n.thumb_set RetailCall_080d3f84,0x080d3f85");
__asm__(".global RetailCall_080d6098\n.thumb_set RetailCall_080d6098,0x080d6099");
__asm__(".global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d");
__asm__(".global RetailCall_080035d0\n.thumb_set RetailCall_080035d0,0x080035d1");
__asm__(".global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609");
__asm__(".global RetailCall_080dab84\n.thumb_set RetailCall_080dab84,0x080dab85");
__asm__(".global RetailCall_080d9ba8\n.thumb_set RetailCall_080d9ba8,0x080d9ba9");
__asm__(".global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d");
__asm__(".global RetailCall_080dadfc\n.thumb_set RetailCall_080dadfc,0x080dadfd");
__asm__(".global RetailCall_080dac40\n.thumb_set RetailCall_080dac40,0x080dac41");
__asm__(".global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691");
__asm__(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8,0x080035a9");
__asm__(".global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08,0x080d3f09");
__asm__(".global RetailCall_080d6134\n.thumb_set RetailCall_080d6134,0x080d6135");
__asm__(".global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64,0x080d9b65");
__asm__(".global RetailCall_080d4020\n.thumb_set RetailCall_080d4020,0x080d4021");
__asm__(".global gDisplayShadow\n.set gDisplayShadow,0x03000940");
__asm__(".global gEffectProgram\n.set gEffectProgram,0x088f46cc");
__asm__(".global gEffectResource\n.set gEffectResource,0x0894d690");
__asm__(".global gPositionedSequence\n.set gPositionedSequence,0x083a6e24");
__asm__(".global gEffectOverlay\n.set gEffectOverlay,0x083a6e3c");
