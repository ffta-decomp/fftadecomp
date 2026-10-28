typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Task Task;
typedef struct {u16 state,unused2;void *record;u8 unused8[12];u16 mode;} Event;
typedef struct {u8 mode,unused1[3];s16 x,y;void *record,*actor;u8 opaque16[12];Task *positioned,*effect;} Work;
extern void *project(void *,s16 *,s16 *,s16 *);
extern Task *create(void *,const void *,u8,u16,u32,Task *,u16);
extern Task *positioned(int,int,int,unsigned,int,void *,const void *,Task *);
extern Task *poll_position(Task *);
extern Task *poll(Task *);
u32 RemainingBand43_0010A2A4(Task *task,Event *event,Work *work)
{
 switch(event->state) {
 case 0:
  work->mode=event->mode;work->record=event->record;
  work->actor=project(work->record,&work->x,&work->y,0);
  break;
 case 1:break;
 case 256: {
  unsigned bit;
  register unsigned flags __asm__("r3");
  register void *record __asm__("r0");
  register const void *sequence __asm__("r1");
  work->positioned=positioned(work->x,work->y,0,1,3,work->opaque16,(const void *)0x083a1ad4,task);
  bit=work->mode&1;flags=2;if(bit)flags=4;
  record=work->record;sequence=(const void *)0x083a1b1c;
  __asm__("" : "+r"(record), "+r"(sequence), "+r"(flags));
  flags|=8;
  work->effect=create(record,sequence,12,30,flags,task,30);
  event->state++;break;
 }
 case 257:
  work->positioned=poll_position(work->positioned);
  if(work->positioned==0) {
   work->effect=poll(work->effect);
   if(work->effect==0)event->state=2;
  }
  break;
 }
 return 0;
}
__asm__(".global project\n.thumb_set project,0x080dd749\n.global create\n.thumb_set create,0x080dcfe5\n.global positioned\n.thumb_set positioned,0x080d6099\n.global poll_position\n.thumb_set poll_position,0x080d6135\n.global poll\n.thumb_set poll,0x080dba5d");
