typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct {u16 state,pad;void *record;u32 untouched[3];u16 delay,flags;} Event;
typedef struct {void *record;u16 timer,flags;} Work;
extern void Cancel(void*,u8);extern void *Get(void*);extern void Update(void*,u16);extern u32 Pending(void*);extern u32 Start(void*);extern u32 Moving(void);
u32 RemainingBand43_000DF080(u32 ignored,Event *event,Work *work){u32 timer,result;
 switch(event->state){
 case 0:work->record=event->record;work->timer=event->delay+1;work->flags=event->flags;break;
 case 1:break;
 case 256:timer=work->timer;if(timer){--timer;work->timer=timer;if((u16)timer)break;if(work->flags&2)Cancel(work->record,0);if(work->flags&4)Update(Get(work->record),8);}
 result=(u8)Pending(work->record);if(result)break;work->timer=result;
 if((work->flags&1)&&(u8)Start(Get(work->record))&&(work->flags&8))work->timer=16;
 case 257:if((u8)Moving())break;timer=work->timer;if(timer){--timer;work->timer=timer;if((u16)timer)break;}event->state=2;break;
 }
 return 0;
}
asm(".global Cancel\n.thumb_set Cancel,0x80dd631\n.global Get\n.thumb_set Get,0x80dd4c5\n.global Update\n.thumb_set Update,0x80de10d\n.global Pending\n.thumb_set Pending,0x80dd651\n.global Start\n.thumb_set Start,0x80db839\n.global Moving\n.thumb_set Moving,0x80d8b4d\n");
