typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct NativeRowWorkspace {u8 opaque00[16];u8 *buffer;} NativeRowWorkspace;
extern NativeRowWorkspace NativeRowBufferWorkspace;
extern const u8 *NativeWidgetLabelPointer;
extern void ClearNativeWidgetText(void *,u16) asm("RetailCall_08013a88");
extern u32 ProcessNativeWidgetText(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
extern void DrawNativeWidgetNumber(void *,void *,u32,u32,u32) asm("RetailCall_0802979c");
extern void FillNativeWidgetRuns(void *,u16,u16,u8,u8,u16,u8) asm("RetailCall_0802ab64");
extern void CopyNativeWidgetRows(void *,u16 *,u8,u8,u8) asm("RetailCall_0802ac14");
void DrawNativeWidgetLabelAndNumber(u8 *,void *,u32) asm("CoreClosure31_00053B34");
void DrawNativeWidgetLabelAndNumber(u8 *widget,void *context,u32 number_input)
{
    u32 number=(u8)number_input;
    register NativeRowWorkspace *workspace asm("r1")=&NativeRowBufferWorkspace;
    u16 *row_index;
    u8 *row_width;
    u8 *buffer;
    asm("" : "+r"(workspace));
    row_index=(u16 *)(widget+72);
    buffer=workspace->buffer+((u32)*row_index<<5);
    row_width=widget+65;
    ClearNativeWidgetText(buffer,2*(*row_width));
    ProcessNativeWidgetText(context,(u32)buffer,NativeWidgetLabelPointer,5,1);
    buffer += 448;
    DrawNativeWidgetNumber(context,buffer,number,2,5);
    FillNativeWidgetRuns(widget+44,0,*row_index,widget[18],*row_width,widget[75],1);
    CopyNativeWidgetRows(widget,*(u16 **)(widget+56),(u8)(widget[16]+1),widget[17],widget[19]);
}
__asm__(".global NativeRowBufferWorkspace\n.set NativeRowBufferWorkspace,0x030008b0\n"
        ".global NativeWidgetLabelPointer\n.set NativeWidgetLabelPointer,0x083937f8\n"
        ".global RetailCall_08013a88\n.thumb_set RetailCall_08013a88,0x08013a89\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n"
        ".global RetailCall_0802979c\n.thumb_set RetailCall_0802979c,0x0802979d\n"
        ".global RetailCall_0802ab64\n.thumb_set RetailCall_0802ab64,0x0802ab65\n"
        ".global RetailCall_0802ac14\n.thumb_set RetailCall_0802ac14,0x0802ac15\n");
