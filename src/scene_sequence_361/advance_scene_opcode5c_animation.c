typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 phase,pad2;void *owner;u8 unknown8[12];u16 repetitions,unknown22;u32 unknown24;}Event;
typedef struct {u8 unknown0[8];u16 length;u8 unknown10[10];u16 frame;u8 unknown22[6];}Animation;
typedef struct {void *owner;u16 unknown4,repetitions;Animation animation;u8 copies[4][28],unknown148[28];}Work;
typedef struct {u8 unknown0[12226],option;}Settings;
typedef void (*CopyRoutine)(void*,const void*,u32);
extern Settings GameSettings asm("0x02000000");
extern CopyRoutine const CurrentCopyRoutine asm("0x0836d4bc");
extern void CallCopy(void*,const void*,u32,CopyRoutine) asm("0x08142251");
extern void LoadResource(void*,const void*) asm("0x0800543d");
extern void InitializeCopy(void*,const void*,void*,u32) asm("0x08000add");
extern void InitializeAnimation(Animation*,const void*,const void*,u32,u32) asm("0x0802b3a9");
extern void *AdvanceAnimation(Animation*) asm("0x0802b3d5");
extern void ComputePoint(s32,s32,s32,volatile s16*,volatile s16*,volatile s16*) asm("0x0801c919");
extern void ProjectPoint(s16,s16,volatile s16*,volatile s16*) asm("0x0801c961");
extern void DrawFrame(void*,s32,s32,u32,u32,u32,u32,u32,u32,u32,u32) asm("0x08002051");
s32 CoreRegion_0012B5F8(void *unused,Event *event,Work *work)
{
 s16 point_x,point_y,point_z;
 s32 phase=event->phase;
 switch(phase){
 case 0:{
  s32 option;
  u32 option_bits;
  const void *palette;
  CopyRoutine const *copy_cell;
  work->owner=event->owner;work->repetitions=event->repetitions;
  option_bits=(u32)GameSettings.option<<30;
  option=option_bits>>30;
  switch(option){case 2:palette=(void*)0x0841b320;break;case 1:palette=(void*)0x0841be00;break;case 0:default:palette=(void*)0x0841a820;break;}
  copy_cell=&CurrentCopyRoutine;
  CallCopy((void*)0x03003b20,palette,32,*copy_cell);
  break;
 }
 case 1:break;
 case 256:
  LoadResource((void*)0x02003cb0,(void*)0x083c5c6c);
  event->phase=257;
  break;
 case 257:{
  register u32 stride asm("r6");
  u8 *source,*destination,*first_context;
  u32 words;
  stride=3840;
  asm volatile("" : "+r"(stride));
  source=(u8*)0x02003cb0;destination=(u8*)0x06013c00;
  first_context=work->copies[0];
  words=stride>>2;
  InitializeCopy(first_context,source,destination,words);
  asm volatile("" : "+r"(source), "+r"(destination));
  source+=stride;destination+=stride;
  InitializeCopy(work->copies[1],source,destination,words);
  source+=stride;destination+=stride;
  InitializeCopy(work->copies[2],source,destination,words);
  source+=stride;destination+=stride;
  InitializeCopy(work->copies[3],source,destination,words);
  event->phase=258;
  break;
 }
 case 258:
  InitializeAnimation(&work->animation,(void*)0x08422adc,(void*)0x0841ceec,0,0);
  event->phase=259;
  break;
 case 259:{
  Animation *animation=&work->animation;
  void *frame;
  u32 repetitions;
  ComputePoint(192,240,64,&point_x,&point_y,&point_z);
  ProjectPoint(point_x,point_y,&point_x,&point_y);
  frame=AdvanceAnimation(animation);
  DrawFrame(frame,point_x,point_y,0,0,0,0,0,480,3,6);
  if(animation->frame==(s32)animation->length-1){
   repetitions=work->repetitions-1;work->repetitions=repetitions;
   if((u16)repetitions==0)event->phase=260;
  }
  break;
 }
 case 260:event->phase=3;break;
 }
 return 0;
}
