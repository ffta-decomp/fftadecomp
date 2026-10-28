typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct HandoffOwner {u8 unknown00[6];u8 completed;};
struct HandoffEvent {u16 state;u8 unknown02[2];struct HandoffOwner *owner;};
struct HandoffWorkspace {struct HandoffOwner *owner;u8 unknown04[4];};
extern u8 gSceneHandoffMode;
extern u32 RequestSceneModeTransition(u32,u32);
asm(".global gSceneHandoffMode\n.set gSceneHandoffMode,0x0200f390\n.global RequestSceneModeTransition\n.thumb_set RequestSceneModeTransition,0x08022cd5");
u32 AdvanceSceneMode15Handoff(void *node,struct HandoffEvent *event,struct HandoffWorkspace *workspace) asm("CoreRegion_00126B9C");
u32 AdvanceSceneMode15Handoff(void *node,struct HandoffEvent *event,struct HandoffWorkspace *workspace)
{
 switch(event->state) {
 case 0:
  workspace->owner=event->owner;
  RequestSceneModeTransition(16,15);
  gSceneHandoffMode=15;
  break;
 case 1:
  break;
 case 256:
  if(gSceneHandoffMode==0)event->state=258;
  break;
 case 258:
  workspace->owner->completed=1;
  event->state=3;
  break;
 }
 return 0;
}
