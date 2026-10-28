typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct SceneContext {u16 state;};
struct SceneLayerState {u8 layer,mode,parameter,unknown03; s16 x,y; u32 parameter8,parameter12;};
struct TwoLayerSequence {
    u16 tick; u8 unknown02[6]; void *motion; u8 motion_state[20];
    void *resource,*initial_transition;
    struct SceneLayerState first,second;
    void *overlay;
};
struct SceneDisplayShadow {
    u16 control; u8 unknown02[56];
    volatile u8 byte58,byte59; u8 unknown60[2];
    volatile u8 byte62,byte63; u8 unknown64[2];
    volatile u8 byte66; u8 unknown67; volatile u8 byte68,byte69;
};
extern struct SceneDisplayShadow gSceneDisplay;
extern u16 gScenePalette[];
extern const u8 gSceneWindowTicks[5],gSceneWindowValues[5];
__asm__(".global gSceneDisplay\n.set gSceneDisplay,0x03000940\n.global gScenePalette\n.set gScenePalette,0x03003860\n.global gSceneWindowTicks\n.set gSceneWindowTicks,0x08149F88\n.global gSceneWindowValues\n.set gSceneWindowValues,0x08149F8D");
extern void *StartTransition(const void*,u32,void*) asm("RetailCall_080D7A70");
extern u32 SetSequenceResource(const void*,u32,u32,u32,u32) asm("RetailCall_080D45D0");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *PollTransition(void*) asm("RetailCall_080D7ABC");
extern void *StartLayerResource(u32,u32,void*,void*,void*) asm("RetailCall_080D8A58");
extern void *PollLayerResource(void*) asm("RetailCall_080D8AEC");
extern u32 ReadSceneLayer(u32,struct SceneLayerState*) asm("RetailCall_0801E1B8");
extern u32 ReadSceneCoordinates(s16*,s16*) asm("RetailCall_080D8A98");
extern u32 ApplySceneLayer(u32,u32,u32,s16,s16,u32,u32) asm("RetailCall_080D74E0");
extern u32 LayerControlMask(u32) asm("RetailCall_080035A8");
extern u32 LayerWindowMask(u32) asm("RetailCall_080035D0");
extern void *StartSceneMotion(s16,s16,u32,u32,u32,void*,const void*,void*) asm("RetailCall_080D6098");
extern u32 ReadScenePaletteIndices(u8*,u8*) asm("RetailCall_0801E6D4");
extern u32 HasScenePalette(void) asm("RetailCall_080D39F0");
extern void *GetScenePalette(void) asm("RetailCall_080D3904");
extern u32 TransferScenePalette(const void*,void*,u32) asm("RetailCall_0814186C");
extern u32 FillScenePalette(u32,void*) asm("RetailCall_0801A42C");
extern void *StartOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void *CopySceneBytes(void*,const void*,u32) asm("RetailCall_081443FC");
extern void *PollSceneMotion(void*) asm("RetailCall_080D6134");
typedef char LayerSize[(sizeof(struct SceneLayerState)==16)?1:-1];
typedef char WorkSize[(sizeof(struct TwoLayerSequence)==76)?1:-1];
u32 AdvanceTwoLayerSceneSequence(void*,struct SceneContext*,struct TwoLayerSequence*) asm("OriginalSceneDefinitionQuestion_0011B3B0");
u32 AdvanceTwoLayerSceneSequence(void *owner,struct SceneContext *context,struct TwoLayerSequence *work)
{
    switch(context->state) {
    case 0:
        work->initial_transition=StartTransition((void*)0x083A6A18,1,owner);
        SetSequenceResource((void*)0x088EB4A4,6,0,0,1);
        break;
    case 1:
        ResumeScene();
        break;
    case 256:
        work->initial_transition=PollTransition(work->initial_transition);
        if(work->initial_transition) break;
        work->resource=StartLayerResource(1,6,(void*)0x06005000,(void*)0x06005800,owner);
        context->state++;
        break;
    case 257: {
        s16 x,y;
        u8 palette_index,other_palette_index;
        u16 saved_palette;
        u8 *palette;
        work->resource=PollLayerResource(work->resource);
        if(work->resource) break;
        ReadSceneLayer(0,&work->first);
        ReadSceneLayer(1,&work->second);
        ReadSceneCoordinates(&x,&y);
        ApplySceneLayer(work->second.layer,0,work->second.parameter,x,y,0x06000000,0x06005800);
        ApplySceneLayer(work->first.layer,0,work->first.parameter,x,y,0x06000000,0x06005000);
        ApplySceneLayer(2,work->second.mode,work->second.parameter,work->second.x,work->second.y,work->second.parameter8,work->second.parameter12);
        ApplySceneLayer(3,work->first.mode,work->first.parameter,work->first.x,work->first.y,work->first.parameter8,work->first.parameter12);
        {
            u32 control_mask=LayerControlMask(2);
            u32 control=gSceneDisplay.control;
            control|=control_mask;
            gSceneDisplay.control=control;
        }
        {
            u32 control_mask=LayerControlMask(3);
            u32 control=gSceneDisplay.control;
            control|=control_mask;
            gSceneDisplay.control=control;
        }
        gSceneDisplay.byte59=0;
        gSceneDisplay.byte58=240;
        gSceneDisplay.byte63=160;
        gSceneDisplay.byte62=160;
        {
            u32 window_mask=LayerWindowMask(work->first.layer);
            window_mask|=LayerWindowMask(work->second.layer);
            gSceneDisplay.byte66=63&~window_mask;
        }
        gSceneDisplay.byte68=63;
        {
            u32 window_mask=LayerWindowMask(work->first.layer);
            window_mask|=LayerWindowMask(work->second.layer);
            gSceneDisplay.byte69=63&~window_mask;
        }
        gSceneDisplay.control|=0x2000;
        gSceneDisplay.control|=0x8000;
        work->motion=StartSceneMotion(120,0,0,1,5,work->motion_state,(void*)0x083A6A24,owner);
        saved_palette=gScenePalette[0];
        ReadScenePaletteIndices(&palette_index,&other_palette_index);
        palette=(u8*)gScenePalette+palette_index*32;
        if((u8)HasScenePalette())
            TransferScenePalette(GetScenePalette(),palette,96);
        else
            FillScenePalette(0xFFFFFFFF,palette);
        gScenePalette[0]=saved_palette;
        SetSequenceResource((void*)0x088EB4A4,6,0,0,1);
        work->overlay=StartOverlay((void*)0x083A6A9C,1,4,0,owner);
        context->state++;
        break;
    }
    case 258: {
        u8 ticks[5],values[5];
        u8 index;
        CopySceneBytes(ticks,gSceneWindowTicks,5);
        CopySceneBytes(values,gSceneWindowValues,5);
        work->tick++;
        for(index=0;index<5;index++) {
            if(work->tick==ticks[index]) {
                gSceneDisplay.byte63=values[index];
                break;
            }
        }
        work->motion=PollSceneMotion(work->motion);
        if(work->motion) break;
        ApplySceneLayer(work->second.layer,work->second.mode,work->second.parameter,work->second.x,work->second.y,work->second.parameter8,work->second.parameter12);
        ApplySceneLayer(work->first.layer,work->first.mode,work->first.parameter,work->first.x,work->first.y,work->first.parameter8,work->first.parameter12);
        {
            u32 control_mask=LayerControlMask(2);
            gSceneDisplay.control&=~control_mask;
        }
        {
            u32 control_mask=LayerControlMask(3);
            gSceneDisplay.control&=~control_mask;
        }
        gSceneDisplay.control&=0xDFFF;
        gSceneDisplay.control&=0x7FFF;
        context->state++;
        break;
    }
    case 259:
        context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x080035a9");

__asm__(".global RetailCall_080035D0\n.thumb_set RetailCall_080035D0, 0x080035d1");

__asm__(".global RetailCall_0801A42C\n.thumb_set RetailCall_0801A42C, 0x0801a42d");

__asm__(".global RetailCall_0801E1B8\n.thumb_set RetailCall_0801E1B8, 0x0801e1b9");

__asm__(".global RetailCall_0801E6D4\n.thumb_set RetailCall_0801E6D4, 0x0801e6d5");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x080d35d9");

__asm__(".global RetailCall_080D3904\n.thumb_set RetailCall_080D3904, 0x080d3905");

__asm__(".global RetailCall_080D39F0\n.thumb_set RetailCall_080D39F0, 0x080d39f1");

__asm__(".global RetailCall_080D45D0\n.thumb_set RetailCall_080D45D0, 0x080d45d1");

__asm__(".global RetailCall_080D6098\n.thumb_set RetailCall_080D6098, 0x080d6099");

__asm__(".global RetailCall_080D6134\n.thumb_set RetailCall_080D6134, 0x080d6135");

__asm__(".global RetailCall_080D74E0\n.thumb_set RetailCall_080D74E0, 0x080d74e1");

__asm__(".global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70, 0x080d7a71");

__asm__(".global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC, 0x080d7abd");

__asm__(".global RetailCall_080D8A58\n.thumb_set RetailCall_080D8A58, 0x080d8a59");

__asm__(".global RetailCall_080D8A98\n.thumb_set RetailCall_080D8A98, 0x080d8a99");

__asm__(".global RetailCall_080D8AEC\n.thumb_set RetailCall_080D8AEC, 0x080d8aed");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x080dfd8d");

__asm__(".global RetailCall_0814186C\n.thumb_set RetailCall_0814186C, 0x0814186d");

__asm__(".global RetailCall_081443FC\n.thumb_set RetailCall_081443FC, 0x081443fd");
