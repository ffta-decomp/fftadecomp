typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneContext {u16 state;};
struct PaletteSceneSequence {u8 unknown00[8];void *asset,*overlay;};
struct ScenePalette {u8 unknown00[318];u16 entry159;};
struct SceneRecord {u8 bytes[12];};
extern struct ScenePalette gScenePalette;
extern const struct SceneRecord gCompletionRecords[];
__asm__(".global gScenePalette\n.set gScenePalette,0x03003860\n.global gCompletionRecords\n.set gCompletionRecords,0x083A69F0");
extern u32 ResumeScene(void) asm("RetailCall_080D35D8");
extern void *StartSceneAsset(const void*,void*) asm("RetailCall_080D4704");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void *PollSceneAsset(void*) asm("RetailCall_080D4774");
extern u32 HasScenePalette(void) asm("RetailCall_080D39F0");
extern void *GetScenePalette(void) asm("RetailCall_080D3904");
extern u32 TransferScenePalette(const void*,void*,u32) asm("RetailCall_0814186C");
extern void *GetSceneTransferSource(void) asm("RetailCall_080D3AF8");
extern u32 TransferSceneData(const void*,u32,void*,u32) asm("RetailCall_08000B68");
extern u32 CommitSceneRecord(const struct SceneRecord*,u32,u32) asm("RetailCall_0801B73C");
typedef char WorkSize[(sizeof(struct PaletteSceneSequence)==16)?1:-1];
typedef char RecordSize[(sizeof(struct SceneRecord)==12)?1:-1];
u32 AdvancePaletteCompletionScene(void*,struct SceneContext*,struct PaletteSceneSequence*) asm("OriginalCallbackQuestion_0011B1C8");
u32 AdvancePaletteCompletionScene(void *owner,struct SceneContext *context,struct PaletteSceneSequence *work)
{
    switch(context->state) {
    case 0:
        break;
    case 1:
        ResumeScene();
        break;
    case 256:
        work->asset=StartSceneAsset((void*)0x0894C758,owner);
        work->overlay=StartSceneOverlay((void*)0x083A69E8,1,4,0,owner);
        context->state++;
        break;
    case 257: {
        void *pending;
        u8 ordinal;
        pending=PollSceneAsset(work->asset);
        work->asset=pending;
        if(pending) break;
        if((u8)HasScenePalette()) {
            u8 *destination=GetScenePalette();
            destination+=158;
            TransferScenePalette((void*)0x03003900,destination,16);
        }
        TransferSceneData(GetSceneTransferSource(),0xFFFFFFFF,(void*)0x06004FE0,8);
        /* The original reuses the completed asset's actual zero value. */
        gScenePalette.entry159=(u16)(u32)pending;
        {
            u32 record_parameter=0x927F;
            for(ordinal=0;ordinal<2;ordinal++)
                CommitSceneRecord(gCompletionRecords+ordinal,1,record_parameter);
        }
        context->state=2;
        break;
    }
    }
    return 0;
}

__asm__(".global RetailCall_08000B68\n.thumb_set RetailCall_08000B68, 0x08000b69");

__asm__(".global RetailCall_0801B73C\n.thumb_set RetailCall_0801B73C, 0x0801b73d");

__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8, 0x080d35d9");

__asm__(".global RetailCall_080D3904\n.thumb_set RetailCall_080D3904, 0x080d3905");

__asm__(".global RetailCall_080D39F0\n.thumb_set RetailCall_080D39F0, 0x080d39f1");

__asm__(".global RetailCall_080D3AF8\n.thumb_set RetailCall_080D3AF8, 0x080d3af9");

__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704, 0x080d4705");

__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774, 0x080d4775");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C, 0x080dfd8d");

__asm__(".global RetailCall_0814186C\n.thumb_set RetailCall_0814186C, 0x0814186d");
