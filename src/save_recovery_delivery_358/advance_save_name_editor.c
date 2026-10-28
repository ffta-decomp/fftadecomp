#include "../task_tree_core.h"
struct SaveNameContext {
    u8 *caller; u16 unknown_04; u16 name_kind;
    u8 unknown_08[0x298-8];
    void *resource; void *name_resource;
    u8 unknown_2a0[0x2f4-0x2a0];
    u8 tick_flag; u8 unknown_2f5; signed char page; u8 init_page; u8 timer;
    u8 unknown_2f9[3];
    void *buffer_large; void *buffer_tiles; void *buffer_small;
    void *buffer_a; void *buffer_b;
    u8 editor_flag_a; u8 editor_flag_b; u8 edited_name[18];
    u8 primary_cursor; u8 secondary_cursor; u8 name_length; u8 unknown_327;
    u8 reset_required; u8 unknown_329[3]; void *window; u8 phase;
};
struct NameEvent { u16 state; u16 unknown_02; u8 *caller; u8 unknown_08[12]; u16 name_kind; };
struct DisplayResource { u8 unknown_00[20]; void *data; };
extern u8 PrimaryLiveName[], SecondaryLiveName[];
extern struct DisplayResource DisplayA, DisplayB;
extern u16 InputState[];
extern void BiosCpuSet(const void *,void *,u32);
extern void *SelectNameResource(u32);
extern void *GetEditorResource(void);
extern void *Allocate(u32);
extern void Free(void *);
extern void *CreateWindow(u32);
extern void DestroyWindow(void *);
extern void InitializeEditor(void);
extern u32 NameByteLength(const u8 *);
extern void PadEditedSaveName(u8 *);
extern u32 UnsignedModulo(u32,u32);
extern void LoadEditorPage(struct SaveNameContext *,u32);
extern void PrepareEditorPage(struct SaveNameContext *,u32);
extern void ActivateNameResource(void *);
extern void ConfigureEditor(struct SaveNameContext *);
extern void UpdateEditor(struct SaveNameContext *);
extern void *GetEditorPage(struct SaveNameContext *);
extern void CopyEditorPage(void *,void *,u32);
extern void CopyEditorTiles(void *,void *,void *,u32);
extern void ConfigureDisplay(void *,u32,u32,u32,u32,u32,u32,u32);
extern u32 PollEditorOpen(struct SaveNameContext *);
extern void UpdateEditorInput(struct SaveNameContext *);
extern void UpdateEditorSelection(struct SaveNameContext *);
extern void UpdateEditorCursor(struct SaveNameContext *);
extern void DrawEditor(struct SaveNameContext *);
extern void AdvanceSaveNameCommit(u16 *,struct SaveNameContext *);
extern void DrawEditorConfirmation(struct SaveNameContext *);
extern u32 PollEditorClose(struct SaveNameContext *);
extern void RestoreNameResource(u32);
extern void RestoreDisplay(void);
extern void ConfigureBackground(u32,u32,u32,u32,u32,void *,void *);
u32 AdvanceSaveNameEditor(u32 unused,struct NameEvent *event,struct SaveNameContext *context)
{
    context->tick_flag=0;
    switch(event->state) {
    case 0:
        context->caller=event->caller;
        context->name_kind=event->name_kind;
        break;
    case 1: break;
    case 256: {
        u32 resource_kind;
        u8 *edited;
        if(context->name_kind!=0) {
            BiosCpuSet(PrimaryLiveName,context->edited_name,10);
            resource_kind=15;
        } else {
            BiosCpuSet(SecondaryLiveName,context->edited_name,10);
            resource_kind=8;
        }
        context->name_resource=SelectNameResource(resource_kind);
        context->resource=GetEditorResource();
        context->buffer_large=Allocate(50688);
        context->buffer_tiles=Allocate(1152);
        context->buffer_small=Allocate(240);
        context->buffer_a=Allocate(256);
        context->buffer_b=Allocate(256);
        context->window=CreateWindow(0xa04);
        InitializeEditor();
        context->unknown_04=0;
        context->page=0;
        context->editor_flag_b=0;
        context->editor_flag_a=0;
        context->unknown_327=0;
        edited=context->edited_name;
        context->name_length=NameByteLength(edited)>>1;
        PadEditedSaveName(edited);
        context->primary_cursor=0;
        context->secondary_cursor=0;
        context->init_page=0;
        context->timer=0;
        event->state=257;
        break;
    }
    case 257:
        context->timer++;
        if((u8)UnsignedModulo(context->timer,3)==0) {
            LoadEditorPage(context,context->init_page);
            PrepareEditorPage(context,context->init_page);
            if(++context->init_page>1) event->state=258;
            context->timer=0;
        }
        break;
    case 258:
        ActivateNameResource(context->name_resource);
        ConfigureEditor(context);
        UpdateEditor(context);
        CopyEditorPage(GetEditorPage(context),(void *)0x06016300,(u8)context->page);
        CopyEditorTiles(GetEditorPage(context),context->buffer_large,(void *)0x0600a280,(u8)context->page);
        ConfigureDisplay(DisplayA.data,2,4,21,6,32,276,11);
        event->state=259;
        break;
    case 259:
        if((u8)PollEditorOpen(context)!=0) event->state=260;
        break;
    case 260:
        if(InputState[1]&8) {
            event->state=262;
            context->phase=0;
        }
        UpdateEditorInput(context);
        UpdateEditorSelection(context);
        UpdateEditorCursor(context);
        DrawEditor(context);
        break;
    case 262:
        AdvanceSaveNameCommit(&event->state,context);
        DrawEditorConfirmation(context);
        break;
    case 263:
        if((u8)PollEditorClose(context)!=0) event->state=264;
        break;
    case 264: {
        u16 fill_a;
        u16 fill_b;
        Free(context->buffer_large);
        Free(context->buffer_tiles);
        Free(context->buffer_small);
        Free(context->buffer_a);
        Free(context->buffer_b);
        DestroyWindow(context->window);
        RestoreNameResource((u8)context->name_kind);
        fill_a=0;
        BiosCpuSet(&fill_a,DisplayA.data,0x01000400);
        fill_b=0;
        BiosCpuSet(&fill_b,DisplayB.data,0x01000400);
        RestoreDisplay();
        ConfigureBackground(2,1,0,0,0,(void *)0x06008000,(void *)0x0600e000);
        ConfigureBackground(3,1,1,0,0,(void *)0x06008000,(void *)0x06005000);
        context->caller[6]=1;
        event->state=3;
        break;
    }
    }
    return 0;
}
asm(".global ConfigureDisplay\n.thumb_set ConfigureDisplay,0x080157a9\n.global ConfigureBackground\n.thumb_set ConfigureBackground,0x0801e459\n.global Allocate\n.thumb_set Allocate,0x08022841\n.global Free\n.thumb_set Free,0x08022855\n.global RestoreDisplay\n.thumb_set RestoreDisplay,0x0802b8e9\n.global SelectNameResource\n.thumb_set SelectNameResource,0x080c83cd\n.global GetEditorResource\n.thumb_set GetEditorResource,0x080cb929\n.global RestoreNameResource\n.thumb_set RestoreNameResource,0x080cea81\n.global CreateWindow\n.thumb_set CreateWindow,0x08121b65\n.global DestroyWindow\n.thumb_set DestroyWindow,0x08121b79\n.global DrawEditor\n.thumb_set DrawEditor,0x0812a441\n.global DrawEditorConfirmation\n.thumb_set DrawEditorConfirmation,0x0812a52d\n.global AdvanceSaveNameCommit\n.thumb_set AdvanceSaveNameCommit,0x0812a5bd\n.global UpdateEditorInput\n.thumb_set UpdateEditorInput,0x0812a91d\n.global UpdateEditorSelection\n.thumb_set UpdateEditorSelection,0x0812ac09\n.global PrepareEditorPage\n.thumb_set PrepareEditorPage,0x0812ad15\n.global UpdateEditor\n.thumb_set UpdateEditor,0x0812ae8d\n.global PollEditorOpen\n.thumb_set PollEditorOpen,0x0812af1d\n.global PollEditorClose\n.thumb_set PollEditorClose,0x0812b095\n.global ConfigureEditor\n.thumb_set ConfigureEditor,0x0812b259\n.global ActivateNameResource\n.thumb_set ActivateNameResource,0x0812b2ed\n.global InitializeEditor\n.thumb_set InitializeEditor,0x0812b341\n.global CopyEditorPage\n.thumb_set CopyEditorPage,0x0812b41d\n.global CopyEditorTiles\n.thumb_set CopyEditorTiles,0x0812b44d\n.global LoadEditorPage\n.thumb_set LoadEditorPage,0x0812b469\n.global GetEditorPage\n.thumb_set GetEditorPage,0x0812b4e1\n.global UpdateEditorCursor\n.thumb_set UpdateEditorCursor,0x0812b505\n.global PadEditedSaveName\n.thumb_set PadEditedSaveName,0x0812b59d\n.global BiosCpuSet\n.thumb_set BiosCpuSet,0x0814186d\n.global UnsignedModulo\n.thumb_set UnsignedModulo,0x08142b29\n.global NameByteLength\n.thumb_set NameByteLength,0x081444b9\n.global PrimaryLiveName\n.set PrimaryLiveName,0x02001f1c\n.global SecondaryLiveName\n.set SecondaryLiveName,0x020021a0\n.global DisplayA\n.set DisplayA,0x030008b0\n.global DisplayB\n.set DisplayB,0x03000990\n.global InputState\n.set InputState,0x03000000\n");
