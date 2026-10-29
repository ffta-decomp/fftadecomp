typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct DialogCommandContext {
    u8 *destination;
    u8 unknown04[4];
    u8 phase, next_phase, profile, unknown0b;
    u16 text_flags;
    s8 column, row;
    u8 selector, row_count;
    u16 text_parameter, return_offset, scale, delay;
    u8 stride, parameter, pending;
    u8 unknown1d[3];
    u16 timer;
    u8 unknown22[4];
    u8 control26, unknown27, control28, unknown29, reset_count;
    u8 unknown2b[9];
    u16 position_x, position_y;
    u8 position_state, unknown39;
    u16 flags;
    u8 unknown3c[4];
    u8 row_index, header_low, header_high_empty, metric;
    u8 unknown44[44];
    u8 text_object[656];
    u8 *text_origin, *current_row, *cursor;
    u8 unknown30c[1024];
    u8 buffer[64];
};
#define OFF(t,f) ((u32)&((t *)0)->f)
typedef char CheckTimer[(OFF(struct DialogCommandContext,timer)==32)?1:-1];
typedef char CheckText[(OFF(struct DialogCommandContext,text_object)==112)?1:-1];
typedef char CheckRow[(OFF(struct DialogCommandContext,current_row)==772)?1:-1];
typedef char CheckCursor[(OFF(struct DialogCommandContext,cursor)==776)?1:-1];
typedef char CheckBuffer[(OFF(struct DialogCommandContext,buffer)==0x70c)?1:-1];
struct RuntimeDialogFields {
    u8 unknown0000[0x2174];
    u16 dialog_parameter;
    u8 unknown2176[0xe4a];
    u8 mode;
};
extern struct RuntimeDialogFields gRuntimeDialogFields;
extern u8 gDialogSharedFields[];
extern const s8 gDialogRowFieldValues[];
extern void (* const gDialogBufferInitializer)(void *,u32);
#define CURRENT (*current_dialog_cell)
#define LIVE_DIALOG (*(struct DialogCommandContext **)0x0200918c)
#define TEXT (CURRENT->text_object)
extern void InitializeTextContext(void *,const void *);
extern void InitializeTextContextWithByteFields(void *,const void *,u32,u32);
extern void AdvanceTextContextPointerByStoredStride(void *,u32);
extern void AdjustTextContextOffset(void *,s16);
extern void SetTextContextColorStyle(void *,u8);
extern void ClearManagedSelectionTextCells(void *,u16);
extern u32 AdjustDialogSelector(u32,u32);
extern u32 ReadTextMetricForPrefix(const u8 *);
extern u8 *FindTextMarkerByOpcode(const u8 *,u32);
/* The original caller publishes a fifth word even though the selected callee
 * does not consume it. Keep that actual outgoing word in this caller ABI. */
extern u32 RenderDialogRecord(void *,const void *,const u8 *,u32,u32);
extern void ConfigureDialogText(u32,void *,void *,u32,u32,u32,u32,u32);
extern void ExpandDialogTableToken(void *,u32);
extern u32 UsesExtendedStreamProfile(u8);
extern u32 IsStreamProfileNine(u8);
extern u32 UsesAlternateStreamSurface(u8);
extern u32 IsAlternateStreamProfile(u8);
extern u32 DispatchTextCallback(void *,u32);
extern void PlayDialogCue(u32);
__asm__(
 ".global InitializeTextContext\n.thumb_set InitializeTextContext,0x08013529\n"
 ".global InitializeTextContextWithByteFields\n.thumb_set InitializeTextContextWithByteFields,0x08013571\n"
 ".global AdvanceTextContextPointerByStoredStride\n.thumb_set AdvanceTextContextPointerByStoredStride,0x080135b9\n"
 ".global AdjustTextContextOffset\n.thumb_set AdjustTextContextOffset,0x08013729\n"
 ".global SetTextContextColorStyle\n.thumb_set SetTextContextColorStyle,0x080137c1\n"
 ".global ClearManagedSelectionTextCells\n.thumb_set ClearManagedSelectionTextCells,0x08013a89\n"
 ".global AdjustDialogSelector\n.thumb_set AdjustDialogSelector,0x08013aad\n"
 ".global ReadTextMetricForPrefix\n.thumb_set ReadTextMetricForPrefix,0x08014779\n"
 ".global FindTextMarkerByOpcode\n.thumb_set FindTextMarkerByOpcode,0x08014f11\n"
 ".global RenderDialogRecord\n.thumb_set RenderDialogRecord,0x080153fd\n"
 ".global ConfigureDialogText\n.thumb_set ConfigureDialogText,0x08016071\n"
 ".global ExpandDialogTableToken\n.thumb_set ExpandDialogTableToken,0x0801624d\n"
 ".global UsesExtendedStreamProfile\n.thumb_set UsesExtendedStreamProfile,0x0801843d\n"
 ".global IsStreamProfileNine\n.thumb_set IsStreamProfileNine,0x08018471\n"
 ".global UsesAlternateStreamSurface\n.thumb_set UsesAlternateStreamSurface,0x08018485\n"
 ".global IsAlternateStreamProfile\n.thumb_set IsAlternateStreamProfile,0x080184d1\n"
 ".global DispatchTextCallback\n.thumb_set DispatchTextCallback,0x08018ced\n"
 ".global PlayDialogCue\n.thumb_set PlayDialogCue,0x08141541\n"
 ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
 ".global gRuntimeDialogFields\n.set gRuntimeDialogFields,0x02000000\n"
 ".global gDialogSharedFields\n.set gDialogSharedFields,0x020020d0\n"
 ".global gDialogRowFieldValues\n.set gDialogRowFieldValues,0x0836d630\n"
 ".global gDialogBufferInitializer\n.set gDialogBufferInitializer,0x0836d4b8");
u32 DispatchActiveDialogCommand(void) __asm__("Frame54_000120F0");
u32 DispatchActiveDialogCommand(void)
{
    u32 operation=(u32)LIVE_DIALOG->cursor[1]-33;
    struct DialogCommandContext **current_dialog_cell=(struct DialogCommandContext **)0x0200918c;
    asm volatile("" : "+r"(current_dialog_cell) : "r"(operation));
    switch (operation) {
    case 110-33: {
        struct DialogCommandContext *context=LIVE_DIALOG;
        struct DialogCommandContext *delay_context;
        context->current_row += (u32)context->stride << 6;
        context->row_index++;
        if ((u8)UsesExtendedStreamProfile(LIVE_DIALOG->profile))
            AdvanceTextContextPointerByStoredStride(LIVE_DIALOG->text_object,(u32)gDialogRowFieldValues[LIVE_DIALOG->row_index]);
        else InitializeTextContext(LIVE_DIALOG->text_object,LIVE_DIALOG->current_row);
        if ((u8)UsesAlternateStreamSurface(LIVE_DIALOG->profile)) SetTextContextColorStyle(LIVE_DIALOG->text_object,5);
        delay_context=LIVE_DIALOG;
        delay_context->delay += 256;
        delay_context->cursor += 2;
        break;
    }
    case 115-33:
        AdjustTextContextOffset(TEXT,6);
        CURRENT->cursor += 2;
        break;
    case 99-33: {
        s32 i;
        struct DialogCommandContext *context;
        struct DialogCommandContext *reset_context;
        u8 *old_cursor;
        u8 *found_cursor;
        LIVE_DIALOG->reset_count++;
        if (!(u8)IsStreamProfileNine(LIVE_DIALOG->profile)) {
            for (i=0;i<(LIVE_DIALOG->row_count>>1);i++)
                ClearManagedSelectionTextCells(LIVE_DIALOG->text_origin+((i*LIVE_DIALOG->stride)<<6),LIVE_DIALOG->stride*2);
        }
        reset_context=LIVE_DIALOG;
        reset_context->current_row=reset_context->text_origin;
        reset_context->row_index=0;
        if ((u8)UsesExtendedStreamProfile(LIVE_DIALOG->profile))
            InitializeTextContextWithByteFields(LIVE_DIALOG->text_object,LIVE_DIALOG->current_row,LIVE_DIALOG->stride,1);
        else InitializeTextContext(LIVE_DIALOG->text_object,LIVE_DIALOG->current_row);
        if ((u8)UsesAlternateStreamSurface(LIVE_DIALOG->profile)) SetTextContextColorStyle(LIVE_DIALOG->text_object,5);
        context=LIVE_DIALOG;
        old_cursor=context->cursor;
        context->cursor=old_cursor+2;
        if (old_cursor[2] && (u8)IsStreamProfileNine(LIVE_DIALOG->profile)) {
            struct DialogCommandContext *advance_context=LIVE_DIALOG;
            advance_context->current_row += (u32)advance_context->stride<<6;
            advance_context->row_index++;
            InitializeTextContext(LIVE_DIALOG->text_object,LIVE_DIALOG->current_row);
            found_cursor=FindTextMarkerByOpcode(LIVE_DIALOG->cursor,110);
            LIVE_DIALOG->cursor=found_cursor+2;
        }
        break;
    }
    case 120-33: {
        struct DialogCommandContext *context;
        CURRENT->control28=1;
        context=CURRENT;
        context->scale=4096;
        context->delay+=4096;
        context->cursor+=2;
        break;
    }
    case 117-33: {
        struct DialogCommandContext *context=CURRENT;
        context->scale=128;
        context->delay=256;
        context->cursor+=2;
        break;
    }
    case 97-33:
    case 112-33: {
        struct DialogCommandContext *context=CURRENT;
        context->delay=128;
        if ((gRuntimeDialogFields.mode&24)==8) context->delay=4096;
        CURRENT->next_phase=5;
        if (CURRENT->pending) {
            struct DialogCommandContext *pending_context;
            CURRENT->parameter=gRuntimeDialogFields.dialog_parameter;
            pending_context=CURRENT;
            pending_context->timer=0;
            pending_context->phase=7;
        } else {
            if ((u8)IsAlternateStreamProfile(CURRENT->profile)) CURRENT->parameter=10;
            context=CURRENT;
            if (context->cursor[1]==97) context->flags&=0xfffe;
            else context->flags|=1;
            {
                struct DialogCommandContext **parameter_cell=(struct DialogCommandContext **)0x0200918c;
                if ((*parameter_cell)->flags&1) {
                    u8 selector=(u8)AdjustDialogSelector((*parameter_cell)->selector,(*parameter_cell)->text_flags);
                    s32 preceding_rows;
                    struct DialogCommandContext *projection_context=*parameter_cell;
                    projection_context->position_x=(u32)selector*4+projection_context->column*8;
                    preceding_rows=(s32)projection_context->row_count-1;
                    projection_context->position_y=(projection_context->row+preceding_rows)*8;
                    projection_context->position_state=0;
                }
                gDialogSharedFields[182]=0;
                (*parameter_cell)->phase=6;
                current_dialog_cell=parameter_cell;
            }
        }
        CURRENT->cursor+=2;
        return 1;
    }
    case 119-33:
        CURRENT->control26=1;
        CURRENT->next_phase=5;
        CURRENT->phase=8;
        CURRENT->cursor+=2;
        return 1;
    case 107-33: {
        struct DialogCommandContext *context;
        CURRENT->pending=1;
        context=CURRENT;
        context->timer=0;
        context->delay+=256;
        context->cursor+=2;
        break;
    }
    case 121-33: {
        s16 metric=(s16)ReadTextMetricForPrefix(CURRENT->cursor+2);
        struct DialogCommandContext *context;
        AdjustTextContextOffset(TEXT,(s16)(CURRENT->stride*8-metric));
        context=CURRENT;
        context->delay+=256;
        context->cursor+=2;
        break;
    }
    case 83-33: {
        u8 style;
        u16 consumed;
        u8 header;
        struct DialogCommandContext *context;
        struct DialogCommandContext *header_context;
        struct DialogCommandContext *flags_context;
        LIVE_DIALOG->parameter=10;
        style=(u8)UsesAlternateStreamSurface(LIVE_DIALOG->profile)?5:0;
        consumed=(u16)RenderDialogRecord(LIVE_DIALOG->text_object,*(void **)LIVE_DIALOG->text_object,LIVE_DIALOG->cursor,style,LIVE_DIALOG->stride);
        LIVE_DIALOG->header_high_empty=0;
        header_context=LIVE_DIALOG;
        header=header_context->cursor[2];
        if (!(header&240)) header_context->header_high_empty=1;
        LIVE_DIALOG->header_low=(header&15)!=0;
        if (!LIVE_DIALOG->header_high_empty) {
            u32 metric=ReadTextMetricForPrefix(LIVE_DIALOG->cursor+3);
            LIVE_DIALOG->metric=metric;
        }
        flags_context=LIVE_DIALOG;
        flags_context->flags|=1;
        flags_context->position_state=0;
        context=LIVE_DIALOG;
        context->position_x=(context->column+1)*8+3;
        {
            s32 row=context->row;
            s32 row_step=2*(s32)context->row_index+1;
            context->position_y=(row+row_step)*8+4;
        }
        if ((u8)UsesExtendedStreamProfile(context->profile)) {
            u16 old_position;
            context=LIVE_DIALOG;
            old_position=context->position_x;
            context->position_x=old_position+16;
            if ((context->flags&256) && !(context->text_flags&16)) context->position_x=old_position+56;
            LIVE_DIALOG->position_y+=gDialogRowFieldValues[LIVE_DIALOG->row_index];
        }
        if (!(LIVE_DIALOG->text_flags&0xc20)) LIVE_DIALOG->position_y+=8;
        LIVE_DIALOG->next_phase=5;
        LIVE_DIALOG->phase=9;
        LIVE_DIALOG->cursor+=consumed;
        return 1;
    }
    case 108-33: {
        u8 style=LIVE_DIALOG->cursor[2];
        struct DialogCommandContext *context;
        if ((u8)UsesExtendedStreamProfile(LIVE_DIALOG->profile)) {
            if (!style) style=5;
            else style=0;
        }
        SetTextContextColorStyle(LIVE_DIALOG->text_object,style);
        context=LIVE_DIALOG;
        context->delay+=256;
        context->cursor+=3;
        break;
    }
    case 37-33: {
        u8 count;
        u8 *old_cursor;
        u32 biased_cursor;
        struct DialogCommandContext *context;
        gDialogBufferInitializer(CURRENT->buffer,64);
        count=(u8)DispatchTextCallback(CURRENT->buffer,CURRENT->cursor[2]);
        context=CURRENT;
        old_cursor=context->cursor;
        context->cursor=old_cursor+3;
        biased_cursor=(u32)old_cursor-777;
        context->return_offset=biased_cursor-(u32)context+count;
        context->cursor=context->buffer;
        context->delay+=256;
        break;
    }
    case 103-33: {
        struct DialogCommandContext *argument_context=CURRENT;
        struct DialogCommandContext *context;
        ConfigureDialogText(argument_context->cursor[2],argument_context->text_object,argument_context->destination,argument_context->stride,
            (u8)argument_context->column,(u8)argument_context->row,argument_context->text_parameter,argument_context->text_flags);
        context=CURRENT;
        context->delay+=256;
        context->cursor+=3;
        break;
    }
    case 116-33: {
        struct DialogCommandContext *context=CURRENT;
        context->delay=128;
        if ((gRuntimeDialogFields.mode&24)==8) context->delay=4096;
        CURRENT->parameter=CURRENT->cursor[2];
        CURRENT->next_phase=5;
        CURRENT->phase=7;
        CURRENT->cursor+=3;
        return 1;
    }
    case 114-33: {
        u8 *old_cursor;
        u32 biased_cursor;
        struct DialogCommandContext *context;
        gDialogBufferInitializer(CURRENT->buffer,64);
        ExpandDialogTableToken(CURRENT->buffer,CURRENT->cursor[2]);
        context=CURRENT;
        old_cursor=context->cursor;
        context->cursor=old_cursor+3;
        biased_cursor=(u32)old_cursor-777;
        context->return_offset=biased_cursor-(u32)context;
        context->cursor=context->buffer;
        context->delay+=256;
        break;
    }
    case 60-33:
    case 62-33: {
        struct DialogCommandContext *context=CURRENT;
        u16 offset=context->cursor[2];
        if (context->cursor[1]==60) offset=-offset;
        context->delay+=256;
        AdjustTextContextOffset(context->text_object,(s16)offset);
        CURRENT->cursor+=3;
        break;
    }
    case 33-33: {
        register u8 *cue_cursor __asm__("r1")=CURRENT->cursor;
        u8 cue;
        asm volatile("" : "+r"(cue_cursor));
        cue=cue_cursor[2];
        if (cue) PlayDialogCue(cue+147);
        CURRENT->control28=1;
        CURRENT->cursor+=3;
        break;
    }
    }
    return 0;
}
