typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Task Task;
typedef struct {u16 state,unused2;void *record;u8 unused8[12];u16 mode;} Event;
typedef struct {u8 mode,unused1;u16 x,y;u8 unused6[2];void *record,*actor;Task *child;} Work;
extern void *project(void *,u16 *,u16 *,u16 *);
extern Task *create(void *,const void *,u8,u16,u32,Task *,u16);
extern Task *poll(Task *);
u32 RemainingBand43_000F6490(Task *task,Event *event,Work *work)
{
 switch(event->state) {
 case 0:
  work->mode=event->mode;
  work->record=event->record;
  work->actor=project(work->record,&work->x,&work->y,0);
  break;
 case 1: break;
 case 256: {
  unsigned bit=work->mode&1;
  register unsigned flags __asm__("r3")=2;
  register void *record __asm__("r0");
  register const void *sequence __asm__("r1");
  if(bit)flags=4;
  record=work->record;sequence=(const void *)0x0839b8a8;
  __asm__("" : "+r"(record), "+r"(sequence), "+r"(flags));
  flags|=8;
  work->child=create(record,sequence,12,0,flags,task,0);
  event->state++;
  break;
 }
 case 257:
  work->child=poll(work->child);
  if(work->child==0)event->state=2;
  break;
 }
 __asm__ volatile ("" : "+r" (task));
 return 0;
}
__asm__(".global project\n.thumb_set project,0x080dd749\n.global create\n.thumb_set create,0x080dcfe5\n.global poll\n.thumb_set poll,0x080dba5d");
