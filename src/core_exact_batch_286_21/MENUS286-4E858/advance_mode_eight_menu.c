typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct MenuControl { u16 state; u8 unknown[18]; u16 mode; };
extern void *gMenuOwner;
extern void InitializeModeEight(void *);
extern u8 WaitForMenuOpening(void *);
extern u8 MenuReadyForInput(void *);
extern u8 ProcessModeEightInput(void *);
extern u8 ReleaseFinishedMenuResources(void *);
extern void ResetMenuResourceRequest(void *);
extern void BeginMenuClosing(void *);
extern void UpdateMenuMarkerWidgets(void *);
u32 AdvanceModeEightMenu(void *task, struct MenuControl *control, u8 *menu)
{
 switch(control->state) {
 case 0: menu[8]=control->mode; *(void **)menu=gMenuOwner; break;
 case 1: break;
 case 0x100: InitializeModeEight(menu); control->state=0x101; break;
 case 0x101:
  if(WaitForMenuOpening(menu)) {
   if(MenuReadyForInput(menu)) control->state=0x105;
   else control->state=0x103;
  } break;
 case 0x103:
  if(ProcessModeEightInput(menu)) {
   if(*(s16 *)(menu+6)==-3) { *(u16 *)(menu+6)=0; control->state=0x106; }
   else control->state=0x105;
  } break;
 case 0x106: ResetMenuResourceRequest(menu); control->state=0x103; break;
 case 0x105:
  if(*(u16 *)(menu+4)&128) { *(u16 *)(menu+4)&=0xff7f; control->state=3; }
  else if(*(u16 *)(menu+4)&64) { *(u16 *)(menu+4)&=0xffbf; BeginMenuClosing(menu); control->state=0x102; }
  else if(*(u16 *)(menu+4)&32) { *(u16 *)(menu+4)&=0xffdf; control->state=0x103; }
  break;
 case 0x102:
  if(ReleaseFinishedMenuResources(menu)) {
   register u32 completed_selection asm("r0")=0xfffe;
   asm("" : "+r" (completed_selection));
   *(u16 *)(menu+6)=completed_selection; control->state=0x105;
  } break;
 }
 UpdateMenuMarkerWidgets(menu);
 return 0;
}
asm(".global gMenuOwner\n.set gMenuOwner,0x0201f548\n.global InitializeModeEight\n.thumb_set InitializeModeEight,0x0804f5bd\n.global WaitForMenuOpening\n.thumb_set WaitForMenuOpening,0x0804ef69\n.global MenuReadyForInput\n.thumb_set MenuReadyForInput,0x08050e15\n.global ProcessModeEightInput\n.thumb_set ProcessModeEightInput,0x0804f745\n.global ReleaseFinishedMenuResources\n.thumb_set ReleaseFinishedMenuResources,0x0804ef91\n.global ResetMenuResourceRequest\n.thumb_set ResetMenuResourceRequest,0x08050efd\n.global BeginMenuClosing\n.thumb_set BeginMenuClosing,0x08050de9\n.global UpdateMenuMarkerWidgets\n.thumb_set UpdateMenuMarkerWidgets,0x0804f8a5");
