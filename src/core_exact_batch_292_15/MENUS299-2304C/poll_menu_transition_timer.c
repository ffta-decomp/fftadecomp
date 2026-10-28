typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TransitionEvent {u8 unknown0[8];u8 active;};
struct TransitionGroup {u8 unknown0[12];struct TransitionEvent *event;};
struct TransitionTimer {u8 unknown0[2];u8 mode;u8 unknown3[285];u16 active,duration;};
extern struct TransitionGroup gTransitionGroup;
extern struct TransitionTimer gTransitionTimer;
extern u8 ReadMenuMode(u16);
extern void UpdateMenuTransition(void);
extern void TriggerMenuTransition(void);
void PollMenuTransitionTimer(void)
{
 u32 mode=ReadMenuMode(13);
 if(mode==1) {
  UpdateMenuTransition();
  if(gTransitionGroup.event->active) {
   if(gTransitionTimer.active || (gTransitionTimer.duration>60 && gTransitionTimer.mode!=3)) {
    TriggerMenuTransition();
    gTransitionTimer.active=mode;
    gTransitionTimer.duration=300;
   }
  }
 }
}
__asm__(".global CoreGlobal36_0002304C\n.thumb_set CoreGlobal36_0002304C, PollMenuTransitionTimer\n.global ReadMenuMode\n.thumb_set ReadMenuMode,0x080c95a9\n.global UpdateMenuTransition\n.thumb_set UpdateMenuTransition,0x080c72b1\n.global TriggerMenuTransition\n.thumb_set TriggerMenuTransition,0x08004c41\n.global gTransitionGroup\n.set gTransitionGroup,0x03002710\n.global gTransitionTimer\n.set gTransitionTimer,0x030028a0\n");
