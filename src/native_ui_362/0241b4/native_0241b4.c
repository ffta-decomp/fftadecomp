#include "interfaces.h"
u32 CoreGlobal36_000241B4(void)
{
 u8 primary,secondary;u16 fill_a,fill_b,fill_c,fill_d;
 struct Node *node;
 if(ReadSave(13)==1 && (gScene.flags&1024)) return 2;
 switch(gScene.state) {
 case 8:return 254;
 case 10:
  InitializeScene(ReadSave(7),0);RegisterTask(&gTasks,3,CallbackA);gScene.state=11;break;
 case 11:
  if(!PollEnter()) break;
  BeginEnter();GetChoices(&primary,&secondary);
  if(PollPrimary()) {
   u32 mask=ChoiceMask(primary);
   register u32 merged __asm__("r1")=gDisplayFlags|mask;
   __asm__ volatile("" : "+r"(merged) : "r"(mask));
   gDisplayFlags=merged;
  }
  if(PollSecondary()) {
   u32 mask=ChoiceMask(secondary);
   register u32 merged __asm__("r1")=gDisplayFlags|mask;
   __asm__ volatile("" : "+r"(merged) : "r"(mask));
   gDisplayFlags=merged;
  }
  {
   register u32 old_control __asm__("r1")=gDisplayFlags;
   register u32 merged_control __asm__("r0");
   register u32 display_bits __asm__("r3");
   __asm__ volatile("" : "+r"(old_control));
   display_bits=7232;
   __asm__ volatile("" : "+r"(display_bits));
   merged_control=display_bits|old_control;
   __asm__ volatile("" : "+r"(merged_control));
   gDisplayFlags=merged_control;
  }
  SetMode(6);gKeys.flags|=1;gScene.state=14;break;
 case 12:BeginExit();gScene.state=13;break;
 case 13:
  if(!PollExit()) break;
  FinishExit();if(gScene.return_early) gScene.state=8;else gScene.state=14;break;
 case 15:if(PollTransition(15)) gScene.state=0;break;
 case 16:if(PollTransition(16)) gScene.state=12;break;
 case 17:gScene.return_early=1;SetTransition(16,16);gScene.state=16;break;
 case 18:gScene.return_early=1;gScene.state=12;break;
 case 19:if(PollTransition(16)) gScene.state=20;break;
 case 20:gScene.timer=8;SetSceneLayer(1);gScene.state=22;break;
 case 22:
  if(gScene.timer) {if(--gScene.timer) break;}
  gScene.state=21;break;
 case 21:RegisterTask(&gTasks,8,CallbackB);gScene.state=23;break;
 case 23:if(gTasks.states[8]==255)gScene.state=24;break;
 case 24:SetSceneOverlay(1);gScene.state=26;break;
 case 26:
  fill_a=0;CpuSet(&fill_a,(void*)0x0600E000,0x01000800);
  fill_b=0;CpuSet(&fill_b,(void*)0x06005000,0x01000800);
  ResetNode(GetActor());PrepareAssets();gScene.state=25;break;
 case 25:
  ResetNode(GetActor());if(!PollAssets()) break;
  ClearAssets();FinishAssets();
  if(gPending) {
   node=FindNode(GetActor(),gPending);
   if(node)ApplyNode(node,10,node->direction,0);
   gPending=0;
  }
  SetTransition(8,15);gScene.state=15;break;
 case 27:if(PollTransitionOut(16))gScene.state=28;break;
 case 28:SetSceneLayer(0);gScene.state=29;break;
 case 29:RegisterTask(&gTasks,8,CallbackB);gScene.state=30;break;
 case 30:
  if(ReadFlag(74)) {if(gTasks.states[8]==253)gScene.state=31;}
  else {if(gTasks.states[8]==255)gScene.state=31;}
  break;
 case 31:SetSceneOverlay(0);gScene.state=34;break;
 case 34:
  fill_c=0;CpuSet(&fill_c,(void*)0x0600E000,0x01000800);
  fill_d=0;CpuSet(&fill_d,(void*)0x06005000,0x01000800);
  ResetNode(GetActor());PrepareAssets();gScene.state=32;break;
 case 32:
  ResetNode(GetActor());if(!PollAssets())break;
  SetTransitionOut(8,15);gScene.state=33;break;
 case 33:if(PollTransitionOut(15))gScene.state=0;break;
 case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 9:case 14:break;
 }
 return 2;
}
