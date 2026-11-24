typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct{u16 state,pad;void *record;u8 unused[12];u16 flags;}Event;
typedef struct{u8 flags,pad;u16 timer,x,y;void *record,*actor,*node,*coord,*raster,*sequence,*background,*request,*extra;}Work;
extern void *ActorPosition(void*,u16*,u16*,u16*);extern u32 ActorFlag(void*);extern void *Coordinates(int,int,u32,u32,u32,void*,const void*,void*);extern void *Request(void*,const void*,u32,u32,u32,void*,u32);extern void *Extra(const void*,u32,u32,u32,void*);extern void LoadBackground(const void*,u32,u32,u32,u32);extern void PlaceBackground(u32,u32,u32,int,int);extern void *CreateRaster(u32,const void*,u32,u32);extern u32 LayerMask(u32);extern void *Sequence(const void*,void*);extern void *Background(const void*,void*);extern void *PollRaster(void*,u32);extern void StopSequence(void*);extern void *PollCoord(void*);extern void *PollBackground(void*);extern void *Poll(void*);
u32 RemainingBand43_000F03D0(void *task,Event *event,Work *work){u32 flags;
switch(event->state){
case 0:
 work->flags=event->flags;work->record=event->record;work->actor=ActorPosition(work->record,&work->x,&work->y,0);
 if((u8)ActorFlag(work->actor))work->y-=8;break;
case 1:break;
case 256:
 work->coord=Coordinates((s16)work->x,(s16)work->y,0,1,1,&work->node,(const void*)0x08399d7c,task);
 if(work->flags&1)flags=4;else flags=2;
 work->request=Request(work->record,(const void*)0x08399d94,12,60,flags,task,60);
 if(work->flags&1)flags=16;else flags=8;
 work->extra=Extra((const void*)0x08399da8,1,flags|4,0,task);work->timer=30;event->state++;break;
case 257:
 if(--work->timer)break;
 LoadBackground((const void*)0x088ea4e0,6,0,0,1);
 PlaceBackground(0,2,0,(s16)work->x,(s16)work->y);
 work->raster=CreateRaster(0,(const void*)0x088edf1c,977,6);
 {u32 mask=LayerMask(2);register u32 display asm("r1")=*(u16*)0x03000940;asm("" : "+r"(display));display|=mask;*(u16*)0x03000940=display;}
 work->sequence=Sequence((const void*)0x08949750,task);
 work->background=Background((const void*)0x0894d6a8,task);event->state++;break;
case 258:
 {u32 old_nonzero=((0u-(u32)work->raster)|(u32)work->raster)>>31;void *value=PollRaster(work->raster,0);work->raster=value;
 if(old_nonzero){if(value)break;{u32 mask=LayerMask(2);*(u16*)0x03000940&=~mask;}StopSequence(work->sequence);work->sequence=value;}}
 if(work->raster)break;
 work->coord=PollCoord(work->coord);if(work->coord)break;
 work->background=PollBackground(work->background);if(work->background)break;
 work->request=Poll(work->request);if(work->request)break;
 event->state=2;break;
}return 0;
}
asm(".global ActorPosition\n.thumb_set ActorPosition,0x80dd749\n.global ActorFlag\n.thumb_set ActorFlag,0x80dd73d\n.global Coordinates\n.thumb_set Coordinates,0x80d6099\n.global Request\n.thumb_set Request,0x80dcfe5\n.global Extra\n.thumb_set Extra,0x80dfd8d\n.global LoadBackground\n.thumb_set LoadBackground,0x80d45d1\n.global PlaceBackground\n.thumb_set PlaceBackground,0x80d49fd\n.global CreateRaster\n.thumb_set CreateRaster,0x80d4b65\n.global LayerMask\n.thumb_set LayerMask,0x80035a9\n.global Sequence\n.thumb_set Sequence,0x80d4705\n.global Background\n.thumb_set Background,0x80d3e9d\n.global PollRaster\n.thumb_set PollRaster,0x80d4d2d\n.global StopSequence\n.thumb_set StopSequence,0x80d4769\n.global PollCoord\n.thumb_set PollCoord,0x80d6135\n.global PollBackground\n.thumb_set PollBackground,0x80d3f09\n.global Poll\n.thumb_set Poll,0x80dba5d\n");
