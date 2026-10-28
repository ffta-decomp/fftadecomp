#include "../task_tree_core.h"
struct SaveNameContext {
    u8 unknown_00[0x2f6];
    signed char page;
    u8 unknown_2f7[5];
    void *buffer_large;
};
extern u16 InputState[];
extern const u8 PageLabelA[],PageLabelB[];
extern void AcknowledgeInput(u16 *);
extern void PlayEditorAction(u32);
extern void *GetEditorPage(struct SaveNameContext *);
extern void CopyEditorTiles(void *,void *,void *,u32);
extern void CopyEditorPage(void *,void *,u32);
extern void DrawEditorLabel(const u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
void UpdateSaveNamePage(struct SaveNameContext *context)
{
    u16 input=InputState[2];
    if(input&0x100) {
        AcknowledgeInput(InputState);
        PlayEditorAction(102);
        if(++context->page>1) context->page=0;
        CopyEditorTiles(GetEditorPage(context),context->buffer_large,(void *)0x0600a280,(u8)context->page);
        CopyEditorPage(GetEditorPage(context),(void *)0x06016300,(u8)context->page);
    } else {
        register u32 page_mask asm("r0")=0x200;
        asm("" : "+r"(page_mask));
        page_mask &= input;
        if(page_mask) {
        AcknowledgeInput(InputState);
        PlayEditorAction(102);
        if(--context->page<0) context->page=1;
        CopyEditorTiles(GetEditorPage(context),context->buffer_large,(void *)0x0600a280,(u8)context->page);
        CopyEditorPage(GetEditorPage(context),(void *)0x06016300,(u8)context->page);
    }
    }
    DrawEditorLabel(PageLabelA,24,3,0,0,0,0,0,0,0,0);
    DrawEditorLabel(PageLabelB,152,3,0,0,0,0,0,0,0,0);
}
asm(".global InputState\n.set InputState,0x03000000\n.global PageLabelA\n.set PageLabelA,0x083a82e4\n.global PageLabelB\n.set PageLabelB,0x083a82dc\n.global AcknowledgeInput\n.thumb_set AcknowledgeInput,0x080023d1\n.global PlayEditorAction\n.thumb_set PlayEditorAction,0x08141541\n.global GetEditorPage\n.thumb_set GetEditorPage,0x0812b4e1\n.global CopyEditorTiles\n.thumb_set CopyEditorTiles,0x0812b44d\n.global CopyEditorPage\n.thumb_set CopyEditorPage,0x0812b41d\n.global DrawEditorLabel\n.thumb_set DrawEditorLabel,0x08001f35\n");
