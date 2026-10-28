typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *actor_a,*actor_b;};
struct EffectChannel {s16 value;u8 unknown02[10];};
struct CoordinatePhaseWork {
    u16 timer;s16 x,y;u8 unknown06[2];
    void *actor_a,*actor_b,*positioned,*positioned_output;
    u8 unknown24[20];
    void *resource_a,*resource_b,*prelude,*overlay;
    struct EffectChannel channel;
};
extern u16 gDisplayFlags;
extern const u8 gActorPrelude[],gFirstProgram[],gFirstResource[],gFirstPositioned[],gSceneOverlay[],gSecondProgram[],gSecondResourceA[],gSecondResourceB[],gSecondPositioned[];
extern void ReadActorCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern void *StartScenePrelude(const void*,u32,void*) asm("RetailCall_080D7A70");
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
extern void *PollScenePrelude(void*) asm("RetailCall_080D7ABC");
extern void StartEffectProgram(const void*,u32,u32,s32,s32,u32) asm("RetailCall_080D7220");
extern void *StartEffectResource(const void*,void*) asm("RetailCall_080D3E9C");
extern void *StartPositionedSequence(s32,s32,s32,u8,u32,void*,const void*,void*) asm("RetailCall_080D6098");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void InitEffectChannel(struct EffectChannel*,s32,s32,u32) asm("RetailCall_080E0608");
extern void AdvanceEffectChannel(struct EffectChannel*) asm("RetailCall_080E064C");
extern void MoveEffectProgram(const void*,u32,s32,s32) asm("RetailCall_080D7468");
extern void *PollEffectResource(void*) asm("RetailCall_080D3F08");
extern void *PollPositionedSequence(void*) asm("RetailCall_080D6134");
extern u8 IsEffectChannelFinished(struct EffectChannel*) asm("RetailCall_080E0690");
extern void *StartSecondaryResource(const void*,void*) asm("RetailCall_080D4704");
extern u32 ReadLayerDisableMask(u32) asm("RetailCall_080035A8");
extern void SetActorPhaseFlag(void*,u32) asm("RetailCall_080DBEB4");
extern void *PollSecondaryResource(void*) asm("RetailCall_080D4774");
typedef char WorkSize[(sizeof(struct CoordinatePhaseWork)==72)?1:-1];
typedef char ChannelSize[(sizeof(struct EffectChannel)==12)?1:-1];
u32 AdvanceTwoCoordinatePhases(void*,struct SceneContext*,struct CoordinatePhaseWork*) asm("OriginalSceneDefinitionQuestion_0011DBCC");
u32 AdvanceTwoCoordinatePhases(void *owner,struct SceneContext *context,struct CoordinatePhaseWork *work)
{
    s32 state=context->state;
    switch(state) {
    case 0:
        work->actor_a=context->actor_a;
        work->actor_b=context->actor_b;
        ReadActorCoordinates(work->actor_a,&work->x,&work->y);
        work->prelude=StartScenePrelude(gActorPrelude,7,owner);
        break;
    case 1:
        RestoreSceneStage();
        break;
    case 256: {
        void *completed=PollScenePrelude(work->prelude);
        work->prelude=completed;
        if(completed) break;
        StartEffectProgram(gFirstProgram,1,3,work->x,(s16)((u16)work->y-16),(u32)completed);
        work->resource_a=StartEffectResource(gFirstResource,owner);
        work->positioned=StartPositionedSequence(work->x,work->y,0,1,6,&work->positioned_output,gFirstPositioned,owner);
        work->overlay=StartSceneOverlay(gSceneOverlay,1,4,0,owner);
        InitEffectChannel(&work->channel,(s16)((u16)work->y-16),work->y,60);
        context->state++;
        break;
    }
    case 257: {
        struct EffectChannel *channel=&work->channel;
        void *completed;
        AdvanceEffectChannel(channel);
        MoveEffectProgram(gFirstProgram,3,work->x,work->channel.value);
        work->resource_a=PollEffectResource(work->resource_a);
        if(work->resource_a) break;
        completed=PollPositionedSequence(work->positioned);
        work->positioned=completed;
        if(completed) break;
        if(!IsEffectChannelFinished(channel)) break;
        StartEffectProgram(gSecondProgram,0,2,work->x,(s16)((u16)work->y-10),(u32)completed);
        work->resource_a=StartEffectResource(gSecondResourceA,owner);
        work->resource_b=StartSecondaryResource(gSecondResourceB,owner);
        work->positioned=StartPositionedSequence(work->x,work->y,0,1,1,&work->positioned_output,gSecondPositioned,owner);
        work->timer=60;
        context->state++;
        break;
    }
    case 258:
        if(work->timer==60) {
            u32 mask=ReadLayerDisableMask(3);
            gDisplayFlags&=~mask;
        }
        if(work->timer && !--work->timer) {
            SetActorPhaseFlag(work->actor_a,1);
            SetActorPhaseFlag(work->actor_b,1);
        }
        work->resource_a=PollEffectResource(work->resource_a);
        if(work->resource_a) break;
        work->resource_b=PollSecondaryResource(work->resource_b);
        if(work->resource_b) break;
        work->positioned=PollPositionedSequence(work->positioned);
        if(work->positioned) break;
        {
            u32 mask=ReadLayerDisableMask(2);
            gDisplayFlags&=~mask;
        }
        context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8,0x080dbdc9");
__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70,0x080d7a71");
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC,0x080d7abd");
__asm__(".global RetailCall_080D7220\n.thumb_set RetailCall_080D7220,0x080d7221");
__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C,0x080d3e9d");
__asm__(".global RetailCall_080D6098\n.thumb_set RetailCall_080D6098,0x080d6099");
__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C,0x080dfd8d");
__asm__(".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608,0x080e0609");
__asm__(".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C,0x080e064d");
__asm__(".global RetailCall_080D7468\n.thumb_set RetailCall_080D7468,0x080d7469");
__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08,0x080d3f09");
__asm__(".global RetailCall_080D6134\n.thumb_set RetailCall_080D6134,0x080d6135");
__asm__(".global RetailCall_080E0690\n.thumb_set RetailCall_080E0690,0x080e0691");
__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704,0x080d4705");
__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8,0x080035a9");
__asm__(".global RetailCall_080DBEB4\n.thumb_set RetailCall_080DBEB4,0x080dbeb5");
__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774,0x080d4775");
__asm__(".global gDisplayFlags\n.set gDisplayFlags,0x03000940");
__asm__(".global gActorPrelude\n.set gActorPrelude,0x083a711c");
__asm__(".global gFirstProgram\n.set gFirstProgram,0x088f668c");
__asm__(".global gFirstResource\n.set gFirstResource,0x0894ddd0");
__asm__(".global gFirstPositioned\n.set gFirstPositioned,0x083a7170");
__asm__(".global gSceneOverlay\n.set gSceneOverlay,0x083a7218");
__asm__(".global gSecondProgram\n.set gSecondProgram,0x088f46f0");
__asm__(".global gSecondResourceA\n.set gSecondResourceA,0x0894d690");
__asm__(".global gSecondResourceB\n.set gSecondResourceB,0x0894cb14");
__asm__(".global gSecondPositioned\n.set gSecondPositioned,0x083a7200");
