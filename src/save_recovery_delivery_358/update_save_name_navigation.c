#include "../task_tree_core.h"
struct SaveNameContext {
    u8 unknown_00[0x2f6]; signed char page;
    u8 unknown_2f7[0x310-0x2f7];
    signed char column; signed char row;
    u8 unknown_312[0x327-0x312]; u8 animation;
};
extern u16 InputState[];
extern const u8 RowWidths[],CursorGraphic[];
extern void AcknowledgeInput(u16 *);
extern void PlayEditorAction(u32);
extern void DrawEditorCursor(const u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void HandleNameEditorButtons(struct SaveNameContext *);
void UpdateSaveNameNavigation(struct SaveNameContext *context)
{
    u16 input=InputState[2];
    u32 up=(u16)(input&64);
    u32 left;
    u32 cursor_x,cursor_y,animation;
    if(up) {
        AcknowledgeInput(InputState);
        PlayEditorAction(108);
        if(--context->row<0) context->row=5;
    } else {
        register u32 down_mask asm("r0")=128;
        asm("" : "+r"(down_mask));
        down_mask &= input;
        if(down_mask) {
        AcknowledgeInput(InputState);
        PlayEditorAction(108);
        if(++context->row>5) context->row=up;
    }
    }
    input=InputState[2];
    left=(u16)(input&32);
    if(left) {
        AcknowledgeInput(InputState);
        PlayEditorAction(108);
        if(--context->column<0)
            context->column=RowWidths[context->row+context->page*6]-1;
    } else {
        register u32 right_mask asm("r0")=16;
        asm("" : "+r"(right_mask));
        right_mask &= input;
        if(right_mask) {
        AcknowledgeInput(InputState);
        PlayEditorAction(108);
        ++context->column;
        if(context->column<RowWidths[context->row+context->page*6]) goto draw_cursor;
        context->column=left;
    }
    }
    if(context->column>=RowWidths[context->row+context->page*6])
        context->column=RowWidths[context->row+context->page*6]-1;
draw_cursor:
    cursor_x=((u32)(u8)context->column<<28)>>24;
    cursor_y=(((u32)(u8)context->row<<28)+0x24000000u)>>24;
    animation=context->animation+6;
    context->animation=animation;
    DrawEditorCursor(CursorGraphic,cursor_x-((animation&127)>>5),cursor_y,0,0,0,0,0,0,0,0);
    HandleNameEditorButtons(context);
}
asm(".global InputState\n.set InputState,0x03000000\n.global RowWidths\n.set RowWidths,0x083a8320\n.global CursorGraphic\n.set CursorGraphic,0x0851ba52\n.global AcknowledgeInput\n.thumb_set AcknowledgeInput,0x080023d1\n.global PlayEditorAction\n.thumb_set PlayEditorAction,0x08141541\n.global DrawEditorCursor\n.thumb_set DrawEditorCursor,0x08001cf1\n.global HandleNameEditorButtons\n.thumb_set HandleNameEditorButtons,0x0812aac9\n");
