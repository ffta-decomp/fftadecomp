typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct{u16 state,pad;void *record;u8 unused[12];u16 flags,variant;}Event;
typedef struct{u8 flags,variant;u16 x,y,pad;void *record,*actor,*raster,*nodes[3],*coord,*background,*sequences[2],*request,*extra;}Work;
extern void *ActorPosition(void*,u16*,u16*,u16*);extern void LoadBackground(const void*,u32,u32,u32,u32);extern void PlaceBackground(u32,u32,u32,int,int);extern void *CreateRaster(u32,const void*,u32,u32);extern void SetRaster(void*,u32);extern u32 LayerMask(u32);extern void *Coordinates(int,int,u32,u32,u32,void*,const void*,void*);extern void *Background(const void*,void*);extern void *Sequence(const void*,void*);extern void SetSequence(void*,u32);extern void *Request(void*,const void*,u32,u32,u32,void*,u32);extern void *Extra(const void*,u32,u32,u32,void*);extern void *PollBackground(void*);extern void StopSequences(void*,u32);extern void StopRaster(void*,u32);extern void *PollCoord(void*);extern void *Poll(void*);
u32 AdvanceAuthoredVariantBackgroundSequence(void*,Event*,Work*) asm("RemainingBand43_000E6714");
u32 AdvanceAuthoredVariantBackgroundSequence(void *task,Event *event,Work *work){u32 flags,extra_flags;
switch(event->state){
case 0:
 work->flags=event->flags;work->variant=event->variant;work->record=event->record;work->actor=ActorPosition(work->record,&work->x,&work->y,0);
 if(work->variant==0)LoadBackground((const void*)0x088ea31c,6,0,0,1);else LoadBackground((const void*)0x088ea31c,6,0,2,1);break;
case 1:break;
case 256:
 PlaceBackground(0,2,0,(s16)work->x,(s16)work->y);
 work->raster=CreateRaster(0,(const void*)0x088edb7c,966,6);SetRaster(work->raster,1);
 {u32 mask=LayerMask(2);register u32 display asm("r1")=*(u16*)0x03000940;asm("" : "+r"(display));display|=mask;*(u16*)0x03000940=display;}
 {int x=(s16)work->x,y=(s16)work->y;const u8 *counts;{register const u8 *phase asm("r3")=(const u8*)0x083974d0;asm("" : "+r"(x),"+r"(y),"+r"(phase));counts=phase;}work->coord=Coordinates(x,y,0,1,({register u32 count_address asm("r2")=work->variant;
 /* One original2B commuted address ADD. Both the LOW8 index and ROM
    table base are actual initialized inputs; C performs the byte read. */
 asm("add %0, %0, %1" : "+r"(count_address) : "l"(counts) : "cc");
 *(const u8 *)count_address;}),work->nodes,({register const void **base asm("r3")=(const void**)0x083974c8;asm("" : "+r"(base));base[work->variant];}),task);}
 work->background=Background((const void*)0x0894d7bc,task);
 work->sequences[0]=Sequence((const void*)0x08949554,task);work->sequences[1]=Sequence((const void*)0x08949564,task);
 SetSequence(work->sequences[0],1);SetSequence(work->sequences[1],1);
 if(work->flags&1)flags=4;else flags=2;
 work->request=Request(work->record,(const char*)0x083974d4+20*work->variant,12,50,flags,task,50);
 if(work->flags&1)extra_flags=16;else extra_flags=8;
 work->extra=Extra(({register const void **base asm("r1")=(const void**)0x0839750c;asm("" : "+r"(base));base[work->variant];}),1,extra_flags|4,0,task);event->state++;break;
case 257:
 {u32 old_nonzero=((0u-(u32)work->background)|(u32)work->background)>>31;void *value=PollBackground(work->background);work->background=value;
 if(value)break;
 if(old_nonzero){StopSequences(work->sequences,2);StopRaster(work->raster,0);work->raster=value;{u32 mask=LayerMask(2);*(u16*)0x03000940&=~mask;}}}
 work->coord=PollCoord(work->coord);if(work->coord)break;event->state++;break;
case 258:work->request=Poll(work->request);if(work->request)break;event->state=2;break;
}return 0;
}
asm(".global ActorPosition\n.thumb_set ActorPosition,0x80dd749\n.global LoadBackground\n.thumb_set LoadBackground,0x80d45d1\n.global PlaceBackground\n.thumb_set PlaceBackground,0x80d49fd\n.global CreateRaster\n.thumb_set CreateRaster,0x80d4b65\n.global SetRaster\n.thumb_set SetRaster,0x800bda5\n.global LayerMask\n.thumb_set LayerMask,0x80035a9\n.global Coordinates\n.thumb_set Coordinates,0x80d6099\n.global Background\n.thumb_set Background,0x80d3e9d\n.global Sequence\n.thumb_set Sequence,0x80d4705\n.global SetSequence\n.thumb_set SetSequence,0x80d47a1\n.global Request\n.thumb_set Request,0x80dcfe5\n.global Extra\n.thumb_set Extra,0x80dfd8d\n.global PollBackground\n.thumb_set PollBackground,0x80d3f09\n.global StopSequences\n.thumb_set StopSequences,0x80d4939\n.global StopRaster\n.thumb_set StopRaster,0x80d4d15\n.global PollCoord\n.thumb_set PollCoord,0x80d6135\n.global Poll\n.thumb_set Poll,0x80dba5d\n");
