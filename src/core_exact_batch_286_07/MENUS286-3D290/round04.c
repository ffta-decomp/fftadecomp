typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gPanelContext asm("PanelContext");
extern const u8 *const gTextEntries[] asm("TextEntries");
extern const u8 *const gDefaultText asm("DefaultText");
extern void DrawText(void *,void *,const u8 *,u32,u32) asm("RetailCall_08015110");
extern u16 *GridPointer(u32,u32,u32,u32) asm("RetailCall_0808b8e4");
extern void ClearRows(u32,u16 *,u16,u16) asm("RetailCall_0808b858");
extern void FillRows(u32,u16 *,u16,u16,u16) asm("RetailCall_0808b7c0");
void ChoosePanelText(void) asm("CoreRegion_0003D290");
void ChoosePanelText(void) {
 u8 *data=*(u8 **)(gPanelContext+4);
 register const u8 *const *entry asm("r0");
 if(data[29]) {
  register const u8 *const *table asm("r1")=gTextEntries;
  register u32 ordinal asm("r0");
  asm("" : "+r"(table));
  ordinal=data[29]+717;
  asm("" : "+r"(ordinal));
  ordinal<<=2;
  asm("" : "+r"(ordinal));
  ordinal+=(u32)table;
  entry=(const u8 *const *)ordinal;
 } else entry=&gDefaultText;
 asm("" : "+r"(entry));
 {
  register const u8 *text asm("r3")=*entry;
  asm("" : "+r"(text));
  DrawText(gPanelContext+3148,(void *)0x060099e0,text,0,1);
 }
 ClearRows(4,GridPointer(4,1,1,2),0,20);
 FillRows(4,GridPointer(4,1,1,2),203,16,0xc000);
}
asm(".global PanelContext\n.set PanelContext,0x03002810\n.global TextEntries\n.set TextEntries,0x08526680\n.global DefaultText\n.set DefaultText,0x085668b0\n.global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n.global RetailCall_0808b8e4\n.thumb_set RetailCall_0808b8e4,0x0808b8e5\n.global RetailCall_0808b858\n.thumb_set RetailCall_0808b858,0x0808b859\n.global RetailCall_0808b7c0\n.thumb_set RetailCall_0808b7c0,0x0808b7c1\n");
