typedef unsigned char u8;
typedef unsigned short u16;
struct MenuPanelContext {void *parent;void *opaque4;void *panels[2];};
extern struct MenuPanelContext *gMenuContext;
extern u8 *GetPanelData(void *);
extern unsigned GetPanelTaskState(void *);
extern void SetPanelTaskState(void *,unsigned);
__asm__(".global gMenuContext\n.set gMenuContext,0x0200f44c\n.global GetPanelData\n.thumb_set GetPanelData,0x08005bfd\n.global GetPanelTaskState\n.thumb_set GetPanelTaskState,0x08005bad\n.global SetPanelTaskState\n.thumb_set SetPanelTaskState,0x08005ba9");
void SetMenuPanelContinuation(u8 selector,u16 value) {
 u8 *child=0;
 void *handle=0;
 int i;
 for(i=0;i<2;++i) {
  handle=gMenuContext->panels[i];
  if(handle) {child=GetPanelData(handle);if(child[0]==selector) break;}
 }
 if(i!=2) {
  *(u16 *)(child+8)=GetPanelTaskState(handle);
  *(u16 *)(child+10)=value;
  SetPanelTaskState(handle,267);
 }
}
