typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *gMenuContext asm("MenuContext");
extern void PrepareContext(void *) asm("RetailCall_0806e59c");
extern u32 ReadMode(const void *) asm("RetailCall_0806fe14");
extern void CopyGrid(void *) asm("RetailCall_0802b108");
extern void CopyRectangle(void *,const void *,u32,u32,u32,u32) asm("RetailCall_08070070");
void ComposeMenuModeLayout(void) asm("SceneTaskDependency_0006E528");
void ComposeMenuModeLayout(void) {
 u8 *context=gMenuContext;
 void *descriptor=context+0x14c0;
 PrepareContext(context);
 if((u8)ReadMode(gMenuContext+0x1a88)==4)CopyGrid(descriptor);
 else {
  CopyRectangle(descriptor,*(void **)(gMenuContext+0x1494),0,0,14,8);
  CopyRectangle(descriptor,gMenuContext+0x1ce8,14,0,10,8);
 }
}
asm(".global MenuContext\n.set MenuContext,0x0200f428\n.global RetailCall_0806e59c\n.thumb_set RetailCall_0806e59c,0x0806e59d\n.global RetailCall_0806fe14\n.thumb_set RetailCall_0806fe14,0x0806fe15\n.global RetailCall_0802b108\n.thumb_set RetailCall_0802b108,0x0802b109\n.global RetailCall_08070070\n.thumb_set RetailCall_08070070,0x08070071\n");
