#include "interfaces.h"
void CoreFrame32_0007E37C(void *unused,u8 *state)
{
 u16 fill0,fill1,fill2,fill3,fill4,fill5,fill6,fill7,fill8,clear_value;
 void *display_result;u16 selected;u8 raw_timer;
 switch(*state) {
 case 0:
  UNIT(gContext)=gPending;SAVED_RECORD(gContext)=SELECTION_RECORD(gContext);PREVIEW_ENABLED(gContext)=1;
  F_SetPreview(1);UNIT_STATE(gContext)=UNIT(gContext)->flags&28;
  SAVED_RECORD(gContext)=SELECTION_RECORD(gContext);
  {struct Context *reset=gContext;SNAPSHOT_HALF(reset)=0;
   {register u8 *scroll_x __asm__("r2")=&gScrollX;register u8 *scroll_y __asm__("r0")=&gScrollY;
    __asm__("" : "+r"(scroll_x), "+r"(scroll_y));*scroll_y=0;*scroll_x=0;}
   PENDING(reset)=0;COUNTER(reset)=0;}
  CATEGORY(gContext)=0;MODE(gContext)=0;gChoicesAvailable=0;
  F_ResetUnitPreview();F_LoadUnitPreview(1,UNIT(gContext),0,1);
  {struct Context *position=gContext;int source_x=SOURCE_X(position)/8;int source_y=SOURCE_Y(position)/8;X(position)=source_x;Y(position)=source_y;}
  F_InitializeGraphic(gGraphics.resource,25,0,0,0,0,3,gTiles,gPalette,432,0);
  {register struct GraphicStatus *status __asm__("r0")=(struct GraphicStatus*)(gGraphics.resource+700);
   __asm__("" : "+r"(status));status->status=1;}
  {struct Context *bounds=gContext;X(bounds)=120;Y(bounds)=65528;GRAPHIC_OFFSET(bounds)=65472;GRAPHIC_SCALE(bounds)=56;EFFECT_FLAGS(bounds)=3;}
  {u32 graphic_size=F_UnitGraphicSize(UNIT(gContext));struct Unit *graphic_unit=UNIT(gContext);
   register void *copy_destination __asm__("r0")=gTextScratch;
   __asm__("" : "+r"(copy_destination));F_CopyUnitGraphic(copy_destination,graphic_unit);
   {register void *destination __asm__("r1")=(void*)0x06014300;
    __asm__("" : : "r"(destination));graphic_size<<=10;graphic_size>>=11;
    F_CpuSet(gTextScratch,destination,graphic_size);}}
  if(F_Restricted(UNIT(gContext)))F_SetLabel(LABEL_BUFFER(gContext),(u8)F_LabelId(UNIT(gContext),0));
  else F_SetLabel(LABEL_BUFFER(gContext),(u8)F_LabelId(UNIT(gContext),1));
  {register void *result __asm__("r0")=F_GetDisplay(UNIT(gContext));
   __asm__("" : "+r"(result));DISPLAY_HANDLE(gContext)=result;EFFECT_FLAGS(gContext)=3;}
  PREVIEW(gContext)=0;*state=35;break;
 case 35:
  if(COUNTER(gContext)++<=10)break;
  F_SetWindow(3,2);gTasks.states[5]=3;F_ResetActor(UNIT(gContext));ROW(gContext)=8;gAlternate=0;gResume=3;*state=24;break;
 case 26: {
  u16 message_id=F_SelectorIndex(SELECTOR(gContext))+44;
  {struct Context *preview=gContext;SAVED_PREVIEW(preview)=PREVIEW(preview);}PREVIEW(gContext)=0;
  {struct Context *cursor=gContext;SAVED_CURSOR(cursor)=CATEGORY_CURSOR(cursor);}
  COUNTER(gContext)=0;CATEGORY_CURSOR(gContext)=3;
  F_ShowMessage(gTextScratch,message_id,&gSurfaceB,&gSurfaceD);*state=27;break;
 }
 case 27:
  if(!F_PollMessage())break;
  TICK(gContext)=15;
  {struct Context *cursor=gContext;CATEGORY_CURSOR(cursor)=SAVED_CURSOR(cursor);}
  {struct Context *preview=gContext;PREVIEW(preview)=SAVED_PREVIEW(preview);}
  *state=28;break;
 case 28:
  gKeys.held=0;gKeys.pressed=0;
  if(TICK(gContext))--TICK(gContext);else *state=2;
  break;
 case 2:
  if(gKeys.pressed==4) {*state=26;goto poll_selector;}
  if(gKeys.pressed&1) {
   selected=F_SelectorIndex(SELECTOR(gContext));F_SetSound(100);
   if(selected==0)gResume=13;
   else if(selected==1)gResume=15;
   else {if(!gChoicesAvailable){F_SetSound(106);break;}gResume=17;}
   F_HideSelector(SELECTOR(gContext));gWaitWindow=4;{register struct Window *active_window __asm__("r0")=gWindows;__asm__("" : "+r"(active_window));active_window+=4;__asm__("" : "+r"(active_window));active_window->flags=3;}F_SetWindow(4,12);*state=34;
  } else if(gKeys.pressed&2) {
   PREVIEW(gContext)=0;F_HideSelector(SELECTOR(gContext));F_SetSound(105);
   gWaitWindow=4;{register struct Window *active_window __asm__("r0")=gWindows;__asm__("" : "+r"(active_window));active_window+=4;__asm__("" : "+r"(active_window));active_window->flags=3;}F_SetWindow(4,12);gAlternate=5;gResume=25;*state=34;break;
  }
poll_selector:
  if(F_PollSelector(SELECTOR(gContext),gKeys.repeat)) {
   F_FillText(4,F_GetText(4,1,1,NEXT_CATEGORY(gContext)*2+2),10,0xC000);
   F_FillText(4,F_GetText(4,1,1,CATEGORY(gContext)*2+2),10,0xB000);
   F_SetWindow(4,2);
  }
  break;
 case 3:
  F_SetSound(101);
  {u8 *availability=&gChoicesAvailable;__asm__("" : "+r"(availability));*availability=F_HasChoices(UNIT(gContext));}
  F_InitSelector(SELECTOR(gContext),gSelectorData,3,28,0,1,0,1,0,0,CATEGORY(gContext));
  F_PollSelector(SELECTOR(gContext),0);
  F_FillText(4,F_GetText(4,1,1,NEXT_CATEGORY(gContext)*2+2),10,0xC000);
  F_FillText(4,F_GetText(4,1,1,CATEGORY(gContext)*2+2),10,0xB000);
  F_SetWindow(4,2);gWaitWindow=4;F_SetWindow(4,2);gResume=2;*state=34;break;
 case 4:break;
 case 5:
  {register u16 *first_clear __asm__("r0")=&fill0;__asm__("" : : "r"(first_clear));clear_value=0;__asm__("" : "+r"(clear_value));*first_clear=clear_value;}
  F_CpuSet(&fill0,F_GetText(0,1,6,9),0x01000001);
  fill1=clear_value;F_CpuSet(&fill1,F_GetText(0,1,6,10),0x01000001);
  fill2=clear_value;F_CpuSet(&fill2,F_GetText(0,1,11,14),0x01000003);
  fill3=clear_value;F_CpuSet(&fill3,F_GetText(0,1,11,15),0x01000003);
  fill4=clear_value;F_CpuSet(&fill4,F_GetText(0,1,11,17),0x01000003);
  fill5=clear_value;F_CpuSet(&fill5,F_GetText(0,1,11,18),0x01000003);
  fill6=clear_value;F_CpuSet(&fill6,gSurfaceA.data,(gSurfaceA.width*gSurfaceA.height)|0x01000000);
  fill7=clear_value;F_CpuSet(&fill7,gSurfaceB.data,(gSurfaceB.width*gSurfaceB.height)|0x01000000);
  {struct Context *completed=gContext;u16 *counter=&COUNTER(completed);register u32 zero __asm__("r0")=0;
   __asm__("" : "+r"(zero) : "r"(counter));*counter=zero;EFFECT_DELAY(completed)=8;}
  gResume=254;*state=22;break;
 case 13:F_Register(&gTasks,2,EquipmentCallback);*state=14;break;
 case 14:if(gTasks.states[2]==255){CATEGORY(gContext)=0;*state=3;}break;
 case 15:F_Register(&gTasks,2,AbilityAssignmentCallback);*state=16;break;
 case 16:if(gTasks.states[2]==255){CATEGORY(gContext)=1;*state=3;}break;
 case 17:F_Register(&gTasks,2,JobChangeCallback);*state=18;break;
 case 18:if(gTasks.states[2]==255){CATEGORY(gContext)=2;*state=3;}break;
 case 21:
  if(COUNTER(gContext)++<=14) {
   raw_timer=gWindows[2].timer;
   if((s8)raw_timer<0){gWindows[2].timer=raw_timer+1;F_SetWindow(2,2);}
  } else {
   UNIT_STATE(gContext)|=1;F_SetActorMode(FIELD(gContext,u8,0x986));F_SetWindow(3,2);F_SetWindow(2,2);*state=gResume;
  }
  break;
 case 22:
  if(COUNTER(gContext)++<=9) {
   {u8 timer=gWindows[2].timer;
    if((s8)timer>-9){gWindows[2].timer=timer-1;F_SetWindow(2,2);}}
   {u8 *scroll_x=&gScrollX;struct Context *scroll;
    __asm__("" : : "r"(scroll_x));scroll=gContext;*scroll_x=SCROLL_SOURCE_X(scroll)/8;gScrollY=SCROLL_SOURCE_Y(scroll)/8;
    X(scroll)=*scroll_x;Y(scroll)=gScrollY;F_MoveGraphic(gGraphics.resource,25,*scroll_x,gScrollY);}
   {struct Context *effect=gContext;
    if(FIELD(effect,u8,0x450)==8) {
     EFFECT_FLAGS(effect)=3;GRAPHIC_OFFSET(gContext)-=8;GRAPHIC_SCALE(gContext)=56;
    }}
   SCROLL_SOURCE_Y(gContext)-=64;
  } else {
   F_RemoveGraphic(gGraphics.resource,26);fill8=0;F_CpuSet(&fill8,gSurfaceD.data,(gSurfaceD.width*gSurfaceD.height)|0x01000000);*state=gResume;
  }
  break;
 case 23:
  if(COUNTER(gContext)++<=9) {
   {struct Context *motion=gContext;int x=SOURCE_X(motion)/8;int y=SOURCE_Y(motion)/8;y-=COUNTER(motion)*8;Y(motion)=y;
    F_MoveGraphic(gGraphics.resource,25,x,y);}EFFECT_FLAGS(gContext)=3;GRAPHIC_OFFSET(gContext)-=8;GRAPHIC_SCALE(gContext)=56;
  } else {
   struct Context *restore=gContext;int x=SOURCE_X(restore)/8;int y=SOURCE_Y(restore)/8;Y(restore)=y;F_MoveGraphic(gGraphics.resource,25,x,y);
   F_ResetActor(UNIT(gContext));GRAPHIC_OFFSET(gContext)=0;GRAPHIC_SCALE(gContext)=56;F_MoveGraphic(gGraphics.resource,25,x,y);
   {u32 graphic_size=F_UnitGraphicSize(UNIT(gContext));struct Unit *graphic_unit=UNIT(gContext);
    register void *copy_destination __asm__("r0")=gTextScratch;
    __asm__("" : "+r"(copy_destination));F_CopyUnitGraphic(copy_destination,graphic_unit);
    {register void *destination __asm__("r1")=(void*)0x06014300;
    __asm__("" : : "r"(destination));graphic_size<<=10;graphic_size>>=11;
    F_CpuSet(gTextScratch,destination,graphic_size);}}
   F_SetLabel(LABEL_BUFFER(gContext),(u8)F_LabelId(UNIT(gContext),1));display_result=F_GetDisplay(UNIT(gContext));DISPLAY_HANDLE(gContext)=display_result;EFFECT_FLAGS(gContext)=3;
   F_CpuSet((u8*)gContext+40,gScratch,0x04000080);F_CpuSet((u8*)gContext+552,gScratch+512,0x04000080);*state=1;
  }
  break;
 case 34:
  if(!gWindows[gWaitWindow].state){*state=gResume;gResume=gAlternate;}
  break;
 case 24:
  Y(gContext)+=8;F_MoveGraphic(gGraphics.resource,25,(u8)X(gContext),(u8)Y(gContext));GRAPHIC_OFFSET(gContext)+=8;
  ++gWindows[2].timer;F_SetWindow(2,3);TICK(gContext)=(TICK(gContext)+1)%240;
  if(ROW(gContext)==4)F_SetSound(142);
  if(--ROW(gContext)==0){*state=gResume;gResume=gAlternate;}
  F_SetRow(8,(u8)ROW(gContext));break;
 case 25:
  Y(gContext)-=8;GRAPHIC_OFFSET(gContext)-=8;F_MoveGraphic(gGraphics.resource,25,(u8)X(gContext),(u8)Y(gContext));
  --gWindows[2].timer;F_SetWindow(2,3);TICK(gContext)=(TICK(gContext)+1)%240;
  if(++ROW(gContext)==8){*state=gResume;gResume=gAlternate;}
  F_SetRow(8,(u8)ROW(gContext));break;
 case 254:
  if(COUNTER(gContext)++>10){F_Release(FIELD(gContext,void*,1088));*state=255;}break;
 case 255:ROOT_CALLBACK(gContext)=254;break;
 }
}
