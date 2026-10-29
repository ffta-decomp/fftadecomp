typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct DialogResource { u8 unknown00[20]; const void *data; };
struct MessageDialog {
    struct DialogResource *resource;
    void *second_resource;
    u8 phase, next_phase, profile, unknown0b;
    u16 flags;
    u8 column, row, width, row_count;
    u16 parameter;
    u8 unknown14[6];
    u8 stride;
    u8 unknown1b[15];
    u8 reset_count;
    u8 unknown2b[725];
    u8 *text_origin, *current_row, *cursor;
    u8 command_prefix[2];
    u8 expanded_text[510];
    u8 scratch[0];
};
#define OFF(t,f) ((u32)&((t *)0)->f)
typedef char CheckOrigin[OFF(struct MessageDialog,text_origin)==768?1:-1];
typedef char CheckCursor[OFF(struct MessageDialog,cursor)==776?1:-1];
typedef char CheckPrefix[OFF(struct MessageDialog,command_prefix)==780?1:-1];
typedef char CheckScratch[OFF(struct MessageDialog,scratch)==1292?1:-1];
#define CURRENT (*(struct MessageDialog **)0x0200918c)
extern const u8 *ConfigureMessageOption(struct MessageDialog *,u8,u16 *);
extern u16 ExpandIndexedText(void *,const u8 *,void *,u16,u8 *,u8 *);
extern u32 UsesExtendedStreamProfile(u8);
extern u32 IsAlternateStreamProfile(u8);
extern u32 IsStreamProfileNine(u8);
extern void ClearTextCells(void *,u32);
extern void CopyDialogRows(const void *,u8,u8,u8,u32,u32,u16,u32);
__asm__(".global ConfigureMessageOption\n.thumb_set ConfigureMessageOption,0x080182cd\n"
        ".global ExpandIndexedText\n.thumb_set ExpandIndexedText,0x08013e9d\n"
        ".global UsesExtendedStreamProfile\n.thumb_set UsesExtendedStreamProfile,0x0801843d\n"
        ".global IsAlternateStreamProfile\n.thumb_set IsAlternateStreamProfile,0x080184d1\n"
        ".global IsStreamProfileNine\n.thumb_set IsStreamProfileNine,0x08018471\n"
        ".global ClearTextCells\n.thumb_set ClearTextCells,0x08013a89\n"
        ".global CopyDialogRows\n.thumb_set CopyDialogRows,0x08015859");
void PresentDialogMessage(u8,u16) __asm__("CoreFrontier_00011B30");
void PresentDialogMessage(u8 kind,u16 incoming_message)
{
    u16 message=incoming_message;
    struct MessageDialog *initial_context=CURRENT;
    struct MessageDialog *expansion_context;
    struct MessageDialog *publication_context;
    register u32 clear_stride __asm__("r8")=(u32)initial_context->stride*2;
    const u8 *bank;
    u32 vertical_margin;
    u32 margin_mask;
    register u32 margin_working __asm__("r2");
    /* Original cached width remains in R8 through the last row clear. */
    __asm__("" : "+r"(clear_stride));
    bank=ConfigureMessageOption(initial_context,kind,&message);
    CURRENT->command_prefix[0]=64;
    CURRENT->command_prefix[1]=99;
    expansion_context=CURRENT;
    ExpandIndexedText(expansion_context->expanded_text,bank,expansion_context->scratch,message,0,0);
    publication_context=CURRENT;
    /* Actual short snapshot is consumed before the first profile helper. */
    __asm__("" : "+r"(publication_context));
    publication_context->cursor=publication_context->command_prefix;
    margin_mask=publication_context->flags&192;
    margin_working=1;
    if(margin_mask) margin_working=2;
    vertical_margin=margin_working;
    /* The joined margin is saved across helpers until the actual row input. */
    __asm__("" : "+r"(vertical_margin) : "r"(margin_working));
    if((u8)UsesExtendedStreamProfile(publication_context->profile) ||
       (u8)IsAlternateStreamProfile(CURRENT->profile)) {
        CURRENT->phase=4;
    } else if((u8)IsStreamProfileNine(CURRENT->profile)) {
        s32 i;
        struct MessageDialog *copy_context;
        register const void *copy_source __asm__("r0");
        register u32 copy_column __asm__("r1");
        register u32 row_working __asm__("r2");
        for(i=1;i<(CURRENT->row_count>>1);i++) {
            struct MessageDialog *row_context=CURRENT;
            ClearTextCells(row_context->text_origin+((i*row_context->stride)<<6),clear_stride);
        }
        copy_context=CURRENT;
        copy_source=copy_context->resource->data;
        copy_column=(u8)(copy_context->column+1);
        row_working=copy_context->row;
        /* Own the original two-byte ADD operand order; no memory effect. */
        __asm__(".Lw4_11b30_row_add_begin:\n\tadd %0,%1,%0\n.Lw4_11b30_row_add_end:"
                : "+l"(row_working)
                : "l"(vertical_margin), "r"(copy_source), "r"(copy_column) : "cc");
        CopyDialogRows(copy_source,(u8)copy_column,
                       (u8)row_working,copy_context->stride,
                       copy_context->row_count>>1,32,copy_context->parameter,12);
    }
    CURRENT->reset_count=0;
}
