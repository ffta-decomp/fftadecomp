/* Complete original unit/job modal transaction. Helpers retain original ABI. */
typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef unsigned int u32;
union StyleCode {u8 raw;struct {u8 orientation:1;u8 variant:7;} __attribute__((packed)) bits;} __attribute__((packed));
struct Modal {u8 gap0[38],waiting,gap39[1940-39];u16 text;union StyleCode style;u8 state,unit_id,job_id,argument2,argument1,clear_region;};
extern const u8 gStyle[];extern u8 gFontA[],gFontB[];
extern void ClearRegion(u8,u8,u8,u8),CreateMessage(void*,int,int,void*,void*,int,int,int,int,int),SetActor(void*,u8),SetPortrait(u8,u8,u8,u32),SetMessageFlags(u16),StopMessage(void),ReplaceMessage(u8,u16),UpdateMessage(void);
extern void *FindRecord(u32);extern u32 GetJobProperty(u8,u8,u8);extern u16 PollMessage(void);
__asm__(".global gStyle\n.set gStyle,0x83916c0");
__asm__(".global gFontA\n.set gFontA,0x30008b0");
__asm__(".global gFontB\n.set gFontB,0x3000990");
__asm__(".global ClearRegion\n.thumb_set ClearRegion,0x802a2c1");
__asm__(".global CreateMessage\n.thumb_set CreateMessage,0x801174d");
__asm__(".global SetActor\n.thumb_set SetActor,0x80132b9");
__asm__(".global SetPortrait\n.thumb_set SetPortrait,0x8013109");
__asm__(".global SetMessageFlags\n.thumb_set SetMessageFlags,0x801339d");
__asm__(".global StopMessage\n.thumb_set StopMessage,0x8013365");
__asm__(".global ReplaceMessage\n.thumb_set ReplaceMessage,0x8011b31");
__asm__(".global UpdateMessage\n.thumb_set UpdateMessage,0x8011c61");
__asm__(".global FindRecord\n.thumb_set FindRecord,0x80c83cd");
__asm__(".global GetJobProperty\n.thumb_set GetJobProperty,0x80c8571");
__asm__(".global PollMessage\n.thumb_set PollMessage,0x8011861");

struct Message {u8 prefix[38],waiting;};

void SceneRegisteredRoot_0002AD54(struct Modal *modal)
{
 u8 first,second;struct Message *message=(struct Message*)modal;
 switch(modal->state) {
 case 1:
  if(modal->clear_region) {
   if(modal->style.raw<=1) ClearRegion(0,0,30,9);
   else ClearRegion(0,12,30,9);
  }
  CreateMessage(modal,modal->argument1,modal->argument2,gFontA,gFontB,(s8)gStyle[modal->style.raw*4],(s8)(gStyle+1)[modal->style.raw*4],(gStyle+2)[modal->style.raw*4],(gStyle+3)[modal->style.raw*4],modal->text);
  {
  u8 orientation;
  register void *actor __asm__("r2")=FindRecord(modal->unit_id);
  __asm__("" : "+r"(actor));
  orientation=0;
  {
   register u32 style_work __asm__("r0")=modal->style.raw;
   register u32 style_mask __asm__("r1")=1;
   __asm__("" : "+r"(style_work), "+r"(style_mask));
   style_work &= style_mask;
   __asm__("" : "+r"(style_work));
   if(style_work==0) orientation=1;
  }SetActor(actor,orientation);}
  SetMessageFlags(3);modal->state=3;break;
 case 2: {
  u8 orientation;
  if(modal->clear_region) ClearRegion(0,0,30,9);
  CreateMessage(modal,modal->argument1,modal->argument2,gFontA,gFontB,(s8)gStyle[modal->style.raw*4],(s8)(gStyle+1)[modal->style.raw*4],(gStyle+2)[modal->style.raw*4],(gStyle+3)[modal->style.raw*4],modal->text);
  first=GetJobProperty(modal->job_id,modal->job_id,9);
  second=GetJobProperty(modal->job_id,modal->job_id,10);
  orientation=0;
  {
   register u32 style_work __asm__("r0")=modal->style.raw;
   register u32 style_mask __asm__("r1")=1;
   __asm__("" : "+r"(style_work), "+r"(style_mask));
   style_work &= style_mask;
   __asm__("" : "+r"(style_work));
   if(style_work==0) orientation=1;
  }SetPortrait(first,second,orientation,18432);SetMessageFlags(3);modal->state=3;break;
 }
 case 4:
  if(modal->clear_region) ClearRegion(0,0,30,9);
  StopMessage();ReplaceMessage(modal->argument1,modal->argument2);modal->state=3;break;
 case 3:
  if(message->waiting) modal->state=5;
  else if(PollMessage()==1) {
   if(modal->clear_region) ClearRegion(0,0,0,0);
   modal->state=0;
  }
  break;
 case 5:PollMessage();break;
 case 6:StopMessage();modal->state=7;break;
 case 7:
  if(PollMessage()==1) {
   modal->state=0;
   if(modal->clear_region) ClearRegion(0,0,0,0);
  }
  break;
 case 0:break;
 }
 UpdateMessage();
}
