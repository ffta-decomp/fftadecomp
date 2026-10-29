typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct DialogControlContext {
    u8 unknown_00[10];
    u8 profile;
    u8 unknown_0b[11];
    u16 scale_x;
    u16 scale_y;
    u8 row_stride;
    u8 unknown_1b;
    u8 yield_requested;
    u8 unknown_1d[3];
    u16 timer;
    u8 unknown_22[30];
    u8 row_index;
    u8 unknown_41[707];
    u8 *current_row;
    u8 *cursor;
};
#define FIELD_OFFSET(t,f) ((u32)&(((t*)0)->f))
typedef char CheckRowIndex[(FIELD_OFFSET(struct DialogControlContext,row_index)==64)?1:-1];
typedef char CheckRowPointer[(FIELD_OFFSET(struct DialogControlContext,current_row)==772)?1:-1];
typedef char CheckCursor[(FIELD_OFFSET(struct DialogControlContext,cursor)==776)?1:-1];
#define CURRENT_DIALOG (*(struct DialogControlContext **)0x0200918c)
#define DIALOG_TEXT_OBJECT ((u8 *)CURRENT_DIALOG+112)
extern void InitializeTextContext(void*,const void*);
extern void AdvanceTextContextPointerByStoredStride(void*,u32);
extern void AdjustTextContextOffset(void*,s16);
extern void SetTextContextColorStyle(void*,u8);
extern u32 UsesExtendedStreamProfile(u8);
extern u32 UsesAlternateStreamSurface(u8);
extern const s8 gDialogRowFieldValues[];
__asm__(".global InitializeTextContext\n.thumb_set InitializeTextContext,0x08013529\n"
        ".global AdvanceTextContextPointerByStoredStride\n.thumb_set AdvanceTextContextPointerByStoredStride,0x080135b9\n"
        ".global AdjustTextContextOffset\n.thumb_set AdjustTextContextOffset,0x08013729\n"
        ".global SetTextContextColorStyle\n.thumb_set SetTextContextColorStyle,0x080137c1\n"
        ".global UsesExtendedStreamProfile\n.thumb_set UsesExtendedStreamProfile,0x0801843d\n"
        ".global UsesAlternateStreamSurface\n.thumb_set UsesAlternateStreamSurface,0x08018485\n"
        ".global gDialogRowFieldValues\n.set gDialogRowFieldValues,0x0836d630");
void ProcessLeadingDialogControls(void) __asm__("Source52_00012D3C");
void ProcessLeadingDialogControls(void)
{
    while (CURRENT_DIALOG->cursor[0] == 64) {
        switch (CURRENT_DIALOG->cursor[1]) {
        case 110:
            CURRENT_DIALOG->current_row += (u32)CURRENT_DIALOG->row_stride << 6;
            CURRENT_DIALOG->row_index++;
            if ((u8)UsesExtendedStreamProfile(CURRENT_DIALOG->profile))
                AdvanceTextContextPointerByStoredStride(DIALOG_TEXT_OBJECT,
                    (u32)gDialogRowFieldValues[CURRENT_DIALOG->row_index]);
            else
                InitializeTextContext(DIALOG_TEXT_OBJECT,CURRENT_DIALOG->current_row);
            if ((u8)UsesAlternateStreamSurface(CURRENT_DIALOG->profile))
                SetTextContextColorStyle(DIALOG_TEXT_OBJECT,5);
            CURRENT_DIALOG->cursor += 2;
            break;
        case 120: {
            struct DialogControlContext *scale_context = CURRENT_DIALOG;
            scale_context->scale_x = 4096;
            scale_context->scale_y = 4096;
            scale_context->cursor += 2;
            break;
        }
        case 117: {
            struct DialogControlContext *scale_context = CURRENT_DIALOG;
            scale_context->scale_x = 128;
            scale_context->scale_y = 256;
            scale_context->cursor += 2;
            break;
        }
        case 107: {
            struct DialogControlContext *yield_context;
            CURRENT_DIALOG->yield_requested = 1;
            yield_context = CURRENT_DIALOG;
            yield_context->timer = 0;
            yield_context->cursor += 2;
            break;
        }
        case 108:
            SetTextContextColorStyle(DIALOG_TEXT_OBJECT,CURRENT_DIALOG->cursor[2]);
            CURRENT_DIALOG->cursor += 3;
            break;
        case 60:
            AdjustTextContextOffset(DIALOG_TEXT_OBJECT,-(s16)CURRENT_DIALOG->cursor[2]);
            CURRENT_DIALOG->cursor += 3;
            break;
        case 62:
            AdjustTextContextOffset(DIALOG_TEXT_OBJECT,CURRENT_DIALOG->cursor[2]);
            CURRENT_DIALOG->cursor += 3;
            break;
        case 102:
            CURRENT_DIALOG->cursor += 4;
            break;
        default:
            return;
        }
    }
}
