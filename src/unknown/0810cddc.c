typedef unsigned char u8;typedef unsigned short u16;typedef short s16;typedef unsigned int u32;typedef int s32;
typedef struct {u16 phase,pad;void *actor;u32 ordinal,flags,unknown16;u16 definition,variant;u32 unknown24;}Event;
typedef struct {u16 timer;u8 count,index,repetitions,variant,pad6[6];void *actor_record,*primary,*targets[24],*child,*mask,*object,*blend,*palette,*opening,*actor;u32 unknown144;void *stage;}Work;
typedef struct {u16 control;}Shadow;
extern Shadow DisplayShadow asm("0x03000940");
extern void *GetActorRecord(void*) asm("0x080dd47d"),*GetIndexedRecord(void*,u32) asm("0x080dd4b5");
extern void *Open(void*,const void*,u32,u32,const void*,void*) asm("0x080e03f9");
extern void Cleanup(void) asm("0x080d38b5");
extern void *PollOpening(void*) asm("0x080e05dd");
extern u32 CountTargets(void*) asm("0x080dd495");
extern void ResetActorRecord(void*) asm("0x080dd305");
extern void PrepareMask(u32,u32,u32,s32,s32) asm("0x080d49fd");
extern void *CreateMask(u32,const void*,u32,u32) asm("0x080d4b65");
extern u32 GetControlMask(u32) asm("0x080035a9");
extern void *CreateBlend(const void*,void*) asm("0x080d3e9d"),*CreatePalette(const void*,void*) asm("0x080d4705");
extern void *CreateObject(const void*,u32,s32,s32,u32,u32,u32,u32) asm("0x080d5cc1");
extern void *CreateStage(const void*,u32,u32,u32,void*) asm("0x080dfd8d");
extern void *PollBlend(void*) asm("0x080d3f09"),*PollPalette(void*) asm("0x080d4775"),*PollMask(void*,u32) asm("0x080d4d2d"),*PollObject(void*) asm("0x08011485");
extern void SetObjectDepth(void*,s32) asm("0x0801121d");
extern u32 CollectRecords(void**) asm("0x080dd3c5");
extern void *GetObjectRecord(void*) asm("0x080dd479");
extern s32 UnitField19IsZero(const void*) asm("0x080c8281");
extern void SelectRecord(void*) asm("0x080dc015");
extern u32 RecordTransitionBusy(void) asm("0x080d8b4d");
extern void GetPosition(void*,volatile u16*,volatile u16*,volatile u16*) asm("0x080dbda1");
extern u32 MoveCamera(s32,s32,u32) asm("0x0801ba21");
extern u32 CameraBusy(void) asm("0x0801bdb1");
extern void StopObject(void*) asm("0x08011429");
extern void LoadAsset(const void*,u32,u32,u32,u32) asm("0x080d45d1");
extern void *CreateCallback(void*,u32,const void*,void*) asm("0x08005b6d"),*PollChild(void*) asm("0x080e051d");
#define ADVANCE() do {register Event *phase_out asm("r1")=event;register s32 advanced_phase asm("r0")=phase_out->phase+1;asm volatile("" : "+r"(advanced_phase) : "r"(phase_out));phase_out->phase=advanced_phase;return 0;}while(0)
#define ENABLE_CONTROL() do {u32 control_mask=GetControlMask(2);register u32 control asm("r1")=DisplayShadow.control;control|=control_mask;asm volatile("" : "+r"(control));DisplayShadow.control=control;}while(0)
s32 AdvanceTargetListActionSequence(void *parent,Event *event,Work *work)
 asm("OriginalAuthoredAction_0010CDDC");
s32 AdvanceTargetListActionSequence(void *parent,Event *event,Work *work)
{
 volatile u16 actor_x,actor_y,actor_z,target_x,target_y,target_z;
 Event child_event;
 s32 phase=event->phase,next_phase;
 switch(phase){
 case 0:{
  void **actor_slot;
  u32 count;
  work->variant=event->variant;
  actor_slot=&work->actor;
  *actor_slot=event->actor;
  count=3;if(work->variant!=0)count=0;
  work->actor_record=GetActorRecord(*actor_slot);
  work->primary=GetIndexedRecord(*actor_slot,0);
  work->opening=Open(*actor_slot,(void*)0x083a26ac,count,7,(void*)phase,parent);
  break;
 }
 case 1:Cleanup();break;
 case 256:{
  void **opening_slot=&work->opening;
  void *opening=PollOpening(*opening_slot);
  *opening_slot=opening;if(opening!=0)break;
  if((u8)CountTargets(work->actor)==0){ResetActorRecord(work->actor_record);next_phase=2;goto store_phase;}
  PrepareMask(0,2,0,120,64);
  work->mask=CreateMask(0,(void*)0x088f2d18,991,7);
  ENABLE_CONTROL();
  work->blend=CreateBlend((void*)0x0894d7e4,parent);
  work->palette=CreatePalette((void*)0x0894ccac,parent);
  work->object=CreateObject((void*)0x085086d4,0,120,96,959,6,1,(u32)opening);
  work->stage=CreateStage((void*)0x083a26d0,1,4,0,parent);
  ADVANCE();
 }
 case 257:{
  u8 *slot_cursor=(u8*)work+128;
  void **blend_slot=(void**)slot_cursor;
  void *blend=PollBlend(*blend_slot),*palette,*mask,*object;
  void **records;
  u32 count,changed;
  u8 i;
  register u32 normalized_count asm("r0");
  register u32 iteration_count asm("r0");
  *blend_slot=blend;if(blend!=0)break;
  slot_cursor+=4;
  palette=PollPalette(*(void**)slot_cursor);*(void**)slot_cursor=palette;if(palette!=0)break;
  mask=PollMask(work->mask,0);work->mask=mask;if(mask!=0)break;
  DisplayShadow.control&=~GetControlMask(2);
  object=PollObject(work->object);work->object=object;if(object!=0)break;
  work->object=CreateObject((void*)0x085086d4,1,120,96,959,6,1,(u32)object);
  SetObjectDepth(work->object,-1);
  slot_cursor-=112;
  count=CollectRecords((void**)slot_cursor);work->count=count;
  /* The original LOW8 nonzero guard is defined before the loop carriers. */
  normalized_count=count<<24;
  asm("" : "+r"(normalized_count));
  i=0;
  records=(void**)slot_cursor;
  if(normalized_count!=0){do{
   void **slot=records+i;
   if((u8)UnitField19IsZero(GetObjectRecord(*slot))!=0 && *slot!=work->primary)*slot=0;
   i++;
   iteration_count=work->count;
   asm("" : "+r"(iteration_count));
  }while(i<iteration_count);}
  do{
   changed=0;i=0;
   while(i<work->count){
    void **scan_address=records+i;
    if(*scan_address==0){
     register s32 j asm("r1")=i;
     /* One real counter survives the source/destination copy and LOW8 wrap. */
     asm("" : "+r"(j));
     if(j<(s32)work->count-1){
      void **shift_base=records;
      do{
       void **destination=shift_base+j;
       void **source_address;
       j++;
       source_address=shift_base+j;
       *destination=*source_address;
       j=(u8)j;
      }while(j<(s32)work->count-1);
     }
     work->count--;changed=1;break;
    }
    i++;
   }
  }while(changed);
  work->timer=10;work->repetitions=1;
  ADVANCE();
 }
 case 258:{
  u32 timer=work->timer-1;work->timer=timer;
  if((u16)timer!=0)break;
  SelectRecord(work->targets[work->index]);
  ADVANCE();
 }
 case 259:{
  u32 index,repetitions;
  if((u8)RecordTransitionBusy()!=0)break;
  work->stage=CreateStage((void*)0x083a26d8,1,4,0,parent);
  work->timer=20;
  index=work->index+1;work->index=index;
  if((u8)index==work->count){
   repetitions=work->repetitions-1;work->repetitions=repetitions;
   if((u8)repetitions==0)ADVANCE();
   work->index=0;
  }
  next_phase=258;goto store_phase;
 }
 case 260:{
  u32 timer=work->timer-1;work->timer=timer;
  if((u16)timer!=0)break;
  GetPosition(work->actor_record,&actor_x,&actor_y,&actor_z);
  MoveCamera((s16)(actor_x-120),(s16)(actor_y-96),2);
  work->timer=30;
  ADVANCE();
 }
 case 261:{
  u32 timer;
  if((u8)CameraBusy()!=0)break;
  timer=work->timer;
  if(timer!=0){timer--;work->timer=timer;if((u16)timer!=0)break;}
  ADVANCE();
 }
 case 262:
  GetPosition(work->primary,&target_x,&target_y,&target_z);
  MoveCamera((s16)(target_x-120),(s16)(target_y-96),16);
  work->timer=20;
  ADVANCE();
 case 263:{
  u32 busy=(u8)CameraBusy();
  u32 timer;
  if(busy!=0)break;
  timer=work->timer;
  if(timer!=0){timer--;work->timer=timer;if((u16)timer!=0)break;}
  StopObject(work->object);
  LoadAsset((void*)0x088eb938,7,0,0,1);
  PrepareMask(0,2,0,120,64);
  work->mask=CreateMask(0,(void*)0x088f2d18,991,7);
  ENABLE_CONTROL();
  work->blend=CreateBlend((void*)0x0894d7e4,parent);
  work->palette=CreatePalette((void*)0x0894ccac,parent);
  work->object=CreateObject((void*)0x085086d4,2,120,96,959,6,1,busy);
  work->stage=CreateStage((void*)0x083a26e0,1,4,0,parent);
  ADVANCE();
 }
 case 264:{
  void **blend_slot=&work->blend;
  void **palette_slot;
  void *blend=PollBlend(*blend_slot),*palette,*mask,*object;
  *blend_slot=blend;if(blend!=0)break;
  palette_slot=&work->palette;
  palette=PollPalette(*palette_slot);*palette_slot=palette;if(palette!=0)break;
  mask=PollMask(work->mask,0);work->mask=mask;if(mask!=0)break;
  DisplayShadow.control&=~GetControlMask(2);
  object=PollObject(work->object);work->object=object;if(object!=0)break;
  *palette_slot=CreatePalette((void*)0x0894848c,parent);
  {
   Event *child_out=&child_event;
   child_out->definition=296;
   child_out->variant=(u32)object;
   child_out->actor=work->actor;
   child_out->ordinal=(u32)object;
   work->child=CreateCallback((void*)0x080efab1,44,child_out,parent);
  }
  ADVANCE();
 }
 case 265:{
  void **palette_slot=&work->palette;
  void *palette=PollPalette(*palette_slot),*child;
  *palette_slot=palette;if(palette!=0)break;
  child=PollChild(work->child);work->child=child;if(child!=0)break;
  next_phase=2;
store_phase:event->phase=next_phase;
  break;
 }
 }
 return 0;
}
