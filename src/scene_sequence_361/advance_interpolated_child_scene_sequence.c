typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;};
struct SceneInterpolation {u16 value; u8 unknown02[10];};
struct InterpolatedSceneEffect {
    u8 unknown00[8]; void *child,*object;
    struct SceneInterpolation interpolation;
    void *overlay;
};
struct SceneDisplay {u16 control;};
extern struct SceneDisplay gSceneDisplay;
__asm__(".global gSceneDisplay\n.set gSceneDisplay,0x03000940");
extern u32 SetSceneResource(const void*,u32,u32,u32,u32) asm("RetailCall_080D45D0");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *StartSceneChild(u32,void*) asm("RetailCall_0811ECD0");
extern void *PollSceneChild(void*) asm("RetailCall_0811ED14");
extern void *CreateSceneEffectObject(void*) asm("RetailCall_0811EC30");
extern u32 InitializeSceneInterpolation(struct SceneInterpolation*,s32,s32,s32) asm("RetailCall_080E0608");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern u32 AdvanceSceneInterpolation(struct SceneInterpolation*) asm("RetailCall_080E064C");
extern u32 SetSceneEffectPosition(void*,s32,s32,u32) asm("RetailCall_080DAC40");
extern u32 SceneInterpolationDone(struct SceneInterpolation*) asm("RetailCall_080E0690");
extern u32 FinishSceneStage(void) asm("RetailCall_080D8D78");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern void *DeleteSceneEffectObject(void*) asm("RetailCall_080D9B64");
typedef char WorkSize[(sizeof(struct InterpolatedSceneEffect)==32)?1:-1];
typedef char InterpolationSize[(sizeof(struct SceneInterpolation)==12)?1:-1];
u32 AdvanceInterpolatedSceneEffect(void*,struct SceneContext*,struct InterpolatedSceneEffect*) asm("OriginalCallbackQuestion_0011B2A0");
u32 AdvanceInterpolatedSceneEffect(void *owner,struct SceneContext *context,struct InterpolatedSceneEffect *work)
{
    switch(context->state) {
    case 0:
        SetSceneResource((void*)0x088EB4A4,6,0,0,1);
        break;
    case 1:
        ResumeScene();
        break;
    case 256:
        work->child=StartSceneChild(1,owner);
        context->state++;
        break;
    case 257:
        work->child=PollSceneChild(work->child);
        if(work->child) break;
        work->object=CreateSceneEffectObject(owner);
        InitializeSceneInterpolation(&work->interpolation,0,145,60);
        work->overlay=StartSceneOverlay((void*)0x083A6A08,1,4,0,owner);
        context->state++;
        break;
    case 258:
        AdvanceSceneInterpolation(&work->interpolation);
        SetSceneEffectPosition(work->object,120,80,work->interpolation.value);
        if(!(u8)SceneInterpolationDone(&work->interpolation)) break;
        FinishSceneStage();
        {
            u32 mask=SceneLayerMask(2);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            gSceneDisplay.control=control;
        }
        {
            u32 mask=SceneLayerMask(3);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            control&=0xDFFF;
            gSceneDisplay.control=control;
        }
        context->state++;
        break;
    case 259:
        work->object=DeleteSceneEffectObject(work->object);
        if(!work->object) context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x080035a9");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x080d35d9");

__asm__(".global RetailCall_080D45D0\n.thumb_set RetailCall_080D45D0, 0x080d45d1");

__asm__(".global RetailCall_080D8D78\n.thumb_set RetailCall_080D8D78, 0x080d8d79");

__asm__(".global RetailCall_080D9B64\n.thumb_set RetailCall_080D9B64, 0x080d9b65");

__asm__(".global RetailCall_080DAC40\n.thumb_set RetailCall_080DAC40, 0x080dac41");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x080dfd8d");

__asm__(".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608, 0x080e0609");

__asm__(".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C, 0x080e064d");

__asm__(".global RetailCall_080E0690\n.thumb_set RetailCall_080E0690, 0x080e0691");

__asm__(".global RetailCall_0811EC30\n.thumb_set RetailCall_0811EC30, 0x0811ec31");

__asm__(".global RetailCall_0811ECD0\n.thumb_set RetailCall_0811ECD0, 0x0811ecd1");

__asm__(".global RetailCall_0811ED14\n.thumb_set RetailCall_0811ED14, 0x0811ed15");
