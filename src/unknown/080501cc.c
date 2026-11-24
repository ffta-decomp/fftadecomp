typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
extern u32 Cell(void*,int,int,u32) asm("RetailCall_0804fdf4");
extern void Label(void*,int,int,u32,u32) asm("RetailCall_0804ffb8");
extern void Empty(void*,int,int) asm("RetailCall_0804ff48");
extern u32 Position(u32,u32,u32) asm("RetailCall_080161a0");
extern u32 PrepareCopy(void) asm("RetailCall_0804ca8c");
extern void Copy(u32,void*,void*,u32,u32,u32,u32) asm("RetailCall_08000bac");
extern void Page(void*,u32) asm("RetailCall_0804fd24");
void BuildPageGrid(u8 *ctx) asm("CoreRegion_000501CC");
void BuildPageGrid(u8 *ctx) {
 u8 *view=ctx+72;
 int item=18*(*(u8**)ctx)[0x560]+1;
 int y,x;
 u8 *dst,*src;u32 copy,pos;
 for(y=3;y<=11;y+=4)for(x=2;x<=22;x+=4) {
  if(item<=*(u16*)(*(u8**)ctx+4)) {
   register int drawX asm("r1")=(s16)x;
   u16 index;u8 status;
   asm("" : "+r"(drawX));
   index=item;status=(u8)Cell(ctx,drawX,(s16)y,index);
   Label(view,(s16)(x-1),(s16)(y+2),index,status);item++;
  } else Empty(view,(s16)x,(s16)y);
 }
 pos=(u16)Position(0,3,view[30]);
 dst=*(u8**)(view+12)+2*pos;
 pos=(u16)Position(0,3,32);
 src=*(u8**)(view+8)+2*pos;
 copy=PrepareCopy();
 Copy(copy,dst,src,view[21],(u16)(view[22]-3),2*view[21],64);
 pos=(u16)Position(20,1,32);
 src=*(u8**)(view+8)+2*pos;
 Page(src,(*(u8**)ctx)[0x560]+1);
}
asm(".global RetailCall_0804fdf4\n.thumb_set RetailCall_0804fdf4,0x0804fdf5\n");
asm(".global RetailCall_0804ffb8\n.thumb_set RetailCall_0804ffb8,0x0804ffb9\n");
asm(".global RetailCall_0804ff48\n.thumb_set RetailCall_0804ff48,0x0804ff49\n");
asm(".global RetailCall_080161a0\n.thumb_set RetailCall_080161a0,0x080161a1\n");
asm(".global RetailCall_0804ca8c\n.thumb_set RetailCall_0804ca8c,0x0804ca8d\n");
asm(".global RetailCall_08000bac\n.thumb_set RetailCall_08000bac,0x08000bad\n");
asm(".global RetailCall_0804fd24\n.thumb_set RetailCall_0804fd24,0x0804fd25\n");
