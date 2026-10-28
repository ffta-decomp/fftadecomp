typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 gTransitionGroup[],gTransitionWorkspace[],gTransitionNode[],gTransitionMode;
extern void ResetMenuTransition(void);
extern void PrepareMenuTransition(void);
extern void InitializeTransitionGroup(void *,void *,void *,u32);
extern void SetTransitionCallback(void *,u32,void *);
extern void TransitionPrimaryCallback(void);
extern void TransitionSecondaryCallback(void);
extern void FillTransitionTiles(const void *,void *,u32);
extern void StartTransitionDisplay(void);
extern void PollMenuTransition(void);
extern void AdvanceTransitionGroup(void *,u32);
extern u32 AdvanceMenuController(void);
extern u8 CompleteTransitionCleanup(void);
void AdvanceMenuTransition(void *task,u8 *state)
{
 switch(*state) {
 case 0:
  ResetMenuTransition();
  *state=1;
  break;
 case 1: {
  u16 background_zero;
  u16 text_zero;
  u32 clear_value;
  register u8 *mode_address __asm__("r1");
  PrepareMenuTransition();
  InitializeTransitionGroup(gTransitionGroup,gTransitionWorkspace,gTransitionNode,9);
  SetTransitionCallback(gTransitionGroup,0,TransitionPrimaryCallback);
  SetTransitionCallback(gTransitionGroup,1,TransitionSecondaryCallback);
  mode_address=&gTransitionMode;
  __asm__("" : "+r"(mode_address));
  clear_value=0;
  *mode_address=9;
  background_zero=clear_value;
  FillTransitionTiles(&background_zero,(void *)0x0600e000,0x01000800);
  text_zero=clear_value;
  FillTransitionTiles(&text_zero,(void *)0x06005000,0x01000800);
  StartTransitionDisplay();
  *state=2;
  break;
 }
 case 2:
  PollMenuTransition();
  AdvanceTransitionGroup(gTransitionGroup,9);
  *state=AdvanceMenuController();
  break;
 case 255:break;
 case 254:
  if(CompleteTransitionCleanup())*state=255;
  break;
 }
}
__asm__(".global CoreGlobal36_00023F00\n.thumb_set CoreGlobal36_00023F00, AdvanceMenuTransition\n.global ResetMenuTransition\n.thumb_set ResetMenuTransition,0x08023fd1\n.global PrepareMenuTransition\n.thumb_set PrepareMenuTransition,0x080227e9\n.global InitializeTransitionGroup\n.thumb_set InitializeTransitionGroup,0x08006a7d\n.global SetTransitionCallback\n.thumb_set SetTransitionCallback,0x08006add\n.global TransitionPrimaryCallback\n.thumb_set TransitionPrimaryCallback,0x080231d9\n.global TransitionSecondaryCallback\n.thumb_set TransitionSecondaryCallback,0x08121909\n.global FillTransitionTiles\n.thumb_set FillTransitionTiles,0x0814186d\n.global StartTransitionDisplay\n.thumb_set StartTransitionDisplay,0x0808f74d\n.global PollMenuTransition\n.thumb_set PollMenuTransition,0x0802304d\n.global AdvanceTransitionGroup\n.thumb_set AdvanceTransitionGroup,0x080069f5\n.global AdvanceMenuController\n.thumb_set AdvanceMenuController,0x080241b5\n.global CompleteTransitionCleanup\n.thumb_set CompleteTransitionCleanup,0x08024109\n.global gTransitionGroup\n.set gTransitionGroup,0x03002710\n.global gTransitionWorkspace\n.set gTransitionWorkspace,0x03002820\n.global gTransitionNode\n.set gTransitionNode,0x03000e40\n.global gTransitionMode\n.set gTransitionMode,0x0200f390\n");
