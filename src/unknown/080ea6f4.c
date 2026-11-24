typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct Task Task;
typedef struct {u16 phase,pad2;void *owner;u8 unknown8[20];}Event;
typedef struct {s32 from_x,from_y,to_x,to_y,sign_x,sign_y;u32 delta_x,delta_y;s32 error,half_delta_y;u32 full_delta_y;}Curve;
typedef struct {u16 timer,unknown2;Task *sequence;u8 template_data[24];Task *renderer;Curve curve;Task *extra;}Work;
typedef struct {u8 unknown0[74];volatile u8 control74,control75,control76,control77;}Shadow;
extern Shadow DisplayShadow asm("0x03000940");
extern void CopyHalfwords(const void*,void*,u32) asm("0x0814186d");
extern void PlaceResource(const void*,u32,u32,u32,s32,u32) asm("0x080d7221");
extern Task *CreateRenderer(u8,u8,u8,const void*,Task*) asm("0x080d9a25");
extern void ReadDisplayPair(volatile u8*,volatile u8*) asm("0x0801e611");
extern u32 LowMask(u8) asm("0x080035f9");
extern u32 HighMask(u8) asm("0x080035a9");
extern void InitializeCurve(Curve*,s32,s32,s32,s32) asm("0x080075cd");
extern void AdvanceCurve(Curve*) asm("0x080076a1");
extern u32 CurveComplete(Curve*) asm("0x08007881");
extern Task *CreatePalette(const void*,Task*) asm("0x080d4705");
extern Task *CreateStage(const void*,u8,u16,u8,Task*) asm("0x080dfd8d");
extern Task *PollPalette(Task*) asm("0x080d4775");
extern void UpdateRenderer(Task*,const void*,u8) asm("0x080d9a89");
extern void SetRendererPosition(Task*,u8,u8) asm("0x080d9add");
extern Task *PollRenderer(Task*) asm("0x080d9b65");

s32 RemainingBand43_000EA6F4(Task *parent,Event *event,Work *work)
{
 volatile u8 first,second;
 s32 phase=event->phase;
 switch(phase){
 case 0:
  CopyHalfwords((const void*)0x08398b8c,work->template_data,12);
  work->timer=61;
  break;
 case 1:break;
 case 256:
  if(--work->timer==0){
   u32 setup_mask,first_mask,second_mask,last_mask;
   Shadow *shadow;
   Curve *curve;
   PlaceResource((void*)0x088f491c,0,2,0,0,0);
   work->renderer=CreateRenderer(16,16,3,work->template_data,parent);
   ReadDisplayPair(&first,&second);
   setup_mask=LowMask(2);
   shadow=&DisplayShadow;
   shadow->control74=setup_mask|64;
   first_mask=LowMask(first);
   second_mask=LowMask(second);
   last_mask=LowMask(3);
   shadow->control75=first_mask|second_mask|last_mask|48;
   shadow->control76=16;shadow->control77=16;
   curve=&work->curve;
   InitializeCurve(curve,16,0,10,29);
   AdvanceCurve(curve);
   work->sequence=CreatePalette((void*)0x0894914c,parent);
   work->extra=CreateStage((void*)0x08398bb8,4,4,0,parent);
   ++event->phase;
  }
  break;
 case 257:event->phase=phase+1;break;
 case 258:{
  Curve *curve=&work->curve;
  if(CurveComplete(curve)==0){
   u8 previous=work->template_data[5];
   u32 current=curve->from_x;
   work->template_data[5]=current;work->template_data[11]=current;
   work->template_data[13]=current;work->template_data[19]=current;
   if((u8)current!=previous)UpdateRenderer(work->renderer,work->template_data,3);
   AdvanceCurve(curve);
  }
  work->sequence=PollPalette(work->sequence);
  if(work->sequence==0){
   work->sequence=CreatePalette((void*)0x08948e44,parent);
   work->extra=CreateStage((void*)0x08398bd8,3,4,0,parent);
   work->timer=20;++event->phase;
  }
  break;
 }
 case 259:
  if(--work->timer==0){work->timer=98;++event->phase;}
  break;
 case 260:
  if(work->timer){--work->timer;if(work->timer==0)SetRendererPosition(work->renderer,16,16);}
  work->sequence=PollPalette(work->sequence);
  if(work->sequence==0){
   u32 mask=HighMask(2);
   *(volatile u16*)&DisplayShadow=*(volatile u16*)&DisplayShadow&~mask;
   ++event->phase;
  }
  break;
 case 261:
  work->renderer=PollRenderer(work->renderer);
  if(work->renderer==0)event->phase=2;
  break;
 }
 return 0;
}
