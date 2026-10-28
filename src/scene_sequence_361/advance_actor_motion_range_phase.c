typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *actor;void **parent_resource;};
struct SceneInterpolation {s16 value;u8 unknown02[10];};
struct ActorMotionWork {
    u16 delay;s16 x,y;u8 unknown06[2];
    void *actor;void **parent_resource;void *child,*child_output;
    u8 unknown24[24];void *range;
    struct SceneInterpolation motion;void *overlay;
};
extern const u8 gActorMotionDefinition[],gSceneOverlay[];
extern void ReadActorCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern u8 IsParentResourceReady(void*) asm("RetailCall_080DFAD0");
extern u32 ConvertActorCoordinates(void*,s32,s32,s16*,s16*) asm("RetailCall_080DC224");
extern u32 SetLayerX(s32,u32) asm("RetailCall_08003508");
extern u32 SetLayerY(s32,u32) asm("RetailCall_08003558");
extern void SetActorPhaseFlag(void*,u32) asm("RetailCall_080DBEB4");
extern void *StartActorMotion(s32,s32,s32,u8,u32,void*,const void*,void*) asm("RetailCall_080D6098");
extern void *AllocateSceneRange(u32,u32,u32,u32) asm("RetailCall_08147EC8");
extern void InitSceneInterpolation(struct SceneInterpolation*,s32,s32,u32) asm("RetailCall_080E0608");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void AdvanceSceneInterpolation(struct SceneInterpolation*) asm("RetailCall_080E064C");
extern void *PollSceneRange(void*) asm("RetailCall_081484CC");
extern void *PollActorMotion(void*) asm("RetailCall_080D6134");
typedef char WorkSize[(sizeof(struct ActorMotionWork)==68)?1:-1];
typedef char ChannelSize[(sizeof(struct SceneInterpolation)==12)?1:-1];
u32 AdvanceActorMotionAndRange(void*,struct SceneContext*,struct ActorMotionWork*) asm("RemainingBand43_0011D73C");
u32 AdvanceActorMotionAndRange(void *owner,struct SceneContext *context,struct ActorMotionWork *work)
{
    s32 state=context->state;
    switch(state) {
    case 0:
        work->actor=context->actor;
        work->parent_resource=context->parent_resource;
        ReadActorCoordinates(work->actor,&work->x,&work->y);
        break;
    case 1:
        break;
    case 256:
        work->delay=25;
        context->state++;
        break;
    case 257: {
        s16 x,y;
        if(work->delay && --work->delay) break;
        if(!IsParentResourceReady(*work->parent_resource)) break;
        ConvertActorCoordinates(work->actor,work->x,work->y,&x,&y);
        SetLayerX(x,3);
        SetLayerY(y,3);
        SetActorPhaseFlag(work->actor,0);
        work->child=StartActorMotion(work->x,work->y,0,1,7,&work->child_output,gActorMotionDefinition,owner);
        work->range=AllocateSceneRange(112,16,150,8);
        InitSceneInterpolation(&work->motion,work->y,(s16)((u16)work->y-16),150);
        work->overlay=StartSceneOverlay(gSceneOverlay,1,4,0,owner);
        context->state++;
        break;
    }
    case 258: {
        s16 x,y;
        AdvanceSceneInterpolation(&work->motion);
        ConvertActorCoordinates(work->actor,work->x,work->motion.value,&x,&y);
        SetLayerX(x,3);
        SetLayerY(y,3);
        work->range=PollSceneRange(work->range);
        if(work->range) break;
        work->child=PollActorMotion(work->child);
        if(work->child) break;
        context->state++;
        break;
    }
    case 259:
        context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8,0x080dbdc9");
__asm__(".global RetailCall_080DFAD0\n.thumb_set RetailCall_080DFAD0,0x080dfad1");
__asm__(".global RetailCall_080DC224\n.thumb_set RetailCall_080DC224,0x080dc225");
__asm__(".global RetailCall_08003508\n.thumb_set RetailCall_08003508,0x08003509");
__asm__(".global RetailCall_08003558\n.thumb_set RetailCall_08003558,0x08003559");
__asm__(".global RetailCall_080DBEB4\n.thumb_set RetailCall_080DBEB4,0x080dbeb5");
__asm__(".global RetailCall_080D6098\n.thumb_set RetailCall_080D6098,0x080d6099");
__asm__(".global RetailCall_08147EC8\n.thumb_set RetailCall_08147EC8,0x08147ec9");
__asm__(".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608,0x080e0609");
__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C,0x080dfd8d");
__asm__(".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C,0x080e064d");
__asm__(".global RetailCall_081484CC\n.thumb_set RetailCall_081484CC,0x081484cd");
__asm__(".global RetailCall_080D6134\n.thumb_set RetailCall_080D6134,0x080d6135");
__asm__(".global gActorMotionDefinition\n.set gActorMotionDefinition,0x083a6f2c");
__asm__(".global gSceneOverlay\n.set gSceneOverlay,0x083a70b4");
