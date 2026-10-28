typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Task Task;
typedef struct {u16 state,unused2;void *record;u8 unused8[12];u16 mode;} Event;
typedef struct {u8 mode,unused1;s16 x,y,z;void *record,*actor,*first,*second;Task *optional,*effect,*script;} Work;
extern const u8 ModelDefinition[],EffectSequences[],ScriptSequence[];
extern void *project(void *,s16 *,s16 *,s16 *);
extern void *model(const void *,unsigned,int,int,int,unsigned,unsigned);
extern void depth(void *,int);
extern unsigned record_flag(void *,unsigned);
extern int record_value(void *);
extern Task *optional(void *,unsigned,Task *);
extern Task *create(void *,const void *,u8,u16,u32,Task *,u16);
extern Task *script(const void *,unsigned,unsigned,unsigned,Task *);
extern unsigned finish_models(void **,u16);
extern Task *poll(Task *);
u32 RemainingBand43_000E7130(Task *task,Event *event,Work *work)
{
 switch(event->state) {
 case 0:
  work->record=event->record;work->mode=event->mode;
  work->actor=project(work->record,&work->x,&work->y,&work->z);break;
 case 256: {
  register unsigned selected __asm__("r4");
  unsigned one,scriptflags;
  register unsigned mode __asm__("r1");
  register unsigned bit __asm__("r0");
  register unsigned flags __asm__("r3");
  register void *record __asm__("r0");
  register const u8 *sequence __asm__("r1");
  register u32 sequence_offset __asm__("r1");
  work->first=model(ModelDefinition,4,work->x,work->y,work->z,0x34d,7);
  work->second=model(ModelDefinition,5,work->x,work->y,work->z,0x34d,7);
  depth(work->first,-1);depth(work->second,1);
  selected=0;
  if((u8)record_flag(work->record,0)) {
   work->optional=optional(work->actor,20,task);selected=1;
  } else if((s16)record_value(work->record)>0)selected=2;
  mode=work->mode;one=1;__asm__("" : "+r"(mode), "+r"(one));
  bit=one;__asm__("" : "+r"(bit));bit&=mode;
  flags=2;if(bit)flags=4;
  record=work->record;sequence_offset=20*selected;
  __asm__("" : "+r"(sequence_offset));
  sequence_offset+=(u32)EffectSequences;sequence=(const u8 *)sequence_offset;
  __asm__("" : "+r"(record), "+r"(sequence), "+r"(flags));
  work->effect=create(record,sequence,12,0,flags,task,30);
  mode=work->mode;bit=one;__asm__("" : "+r"(bit));bit&=mode;
  scriptflags=8;if(bit)scriptflags=16;
  work->script=script(ScriptSequence,1,scriptflags|4,0,task);
  event->state++;break;
 }
 case 257:
  if((u8)finish_models(&work->first,2))event->state++;
  break;
 case 258:
  work->optional=poll(work->optional);
  if(work->optional==0) {
   work->effect=poll(work->effect);
   if(work->effect==0)event->state=2;
  }
  break;
 }
 return 0;
}
__asm__(".global project\n.thumb_set project,0x080dd749\n.global model\n.thumb_set model,0x080d5e81\n.global depth\n.thumb_set depth,0x08011059\n.global record_flag\n.thumb_set record_flag,0x080dd685\n.global record_value\n.thumb_set record_value,0x080dd4d5\n.global optional\n.thumb_set optional,0x080df90d\n.global create\n.thumb_set create,0x080dcfe5\n.global script\n.thumb_set script,0x080dfd8d\n.global finish_models\n.thumb_set finish_models,0x080d5f25\n.global poll\n.thumb_set poll,0x080dba5d\n.global ModelDefinition\n.set ModelDefinition,0x084f6130\n.global EffectSequences\n.set EffectSequences,0x08397790\n.global ScriptSequence\n.set ScriptSequence,0x083977dc");
