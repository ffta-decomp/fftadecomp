typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u8 gInputState[];
extern void ResetInputRepeat(u8*);
extern u32 QueryClampedRow(u8*,u32);
extern u32 GetDataEndRaw(u8*);
extern u32 GetVisibleCount(u8*);
extern u32 CanShiftSelection(u8*,u32);
extern void MarkMenuRow(u8*,u8);
extern void MoveMenuCursor(u8*,u8,u32,u8);
extern void MoveMenuPage(u8*,u8);
extern void RequestMenuFeedback(u32);
__asm__(".global gInputState\n.set gInputState,0x03000000");
__asm__(".global ResetInputRepeat\n.thumb_set ResetInputRepeat,0x80023d1");
__asm__(".global QueryClampedRow\n.thumb_set QueryClampedRow,0x8017b69");
__asm__(".global GetDataEndRaw\n.thumb_set GetDataEndRaw,0x8017be9");
__asm__(".global GetVisibleCount\n.thumb_set GetVisibleCount,0x8017b51");
__asm__(".global CanShiftSelection\n.thumb_set CanShiftSelection,0x8017a91");
__asm__(".global MarkMenuRow\n.thumb_set MarkMenuRow,0x8050bf1");
__asm__(".global MoveMenuCursor\n.thumb_set MoveMenuCursor,0x8050a8d");
__asm__(".global MoveMenuPage\n.thumb_set MoveMenuPage,0x8050af5");
__asm__(".global RequestMenuFeedback\n.thumb_set RequestMenuFeedback,0x8141541");

u32 HandleMenuVerticalSelection(u8 *context,u16 pressed,u16 modifier) __asm__("CoreRegion_0005093C");
u32 HandleMenuVerticalSelection(u8 *context,u16 pressed,u16 modifier)
{
    register u8 *list __asm__("r8")=context+72;
    u8 *cursor;
    int next_row;
    u32 direction;
    register u8 *call_context __asm__("r0");
    __asm__("" : "+r"(list));
    cursor=context+104;
    if (!(pressed&128))
        goto up_input;
    ResetInputRepeat(gInputState);
    if ((modifier&512) && context[8]!=1) {
        MoveMenuPage(context,128);
        goto no_change;
    }
    {
        register u32 raw_row __asm__("r1");
        u32 row_bits;
        int old_row;
        u32 selected;
        int end;
        raw_row=cursor[17];
        __asm__("" : "+r"(raw_row));
        row_bits=raw_row<<24;
        old_row=(int)row_bits>>24;
        selected=(u16)QueryClampedRow(list,old_row);
        end=(s16)GetDataEndRaw(list);
        if ((int)selected<end)
            MarkMenuRow(context,row_bits>>24);
        next_row=(s8)(old_row+1);
    }
    if (next_row>=(int)(u16)GetVisibleCount(list))
        goto down_wrap;
    if (context[10]>1)
        RequestMenuFeedback(109);
    call_context=context;
    __asm__("" : "+r"(call_context));
    direction=128;
normal_move:
    MoveMenuCursor(call_context,direction,next_row,0);
    goto no_change;
down_wrap:
    if ((u8)CanShiftSelection(list,128)==0)
        goto no_change;
    RequestMenuFeedback(109);
    call_context=context;
    __asm__("" : "+r"(call_context));
    direction=128;
    goto wrap_move;
up_input:
    if (!(pressed&64))
        goto no_change;
    ResetInputRepeat(gInputState);
    if (modifier&512) {
        MoveMenuPage(context,64);
        goto no_change;
    }
    {
        register u32 raw_row __asm__("r1");
        u32 row_bits;
        int old_row;
        raw_row=cursor[17];
        __asm__("" : "+r"(raw_row));
        row_bits=raw_row<<24;
        old_row=(int)row_bits>>24;
        if ((u16)QueryClampedRow(list,old_row)!=0)
            MarkMenuRow(context,row_bits>>24);
        next_row=(s8)(old_row-1);
    }
    if (next_row<0)
        goto up_wrap;
    if (context[10]>1)
        RequestMenuFeedback(109);
    call_context=context;
    __asm__("" : "+r"(call_context));
    direction=64;
    goto normal_move;
up_wrap:
    if ((u8)CanShiftSelection(list,64)==0)
        goto no_change;
    RequestMenuFeedback(109);
    call_context=context;
    __asm__("" : "+r"(call_context));
    direction=64;
wrap_move:
    MoveMenuCursor(call_context,direction,next_row,1);
    {
        register u32 committed_state __asm__("r0")=0xfffd;
        /* Native defines the full literal in R0 immediately before STRH. */
        __asm__("" : "+r"(committed_state));
        *(u16*)(context+6)=committed_state;
    }
    return 1;
no_change:
    return 0;
}
