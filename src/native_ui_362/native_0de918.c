typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 reserved[12];u16 delay,cue;} Event;
typedef struct {u16 count,delay;u8 cue,pad[3];void *record,*child;} Work;
extern u32 Predicate(void*) __asm__("0x080DD730");
extern void *Create(void*,const void*,u32,u32,void*) __asm__("0x080DE0E0");
extern void IndexedCue(u32,u32) __asm__("0x08141570");
extern void DefaultCue(u32) __asm__("0x08141520");
extern void *Poll(void*) __asm__("0x080DBA5C");
u32 RemainingBand43_000DE918(void *parent,Event *event,Work *work)
{
 switch(event->phase){
 case 0:work->record=event->record;work->delay=event->delay+1;work->cue=event->cue;break;
 case 1:break;
 case 256:
 if(--work->delay)break;
 if(!(u8)Predicate(work->record))work->child=Create(work->record,(void*)0x083955F8,2,0,parent);
 work->count=8;++event->phase;break;
 case 257:
 if(work->count){
  if(--work->count==0 && work->cue!=255){u32 index=0;if(work->cue)index=work->cue;if(index)IndexedCue(index,275);else DefaultCue(275);}
  break;
 }
 work->child=Poll(work->child);if(work->child)break;event->phase=2;break;
 }return 0;
}
