typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct NativeTextList { u8 opaque00[21]; u8 row_width; } NativeTextList;
typedef struct NativeRowWorkspace { u8 opaque00[16]; u8 *buffer; } NativeRowWorkspace;
extern NativeRowWorkspace NativeRowBufferWorkspace;
extern u8 *NativeRowTextRoot;
extern u32 GetNativeListRow(NativeTextList *,u32) asm("RetailCall_08017b9c");
extern void ClearNativeTextRow(void *,u16) asm("RetailCall_08013a88");
extern u32 ProcessNativeRowText(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
void DrawNativeListTextRow(const u8 *,NativeTextList *,u32,u32) asm("SceneTaskDependency_000535E8");
void DrawNativeListTextRow(const u8 *encoded_text,NativeTextList *list,
                         u32 row_input,u32 style_input)
{
    register const u8 *content asm("r8") = encoded_text;
    register NativeTextList *incoming_list asm("r1") = list;
    register u32 incoming_row asm("r2") = row_input;
    register u32 incoming_style asm("r3") = style_input;
    register u32 row_work asm("r1");
    register u32 style_work asm("r5");
    NativeTextList *active_list;
    u32 style;
    u32 physical_row;
    u8 *buffer;
    asm("" : "+r"(content), "+r"(incoming_list),
             "+r"(incoming_row), "+r"(incoming_style));
    active_list = incoming_list;
    row_work = incoming_row;
    style_work = incoming_style;
    asm("" : "+r"(row_work), "+r"(style_work));
    style = (u8)style_work;
    physical_row = GetNativeListRow(active_list,(s8)row_work);
    buffer = NativeRowBufferWorkspace.buffer + ((u32)(u16)physical_row << 5);
    ClearNativeTextRow(buffer,2*active_list->row_width);
    ProcessNativeRowText(NativeRowTextRoot+6752,(u32)buffer,content,style,1);
}
__asm__(".global NativeRowBufferWorkspace\n.set NativeRowBufferWorkspace,0x030008B0\n"
        ".global NativeRowTextRoot\n.set NativeRowTextRoot,0x0200F428\n"
        ".global RetailCall_08017b9c\n.thumb_set RetailCall_08017b9c,0x08017b9d\n"
        ".global RetailCall_08013a88\n.thumb_set RetailCall_08013a88,0x08013a89\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n");
