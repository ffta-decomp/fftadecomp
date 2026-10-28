typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u8 gDisplayControl[];
extern unsigned ResolveMenuRowTile(void *,int);
extern void ClearMenuRow(void *,u32);
extern unsigned ResolveMenuSelection(void *,int);
extern void *ResolveRowCaption(void *,int);
extern void *PrepareRowBuffer(void *,void *,u32);
extern void DrawText(void *,void *,const void *,u32,u32);
void DrawSelectedMenuRow(u8 *menu,s8 row)
{
 u8 *panel=menu+72;
 u32 disabled=0;
 u32 raw_tile=ResolveMenuRowTile(panel,row);
 register u8 *display asm("r1")=gDisplayControl;
 register u8 *buffer asm("r6");
 register u32 byte_offset asm("r0");
 u16 selected_id;
 void *caption;
 asm("" : "+r" (display));
 byte_offset=32*(u32)(u16)raw_tile;
 display=*(u8 **)(display+16);
 asm("" : "+r" (display), "+r" (byte_offset));
 buffer=display+byte_offset;
 asm("" : "+r" (buffer));
 ClearMenuRow(buffer,2*(u32)panel[21]);
 selected_id=ResolveMenuSelection(panel,row);
 if((*(s8 **)(menu+144))[selected_id]<=0) disabled=1;
 caption=ResolveRowCaption(menu,(s16)selected_id);
 buffer=PrepareRowBuffer(menu,buffer,selected_id);
 asm("" : "+r" (buffer));
 DrawText(*(u8 **)menu+20,buffer,caption,disabled,1);
}
asm(".global gDisplayControl\n.set gDisplayControl,0x030008b0\n.global ResolveMenuRowTile\n.thumb_set ResolveMenuRowTile,0x08017b9d\n.global ClearMenuRow\n.thumb_set ClearMenuRow,0x08013a89\n.global ResolveMenuSelection\n.thumb_set ResolveMenuSelection,0x08017b69\n.global ResolveRowCaption\n.thumb_set ResolveRowCaption,0x0805064d\n.global PrepareRowBuffer\n.thumb_set PrepareRowBuffer,0x08050735\n.global DrawText\n.thumb_set DrawText,0x08015111");
