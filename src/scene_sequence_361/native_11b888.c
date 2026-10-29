typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;};
struct SceneInterpolation {u16 value;u8 unknown02[10];};
struct PairedSceneSequence {
    u16 delay;s16 x,y;u16 unknown06;
    void *script,*effects[2],*transition;
    struct SceneInterpolation vertical,first_radius,second_radius;
    void *overlay;
};
struct ScenePalette {u8 unknown00[194];u16 sequence_color;};
struct SceneDisplayShadow {
    u16 control;u8 unknown02[56];
    volatile u8 byte58,byte59,byte60,byte61,byte62,byte63,byte64,byte65;
    volatile u8 byte66,byte67,byte68;u8 unknown69[5];volatile u8 byte74;
};
extern struct ScenePalette gScenePalette;
extern struct SceneDisplayShadow gSceneDisplay;
__asm__(".global gScenePalette\n.set gScenePalette,0x03003860\n.global gSceneDisplay\n.set gSceneDisplay,0x03000940");
extern void *StartTransition(const void*,u32,void*) asm("RetailCall_080D7A70");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *PollTransition(void*) asm("RetailCall_080D7ABC");
extern u32 LoadSceneContent(const void*,u32,u32,u32,u32,u32) asm("RetailCall_080D7220");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern void *CreateSceneEffect(u32,u32,u32,void*) asm("RetailCall_080DAB84");
extern u32 SceneWindowMask(u32) asm("RetailCall_080035D0");
extern u32 SetSceneEffectMode(void*,u32) asm("RetailCall_080D9BA8");
extern u32 InitializeSceneInterpolation(struct SceneInterpolation*,s32,s32,s32) asm("RetailCall_080E0608");
extern u32 ConvertSceneCoordinates(s16,s16,s16*,s16*) asm("RetailCall_0801C960");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern u32 AdvanceSceneInterpolation(struct SceneInterpolation*) asm("RetailCall_080E064C");
extern u32 SetSceneEffectDimensions(void*,s16,s16,u32,u32) asm("RetailCall_080DAC80");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern u32 RestoreSceneStage(u32,u32,u32,u32) asm("RetailCall_080DBED4");
extern void *DeleteSceneEffect(void*) asm("RetailCall_080D9B64");
typedef char WorkSize[(sizeof(struct PairedSceneSequence)==64)?1:-1];
typedef char InterpolationSize[(sizeof(struct SceneInterpolation)==12)?1:-1];
u32 AdvanceStaggeredPairedSceneSequence(void*,struct SceneContext*,struct PairedSceneSequence*) asm("OriginalSceneDefinitionQuestion_0011B888");
u32 AdvanceStaggeredPairedSceneSequence(void *owner,struct SceneContext *context,struct PairedSceneSequence *incoming_work)
{
    /* Native copies the initialized incoming R2 work pointer into R6 here. */
    register struct PairedSceneSequence *work asm("r6")=incoming_work;
    asm("" : "+r"(work));
    switch(context->state) {
    case 0:
        work->transition=StartTransition((void*)0x083A6B04,2,owner);
        gScenePalette.sequence_color=0x396D;
        break;
    case 1:
        ResumeScene();
        break;
    case 256: {
        void *pending;
        void **effects;
        pending=PollTransition(work->transition);
        work->transition=pending;
        if(pending) break;
        LoadSceneContent((void*)0x088F46CC,0,2,0,(u32)pending,(u32)pending);
        work->script=StartSceneScript((void*)0x0894DDAC,owner);
        effects=work->effects;
        work->effects[0]=CreateSceneEffect(1,0,0,owner);
        effects[1]=CreateSceneEffect(0,0,0,owner);
        gSceneDisplay.byte59=(u8)(u32)pending;
        gSceneDisplay.byte58=(u8)(u32)pending;
        gSceneDisplay.byte63=(u8)(u32)pending;
        gSceneDisplay.byte62=160;
        gSceneDisplay.byte61=(u8)(u32)pending;
        gSceneDisplay.byte60=(u8)(u32)pending;
        gSceneDisplay.byte65=(u8)(u32)pending;
        gSceneDisplay.byte64=160;
        gSceneDisplay.byte66=63&~SceneWindowMask(2);
        gSceneDisplay.byte67=63;
        gSceneDisplay.byte68=63&~SceneWindowMask(2);
        gSceneDisplay.control|=0x6000;
        SetSceneEffectMode(work->effects[0],1);
        SetSceneEffectMode(effects[1],1);
        InitializeSceneInterpolation(&work->first_radius,0,120,40);
        InitializeSceneInterpolation(&work->second_radius,0,120,32);
        work->delay=8;
        InitializeSceneInterpolation(&work->vertical,0,5,32);
        ConvertSceneCoordinates(208,264,&work->x,&work->y);
        work->overlay=StartSceneOverlay((void*)0x083A6B1C,1,4,0,owner);
        context->state++;
        break;
    }
    case 257: {
        AdvanceSceneInterpolation(&work->first_radius);
        {
            register void *effect asm("r0")=work->effects[0];
            register s32 effect_x asm("r1")=work->x;
            register s32 effect_y asm("r2")=work->y;
            u16 radius;
            asm("" : : "r"(effect), "r"(effect_x), "r"(effect_y));
            radius=work->first_radius.value;
            SetSceneEffectDimensions(effect,effect_x,effect_y,radius,(u16)((s16)radius>>1));
        }
        {
        u16 delay=work->delay;
        if(delay) work->delay=delay-1;
        else {
            AdvanceSceneInterpolation(&work->second_radius);
            AdvanceSceneInterpolation(&work->vertical);
            {
                register void *effect asm("r0")=work->effects[1];
                register s32 effect_x asm("r1")=work->x;
                register s32 effect_y asm("r2")=(s16)(work->y-work->vertical.value);
                u16 radius;
                asm("" : : "r"(effect), "r"(effect_x), "r"(effect_y));
                radius=work->second_radius.value;
                SetSceneEffectDimensions(effect,effect_x,effect_y,radius,(u16)((s16)radius>>1));
            }
        }
        }
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        {
            u32 mask=SceneLayerMask(2);
            u32 control=gSceneDisplay.control;
            register u32 zero asm("r3");
            control&=~mask;
            zero=0;
            asm("" : "+r"(zero));
            control&=0x9FFF;
            gSceneDisplay.control=control;
            gSceneDisplay.byte74=zero;
        }
        RestoreSceneStage(0,0,0,0);
        context->state++;
        break;
    }
    case 258:
        work->effects[0]=DeleteSceneEffect(work->effects[0]);
        if(work->effects[0]) break;
        work->effects[1]=DeleteSceneEffect(work->effects[1]);
        if(work->effects[1]) break;
        context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x080035a9");

__asm__(".global RetailCall_080035D0\n.thumb_set RetailCall_080035D0, 0x080035d1");

__asm__(".global RetailCall_0801C960\n.thumb_set RetailCall_0801C960, 0x0801c961");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x080d35d9");

__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x080d3e9d");

__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x080d3f09");

__asm__(".global RetailCall_080D7220\n.thumb_set RetailCall_080D7220, 0x080d7221");

__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70, 0x080d7a71");

__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC, 0x080d7abd");

__asm__(".global RetailCall_080D9B64\n.thumb_set RetailCall_080D9B64, 0x080d9b65");

__asm__(".global RetailCall_080D9BA8\n.thumb_set RetailCall_080D9BA8, 0x080d9ba9");

__asm__(".global RetailCall_080DAB84\n.thumb_set RetailCall_080DAB84, 0x080dab85");

__asm__(".global RetailCall_080DAC80\n.thumb_set RetailCall_080DAC80, 0x080dac81");

__asm__(".global RetailCall_080DBED4\n.thumb_set RetailCall_080DBED4, 0x080dbed5");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x080dfd8d");

__asm__(".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608, 0x080e0609");

__asm__(".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C, 0x080e064d");
