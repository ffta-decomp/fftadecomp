typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *definition;u8 unknown08[12];u8 definition_id;};
struct SceneInterpolation {u16 value;u8 unknown02[10];};
struct SceneCoordinates {s16 x,y;};
struct RecordLayerSceneSequence {
    u8 variant,unknown01;u16 delay;s16 record_x,record_y;
    void *record,*script;
    struct SceneInterpolation horizontal,vertical;
    void *resource,*overlay;
};
struct SceneDisplayShadow {u16 control;};
extern struct SceneDisplayShadow gSceneDisplay;
extern const struct SceneCoordinates gLayerSceneStartingCoordinates[2];
__asm__(".global gSceneDisplay\n.set gSceneDisplay,0x03000940\n.global gLayerSceneStartingCoordinates\n.set gLayerSceneStartingCoordinates,0x083A6C18");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *StartRecordLayerResource(void*,u32,u32,u32,void*,void*,void*) asm("RetailCall_080DC1E8");
extern void *PollRecordLayerResource(void*) asm("RetailCall_080DBA5C");
extern u32 SceneLayerBaseFlags(void*) asm("RetailCall_08003A74");
extern u32 SceneLayerFormatFlags(void*) asm("RetailCall_08003A80");
extern u32 ApplySceneLayerSetup(u16,u32) asm("RetailCall_080034B8");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035A8");
extern u32 ConvertSceneCoordinates(s16,s16,s16*,s16*) asm("RetailCall_0801C960");
extern u32 ProjectRecordCoordinates(void*,s16,s16,s16*,s16*) asm("RetailCall_080DC224");
extern u32 SetSceneLayerX(s16,u32) asm("RetailCall_08003508");
extern u32 SetSceneLayerY(s16,u32) asm("RetailCall_08003558");
extern u32 ReadRecordCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern u32 InitializeSceneInterpolation(struct SceneInterpolation*,s32,s32,s32) asm("RetailCall_080E0608");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern u32 AdvanceSceneInterpolation(struct SceneInterpolation*) asm("RetailCall_080E064C");
extern u32 SceneInterpolationDone(struct SceneInterpolation*) asm("RetailCall_080E0690");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern u32 ClearSceneStage(void) asm("RetailCall_080D4020");
extern u32 UpdateDefinitionRecordFlag(void*,u32) asm("RetailCall_080DBEB4");
typedef char WorkSize[(sizeof(struct RecordLayerSceneSequence)==48)?1:-1];
typedef char InterpolationSize[(sizeof(struct SceneInterpolation)==12)?1:-1];
u32 AdvanceRecordLayerSceneSequence(void*,struct SceneContext*,struct RecordLayerSceneSequence*) asm("OriginalSceneDefinitionQuestion_0011C2E8");
u32 AdvanceRecordLayerSceneSequence(void *owner,struct SceneContext *context,struct RecordLayerSceneSequence *work)
{
    switch(context->state) {
    case 0:
        work->variant=context->definition_id-120;
        work->record=context->definition;
        break;
    case 1:
        ResumeScene();
        break;
    case 256:
        work->resource=StartRecordLayerResource(work->record,0,0,6,(void*)0x0600F9E0,(void*)0x06005000,owner);
        context->state++;
        break;
    case 257: {
        s16 x,y,destination_x,destination_y;
        const struct SceneCoordinates *coordinates;
        u32 flags;
        work->resource=PollRecordLayerResource(work->resource);
        if(work->resource) break;
        flags=SceneLayerBaseFlags((void*)0x06005000);
        flags|=SceneLayerFormatFlags((void*)0x06008000);
        ApplySceneLayerSetup((u16)flags,3);
        {
            u32 mask=SceneLayerMask(3);
            u32 control=gSceneDisplay.control;
            control|=mask;
            gSceneDisplay.control=control;
        }
        {
            /* Reuse the proven native root-before-index definition, with
             * the actual initialized ROM object and no emitted instruction. */
            register const struct SceneCoordinates *root asm("r0")=gLayerSceneStartingCoordinates;
            asm("" : "+r"(root));
            coordinates=(const struct SceneCoordinates *)((u32)(work->variant*sizeof(*root))+(u32)root);
        }
        ConvertSceneCoordinates(coordinates->x,coordinates->y,&x,&y);
        ProjectRecordCoordinates(work->record,x,y,&x,&y);
        y+=8;
        SetSceneLayerX(x,3);
        SetSceneLayerY(y,3);
        ReadRecordCoordinates(work->record,&work->record_x,&work->record_y);
        ProjectRecordCoordinates(work->record,work->record_x,work->record_y,&destination_x,&destination_y);
        InitializeSceneInterpolation(&work->horizontal,x,destination_x,90);
        InitializeSceneInterpolation(&work->vertical,y,destination_y,90);
        work->script=StartSceneScript((void*)0x0894DD84,owner);
        work->overlay=StartSceneOverlay((void*)0x083A6C10,1,4,0,owner);
        work->delay=40;
        context->state++;
        break;
    }
    case 258: {
        struct SceneInterpolation *horizontal;
        if(work->delay) {
            work->delay--;
            if(work->delay) break;
        }
        horizontal=&work->horizontal;
        AdvanceSceneInterpolation(horizontal);
        AdvanceSceneInterpolation(&work->vertical);
        SetSceneLayerX((s16)work->horizontal.value,3);
        SetSceneLayerY((s16)work->vertical.value,3);
        if(!(u8)SceneInterpolationDone(horizontal)) break;
        work->delay=40;
        context->state++;
        break;
    }
    case 259:
        if(work->delay) {
            work->delay--;
            if(work->delay) break;
        }
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        {
            u32 mask=SceneLayerMask(3);
            u32 control=gSceneDisplay.control;
            control&=~mask;
            gSceneDisplay.control=control;
        }
        ClearSceneStage();
        UpdateDefinitionRecordFlag(work->record,1);
        context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_080034B8\n.thumb_set RetailCall_080034B8, 0x080034b9");

__asm__(".global RetailCall_08003508\n.thumb_set RetailCall_08003508, 0x08003509");

__asm__(".global RetailCall_08003558\n.thumb_set RetailCall_08003558, 0x08003559");

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x080035a9");

__asm__(".global RetailCall_08003A74\n.thumb_set RetailCall_08003A74, 0x08003a75");

__asm__(".global RetailCall_08003A80\n.thumb_set RetailCall_08003A80, 0x08003a81");

__asm__(".global RetailCall_0801C960\n.thumb_set RetailCall_0801C960, 0x0801c961");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x080d35d9");

__asm__(".global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x080d3e9d");

__asm__(".global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x080d3f09");

__asm__(".global RetailCall_080D4020\n.thumb_set RetailCall_080D4020, 0x080d4021");

__asm__(".global RetailCall_080DBA5C\n.thumb_set RetailCall_080DBA5C, 0x080dba5d");

__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8, 0x080dbdc9");

__asm__(".global RetailCall_080DBEB4\n.thumb_set RetailCall_080DBEB4, 0x080dbeb5");

__asm__(".global RetailCall_080DC1E8\n.thumb_set RetailCall_080DC1E8, 0x080dc1e9");

__asm__(".global RetailCall_080DC224\n.thumb_set RetailCall_080DC224, 0x080dc225");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x080dfd8d");

__asm__(".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608, 0x080e0609");

__asm__(".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C, 0x080e064d");

__asm__(".global RetailCall_080E0690\n.thumb_set RetailCall_080E0690, 0x080e0691");
