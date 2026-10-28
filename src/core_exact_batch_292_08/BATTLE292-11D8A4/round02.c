typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct{u16 state,pad;void *actor;void **reference;}Event;
typedef struct{u16 counter,x,y,pad;void *actor;void **reference;void *coord1,*node1,*coord2,*node2,*coord3,*nodes[7],*background,*sequence,*extra;}Work;
extern void Position(void*,u16*,u16*);extern void Background(const void*,u32,u32,int,int,u32);extern void *CreateBackground(const void*,void*);extern void *Coordinates(int,int,u32,u32,u32,void*,const void*,void*);extern void *Extra(const void*,u32,u32,u32,void*);extern u32 Signal(void*);extern void ClearSignal(void*);extern void *PollCoord(void*);extern void *Sequence(const void*,void*);extern void *PollBackground(void*);extern u32 LayerMask(u32);extern void ClearBackground(void);extern void *Poll(void*);extern void *PollSequence(void*);
u32 RemainingBand43_0011D8A4(void *task,Event *event,Work *work){
switch(event->state){
case 0:work->actor=event->actor;work->reference=event->reference;Position(work->actor,&work->x,&work->y);break;
case 1:break;
case 256:
 Background((const void*)0x088f53dc,0,2,(s16)work->x,(s16)(work->y-24),0);
 work->background=CreateBackground((const void*)0x0894ddbc,task);
 work->coord1=Coordinates((s16)work->x,(s16)(work->y-36),0,1,1,&work->node1,(const void*)0x083a6fd4,task);
 work->extra=Extra((const void*)0x083a70bc,1,4,0,task);event->state++;break;
case 257:
 if(!(u8)Signal(*work->reference))break;
 work->coord1=PollCoord(work->coord1);if(work->coord1)break;
 ClearSignal(*work->reference);
 work->coord2=Coordinates((s16)work->x,(s16)(work->y-24),0,1,1,&work->node2,(const void*)0x083a6fec,task);
 work->sequence=Sequence((const void*)0x0894ac90,task);
 work->extra=Extra((const void*)0x083a70c4,1,4,0,task);event->state++;break;
case 258:
 work->coord2=PollCoord(work->coord2);if(work->coord2)break;
 work->coord3=Coordinates((s16)work->x,(s16)(work->y-24),0,1,7,work->nodes,(const void*)0x083a7004,task);event->state++;break;
case 259:
 work->background=PollBackground(work->background);if(work->background)break;
 work->coord3=PollCoord(work->coord3);if(work->coord3)break;
 {u32 mask=LayerMask(2);*(u16*)0x03000940&=~mask;}
 ClearBackground();
 {void *value=Poll(*work->reference);*work->reference=value;if(value)break;}
 work->sequence=PollSequence(work->sequence);if(work->sequence)break;
 event->state=2;break;
}return 0;
}
asm(".global Position\n.thumb_set Position,0x80dbdc9\n.global Background\n.thumb_set Background,0x80d7221\n.global CreateBackground\n.thumb_set CreateBackground,0x80d3e9d\n.global Coordinates\n.thumb_set Coordinates,0x80d6099\n.global Extra\n.thumb_set Extra,0x80dfd8d\n.global Signal\n.thumb_set Signal,0x80dfad1\n.global ClearSignal\n.thumb_set ClearSignal,0x80dfaed\n.global PollCoord\n.thumb_set PollCoord,0x80d6135\n.global Sequence\n.thumb_set Sequence,0x80d4705\n.global PollBackground\n.thumb_set PollBackground,0x80d3f09\n.global LayerMask\n.thumb_set LayerMask,0x80035a9\n.global ClearBackground\n.thumb_set ClearBackground,0x80d4021\n.global Poll\n.thumb_set Poll,0x80dba5d\n.global PollSequence\n.thumb_set PollSequence,0x80d4775\n");
