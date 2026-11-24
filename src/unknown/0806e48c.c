typedef unsigned char u8;
typedef signed short s16;
extern u8 *gMenuBoundaryContext;
extern unsigned QueryMenuBoundaryMode(void *);
extern void BindMenuTransition(void *,void *,void (*)(void),unsigned);
extern void MenuTransitionCallback(void);
extern void UpdateMenuPastLastRow(void *);
__asm__(".global gMenuBoundaryContext\n.set gMenuBoundaryContext,0x0200f428\n.global QueryMenuBoundaryMode\n.thumb_set QueryMenuBoundaryMode,0x0806fe15\n.global BindMenuTransition\n.thumb_set BindMenuTransition,0x08017db5\n.global MenuTransitionCallback\n.thumb_set MenuTransitionCallback,0x08017f05\n.global UpdateMenuPastLastRow\n.thumb_set UpdateMenuPastLastRow,0x0806e4e1");
void HandleMenuPastLastRow(u8 *context) {
 if(context[67]-1 < *(s16 *)(context+68)) {
  if((u8)QueryMenuBoundaryMode(gMenuBoundaryContext+0x1a88)==4) {
   BindMenuTransition(context+96,context+44,MenuTransitionCallback,0);
   UpdateMenuPastLastRow(context);
  }
 }
}
