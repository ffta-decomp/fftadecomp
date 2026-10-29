#include "interfaces.h"
void CoreGlobal36_00070604(void *unused,u8 *state)
{
 u32 shadow_zero;
 register u8 selected_zero __asm__("r3");
 u16 clear_a,clear_b,fill_a,fill_b,fill_c,fill_d,value;int record,offset;struct Context *context;u8 *initial_tasks;register u8 *menu_mode __asm__("r0");struct Context **context_cell,**record_context_cell;
 context_cell=&gContext;
 /* The entry cell is carried into state5 or handed to the record-copy phase. */
 __asm__("" : "+r"(context_cell));
 (*context_cell)->state=*state;
 switch(*state) {
 case 0:
  clear_a=0;CpuSet(&clear_a,gScratch,0x01000100);
  clear_b=0;CpuSet(&clear_b,gScratch+512,0x01000100);
  Synchronize();*state=3;break;
 case 4:*state=3;break;
 case 3:
  gActiveWindow=255;SetWindowMode(1);InitializeWindows();InitializeGraphics();Synchronize();
  record=14;
  record_context_cell=context_cell;
  __asm__("" : "+r"(record_context_cell));
  offset=1000;
  for(;record<=15;++record) {
   CpuSet(GetRecord((u8)record),(u8*)*record_context_cell+offset,16);offset+=32;
  }
  Synchronize();InitializeUnitMenu();
  {
   register volatile u16 *shadow __asm__("r0")=gDisplay;
   __asm__("" : "+r"(shadow));
   (void)shadow[8];
   selected_zero=0;
   shadow_zero=0;
   /* The byte input dies at selected; the word input survives to default owner. */
   __asm__("" : "+r"(selected_zero), "+r"(shadow_zero));
   shadow[8]=shadow_zero;
   value=shadow[8];(void)shadow[6];shadow[6]=value;
   (void)shadow[7];shadow[7]=shadow_zero;
   value=shadow[7];(void)shadow[5];shadow[5]=value;
  }
  gContext->unit=gPending;gContext->selected=selected_zero;gContext->sentinel=255;
  initial_tasks=gTasks;
  /* The original initialized table snapshot survives only the default outcome. */
  __asm__("" : "+r"(initial_tasks));
  InitializeTasks(initial_tasks,gTaskDescriptors,gTaskStorage,8);
  PrepareUnit(gContext->unit,((gContext->unit->flags>>15)^1));
  switch(ReadSave(51)) {
  case 0:
   gContext->menu_mode=1;
   if(gScene.flags&2)gMenuOwner=0;
   if(!IsUnitRestricted(gContext->unit) && (gScene.flags&2) && !(gContext->unit->flags&8192)) {
    context=gContext;context->previous=((int)gPending-(int)gUnitPool)/264;
    gContext->selection=gContext->previous;
    RegisterTask(gTasks,0,AbilityCallback);
   } else {
    CpuSet(GetRecord(5),(u8*)gContext+712,16);
    goto register_menu;
   }
   break;
  case 2: {
   register u32 mode_offset __asm__("r2");
   menu_mode=(u8*)gContext;
   mode_offset=0x44c;
   /* Actual branch root/offset inputs precede this address publication. */
   __asm__("" : "+r"(menu_mode), "+r"(mode_offset));
   menu_mode+=mode_offset;
   __asm__("" : "+r"(menu_mode));
   goto activate_menu;
  }
  case 4: {
   register u32 mode_offset __asm__("r2");
   menu_mode=(u8*)gContext;
   mode_offset=0x44c;
   /* This original outcome owns its separate root/offset definition. */
   __asm__("" : "+r"(menu_mode), "+r"(mode_offset));
   menu_mode+=mode_offset;
   __asm__("" : "+r"(menu_mode));
   goto activate_menu;
  }
  case 1:case 3:case 5:menu_mode=&gContext->menu_mode;
activate_menu: {
   register u32 owner_zero __asm__("r2")=0;
   /* Both actual store inputs are defined before the original shared write sequence. */
   __asm__("" : "+r"(menu_mode), "+r"(owner_zero));
   *menu_mode=1;gMenuOwner=(void*)owner_zero;
  }
register_menu:
   RegisterTask(gTasks,0,MenuCallback);break;
  default:
   WriteSave(51,6);gContext->menu_mode=1;gMenuOwner=(void*)shadow_zero;RegisterTask(initial_tasks,0,MenuCallback);break;
  }
  RegisterTask(gTasks,1,CommonCallback);RegisterTask(gTasks,2,CommonCallback);RegisterTask(gTasks,3,CommonCallback);
  RegisterChild(gTasks,4,DetailsCallback,3);RegisterTask(gTasks,7,CommonCallback);
  if(gMenuOwner)RegisterChild(gTasks,5,WindowCallback,1);else RegisterTask(gTasks,5,WindowCallback);
  RegisterTask(gTasks,6,AuxiliaryCallback);RegisterTask(gCallbackSystem,0,TextCallback);RegisterTask(gCallbackSystem,1,CallbackB289);
  *state=5;break;
 case 5:PollTasks(gTasks,8);*state=(*context_cell)->state;break;
 case 254:
  fill_a=1;CpuSet(&fill_a,gWindowA.data,(gWindowA.width*gWindowA.height)|0x01000000);
  fill_b=1;CpuSet(&fill_b,gWindowB.data,(gWindowB.width*gWindowB.height)|0x01000000);
  fill_c=0;CpuSet(&fill_c,gWindowC.data,(gWindowC.width*gWindowC.height)|0x01000000);
  fill_d=0;CpuSet(&fill_d,gWindowD.data,(gWindowD.width*gWindowD.height)|0x01000000);
  ReleaseResource(gGraphics.resource,64);StopTasks(gTasks);StopTask(gCallbackSystem,0);StopTask(gCallbackSystem,1);CloseUnitMenu(1);*state=255;break;
 case 255:break;
 }
}
