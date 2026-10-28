typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 state,pad;void *record;} Event;
typedef struct {u16 timer,pad;void *record,*actor,*nodes[3],*coord,*actor_effect,*sequence,*extra;} Work;
extern void *Copy(void*,const void*,u32);extern void *Actor(void*);extern u32 Marked(void*);extern u32 Predicate(void*,u32);extern void Position(void*,u16*,u16*);
extern void *Coordinates(int,int,u32,u32,u32,void*,const void*,void*);extern void *Extra(const void*,u32,u32,u32,void*);extern void *Sequence(void*,const void*,u32,u32,u32,void*,u32);extern void *ActorEffect(void*,u32,u32,void*);extern void *PollCoord(void*);extern void *Poll(void*);
u32 RemainingBand43_000EF970(void *task,Event *event,Work *work){u16 values[2],x,y;u32 mode,result,index;
 switch(event->state){
 case 0:
 Copy(values,(const void*)0x08149d0c,4);
 work->record=event->record;work->actor=Actor(work->record);work->actor=Actor(work->record);
 mode=2;
 if((u8)Marked(work->record)){result=(u8)Predicate(work->record,0);mode=1;if(result)mode=0;}
 if(mode==1){
 Position(work->actor,&x,&y);
 work->coord=Coordinates((s16)x,(s16)y,0,1,3,work->nodes,(const void*)0x08399abc,task);
 work->extra=Extra((const void*)0x08399b34,1,4,180,task);
 }
 {register u32 selected asm("r3")=mode;asm("" : "+r"(selected));index=selected;}if(mode==2)index=0;
 work->sequence=Sequence(work->record,(const char*)0x08399b04+20*index,12,values[index],4,task,216);
 if(mode==0)work->actor_effect=ActorEffect(work->actor,2,224,task);
 work->timer=224;break;
 case 1:break;
 case 256:
 work->coord=PollCoord(work->coord);if(work->coord)break;
 work->actor_effect=Poll(work->actor_effect);if(work->actor_effect)break;
 work->sequence=Poll(work->sequence);if(work->sequence)break;
 event->state=2;break;
 }
 return 0;
}
asm(".global Copy\n.thumb_set Copy,0x81443fd\n.global Actor\n.thumb_set Actor,0x80dd4c5\n.global Marked\n.thumb_set Marked,0x80dd581\n.global Predicate\n.thumb_set Predicate,0x80dd671\n.global Position\n.thumb_set Position,0x80dbdc9\n.global Coordinates\n.thumb_set Coordinates,0x80d6099\n.global Extra\n.thumb_set Extra,0x80dfd8d\n.global Sequence\n.thumb_set Sequence,0x80dcfe5\n.global ActorEffect\n.thumb_set ActorEffect,0x80df8e9\n.global PollCoord\n.thumb_set PollCoord,0x80d6135\n.global Poll\n.thumb_set Poll,0x80dba5d\n");
