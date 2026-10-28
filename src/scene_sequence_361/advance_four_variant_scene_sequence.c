typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct SceneContext {u16 state; u8 unknown02[18]; u8 definition;};
struct SceneSequence {
    u8 unknown00[2]; u8 variant; u8 unknown03;
    s16 x,y;
    void *object, *motion;
    u8 motion_state[32];
    void *script, *first_asset, *second_asset, *initial_transition, *transition;
};
struct CoordinatePair {s16 x,y;};
struct VariantSceneRecord {u8 bytes[12];};
extern const struct CoordinatePair gVariantCoordinates[4];
extern const u8 gVariantObjectCodes[4];
extern const struct VariantSceneRecord gVariantSceneRecords[4];
__asm__(".global gVariantCoordinates\n.set gVariantCoordinates,0x083A69A4\n.global gVariantObjectCodes\n.set gVariantObjectCodes,0x083A69B4\n.global gVariantSceneRecords\n.set gVariantSceneRecords,0x083A69B8");
struct SequencePalette {u8 unknown00[194]; u16 white;};
struct SequenceDisplay {u16 control;u8 unknown02[66]; volatile u8 inside,outside;u8 unknown46[4];volatile u8 blend;};
extern struct SequencePalette gSequencePalette;
extern struct SequenceDisplay gSequenceDisplay;
__asm__(".global gSequencePalette\n.set gSequencePalette,0x03003860\n.global gSequenceDisplay\n.set gSequenceDisplay,0x03000940");
extern void *StartSequenceTransition(const void*,u32,void*) asm("RetailCall_080D7A70");
extern void ResumeScene(void) asm("RetailCall_080D35D8");
extern void *PollSequenceTransition(void*) asm("RetailCall_080D7ABC");
extern void LoadSequenceContent(const void*,u32,u32,u32,u32,u32) asm("RetailCall_080D7220");
extern void *StartSceneScript(const void*,void*) asm("RetailCall_080D3E9C");
extern void *StartSceneAsset(const void*,void*) asm("RetailCall_080D4704");
extern void ConvertSceneCoordinates(s16,s16,s16*,s16*) asm("RetailCall_0801C960");
extern void *CreateSequenceMotion(s16,s16,u32,u32,u32,void*,const void*,void*) asm("RetailCall_080D6098");
extern void *CreateSceneObject(const void*,u32,s16,s16,u32,u32,u32,u32) asm("RetailCall_080D5CC0");
extern void SetSceneObjectState(void*,u32) asm("RetailCall_08011100");
extern u32 SceneLayerMask(u32) asm("RetailCall_080035D0");
extern void *StartSequenceOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void *PollSceneScript(void*) asm("RetailCall_080D3F08");
extern void SetVariantSceneRecord(const void*,u32) asm("RetailCall_0801B798");
extern void CommitVariantSceneRecord(void) asm("RetailCall_0801B878");
extern void *PollSceneObject(void*) asm("RetailCall_08011484");
extern void *PollSceneAsset(void*) asm("RetailCall_080D4774");
extern void *PollSequenceMotion(void*) asm("RetailCall_080D6134");
extern u32 SceneLayerReleaseMask(u32) asm("RetailCall_080035A8");

typedef char WorkSize[(sizeof(struct SceneSequence)==68)?1:-1];
u32 AdvanceFourVariantSceneSequence(void*,struct SceneContext*,struct SceneSequence*) asm("OriginalSceneDefinitionCallback_0811AF98");
u32 AdvanceFourVariantSceneSequence(void *owner,struct SceneContext *context,struct SceneSequence *work)
{
    void *pending;
    const struct CoordinatePair *coordinates;
    switch(context->state) {
    case 0:
        work->variant=context->definition-107;
        work->initial_transition=StartSequenceTransition((void*)0x083A688C,5,owner);
        gSequencePalette.white=32767;
        break;
    case 1:
        ResumeScene();
        break;
    case 256: {
        u32 mask;
        pending=PollSequenceTransition(work->initial_transition);
        work->initial_transition=pending;
        if(pending) break;
        LoadSequenceContent((void*)0x088F46CC,0,2,0,0,0);
        work->script=StartSceneScript((void*)0x083A6988,owner);
        work->first_asset=StartSceneAsset((void*)0x0894C744,owner);
        {
            /* Actual ROM root is defined before the variant read in native. */
            register const struct CoordinatePair *root asm("r0") = gVariantCoordinates;
            asm("" : "+r"(root));
            /* Native forms the byte displacement, then adds the ROM root. */
            coordinates=(const struct CoordinatePair *)
                ((u32)(work->variant * sizeof(*root)) + (u32)root);
        }
        ConvertSceneCoordinates(coordinates->x,coordinates->y,&work->x,&work->y);
        work->motion=CreateSequenceMotion(work->x,work->y,0,1,8,work->motion_state,(void*)0x083A68C8,owner);
        work->object=CreateSceneObject((void*)0x08507828,gVariantObjectCodes[work->variant],work->x,work->y,844,0,0,0);
        SetSceneObjectState(work->object,2);
        mask=SceneLayerMask(2);
        gSequenceDisplay.inside=63&~mask;
        gSequenceDisplay.outside=63;
        gSequenceDisplay.control|=32768;
        work->transition=StartSequenceOverlay((void*)0x083A699C,1,4,64,owner);
        context->state++;
        break;
    }
    case 257:
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        SetVariantSceneRecord(gVariantSceneRecords+work->variant,0);
        CommitVariantSceneRecord();
        work->script=StartSceneScript((void*)0x083A6992,owner);
        work->second_asset=StartSceneAsset((void*)0x08949F18,owner);
        context->state++;
        break;
    case 258: {
        u32 mask;
        u32 flags;
        register u32 clear asm("r3");
        work->script=PollSceneScript(work->script);
        if(work->script) break;
        work->object=PollSceneObject(work->object);
        if(work->object) break;
        work->first_asset=PollSceneAsset(work->first_asset);
        if(work->first_asset) break;
        work->second_asset=PollSceneAsset(work->second_asset);
        if(work->second_asset) break;
        work->motion=PollSequenceMotion(work->motion);
        if(work->motion) break;
        mask=SceneLayerReleaseMask(2);
        flags=gSequenceDisplay.control&~mask;
        /* Native defines this real clearing value before finishing the mask. */
        clear=0;
        asm("" : "+r"(clear));
        flags&=32767;
        gSequenceDisplay.control=flags;
        gSequenceDisplay.blend=clear;
        context->state=2;
        break;
    }
    }
    return 0;
}

__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8, 0x080035a9\n.global RetailCall_080035D0\n.thumb_set RetailCall_080035D0, 0x080035d1\n.global RetailCall_08011100\n.thumb_set RetailCall_08011100, 0x08011101\n.global RetailCall_08011484\n.thumb_set RetailCall_08011484, 0x08011485\n.global RetailCall_0801B798\n.thumb_set RetailCall_0801B798, 0x0801b799\n.global RetailCall_0801B878\n.thumb_set RetailCall_0801B878, 0x0801b879\n.global RetailCall_0801C960\n.thumb_set RetailCall_0801C960, 0x0801c961\n.global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x080d35d9\n.global RetailCall_080D3E9C\n.thumb_set RetailCall_080D3E9C, 0x080d3e9d\n.global RetailCall_080D3F08\n.thumb_set RetailCall_080D3F08, 0x080d3f09\n.global RetailCall_080D4704\n.thumb_set RetailCall_080D4704, 0x080d4705\n.global RetailCall_080D4774\n.thumb_set RetailCall_080D4774, 0x080d4775\n.global RetailCall_080D5CC0\n.thumb_set RetailCall_080D5CC0, 0x080d5cc1\n.global RetailCall_080D6098\n.thumb_set RetailCall_080D6098, 0x080d6099\n.global RetailCall_080D6134\n.thumb_set RetailCall_080D6134, 0x080d6135\n.global RetailCall_080D7220\n.thumb_set RetailCall_080D7220, 0x080d7221\n.global RetailCall_080D7A70\n.thumb_set RetailCall_080D7A70, 0x080d7a71\n.global RetailCall_080D7ABC\n.thumb_set RetailCall_080D7ABC, 0x080d7abd\n.global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x080dfd8d\n");
