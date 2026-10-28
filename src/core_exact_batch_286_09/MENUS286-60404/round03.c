typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gPanelOwner asm("PanelOwner");
extern u32 IsReady(u32) asm("RetailCall_080099a4");
extern void InitializePanel(void *) asm("RetailCall_0806025c");
extern void *StartChild(void *,u32) asm("RetailCall_0805f670");
u32 InitializeReadyPanel(u8 *object) asm("CoreRegion30_00060404");
u32 InitializeReadyPanel(u8 *object) {
 if((u8)IsReady(object[7])) {
  InitializePanel(object);
  if(object[0]==4) {
   register u8 *root asm("r2")=gPanelOwner;
   const u16 *counts=(const u16 *)(root+312);
   register u32 offset asm("r0");
   register u8 *itemAddress asm("r2");
   offset=(counts[0]+counts[1])*4;
   asm("" : "+r"(offset), "+r"(root));
   itemAddress=root+32;
   itemAddress+=offset;
   asm("" : "+r"(itemAddress));
   *(void **)(object+12)=StartChild(*(void **)itemAddress,4);
  }
  return 1;
 }
 return 0;
}
asm(".global PanelOwner\n.set PanelOwner,0x0200f44c\n.global RetailCall_080099a4\n.thumb_set RetailCall_080099a4,0x080099a5\n.global RetailCall_0806025c\n.thumb_set RetailCall_0806025c,0x0806025d\n.global RetailCall_0805f670\n.thumb_set RetailCall_0805f670,0x0805f671\n");
