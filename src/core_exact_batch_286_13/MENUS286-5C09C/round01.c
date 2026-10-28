typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u8 prefix[17];s8 index;} IndexView;
extern u8 *gMenuContext asm("MenuContext");
extern u32 GetCount(void *) asm("RetailCall_08017b50");
extern void PaintRow(void *,int,u32,u32,u32) asm("RetailCall_0802acd4");
void RefreshSelectedMenuRowStyle(void) asm("CoreClosure31_0005C09C");
void RefreshSelectedMenuRowStyle(void) {
 u8 *context=gMenuContext;
 u8 *data=context+0xd20;
 IndexView *view=(IndexView *)(context+0xd40);
 u8 row=0;
 int selected=view->index;
 while(row<(u16)GetCount(data)) {
  if(row==selected)PaintRow(data,row,11,2,(u8)(data[21]-2));
  else PaintRow(data,(s8)row,255,2,(u8)(data[21]-2));
  row++;
 }
}
asm(".global MenuContext\n.set MenuContext,0x0200f428\n.global RetailCall_08017b50\n.thumb_set RetailCall_08017b50,0x08017b51\n.global RetailCall_0802acd4\n.thumb_set RetailCall_0802acd4,0x0802acd5\n");
