typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct{u16 state,pad;void *actor1,*actor2,*record;u32 unused;u16 flag;}Event;
typedef struct{s16 timer;u8 flag,pad;s16 xs[60],ys[60];void *path,*actor1,*actor2,*record,*sprite,*sprites[3],*nodes[3],*coord,*sequence,*request;}Work;
extern void ActorPoint(void*,u16*,u16*,u16*);extern void Position(void*,u16*,u16*);extern void *Path(void**,u16*,u16*,u32,u32,u32,s16*,s16*,u32,void*);extern void *Sprite(const void*,u32,int,int,u32,u32,u32);extern void SetSprite(void*,u32);extern void *Sequence(const void*,void*);extern void StartPath(void*);extern void *Copy(void*,const void*,u32);extern void *PollPath(void*);extern void Destroy(void*);extern void *Coordinates(int,int,u32,u32,u32,void*,const void*,void*);extern void *Request(void*,const void*,u32,u32,u32,void*,u32);extern void *PollSequence(void*);extern u32 PollSprites(void**,u32);extern void *PollCoord(void*);extern void *Poll(void*);
u32 RemainingBand43_000FEBDC(void *task,Event *event,Work *work){struct{u16 z0,z1;u8 markers[3];u16 targetx,targety;u16 start[2],end[2];} local;
switch(event->state){
case 0:work->actor1=event->actor1;work->actor2=event->actor2;work->record=event->record;work->flag=event->flag;work->timer=62;break;
case 1:break;
case 256:
 ActorPoint(work->actor1,&local.start[0],&local.start[1],&local.z0);ActorPoint(work->actor2,&local.end[0],&local.end[1],&local.z1);
 work->path=Path(&work->sprite,local.start,local.end,-28,-28,60,work->xs,work->ys,0,task);event->state++;break;
case 257:
 {int remaining=(s16)--work->timer;if(remaining)break;
 work->sprite=Sprite((const void*)0x084fba40,2,work->xs[0],work->ys[0],929,6,0);SetSprite(work->sprite,1);
 work->sequence=Sequence((const void*)0x08949adc,task);StartPath(work->path);work->timer=remaining;event->state++;}break;
case 258:
 {register u8 *marker asm("r4")=local.markers;u8 i;asm("" : "+r"(marker));Copy(marker,(const void*)0x08149dcc,3);for(i=0;i<3;i++){if(work->timer==marker[i])work->sprites[i]=Sprite((const void*)0x084fba40,3,work->xs[work->timer],work->ys[work->timer],929,6,0);}}
 work->timer++;
 work->path=PollPath(work->path);if(work->path)break;
 {void *finished=work->path;Destroy(work->sprite);work->sprite=finished;}
 {register void *actor asm("r0")=work->actor2;u16 *x=&local.targetx,*y=&local.targety;asm("" : "+r"(actor),"+r"(x),"+r"(y));Position(actor,x,y);
 work->coord=Coordinates((s16)*x,(s16)*y,0,1,3,work->nodes,(const void*)0x0839e0fc,task);}
 if(work->flag==1)work->request=Request(work->record,(const void*)0x0839e194,12,30,4,task,30);
 event->state++;break;
case 259:
 work->sequence=PollSequence(work->sequence);if(work->sequence)break;
 if(!(u8)PollSprites(work->sprites,3))break;
 work->coord=PollCoord(work->coord);if(work->coord)break;
 work->request=Poll(work->request);if(work->request)break;event->state=2;break;
}return 0;}
asm(".global ActorPoint\n.thumb_set ActorPoint,0x80dbda1\n.global Position\n.thumb_set Position,0x80dbdc9\n.global Path\n.thumb_set Path,0x80d62cd\n.global Sprite\n.thumb_set Sprite,0x80d5dd5\n.global SetSprite\n.thumb_set SetSprite,0x801121d\n.global Sequence\n.thumb_set Sequence,0x80d4705\n.global StartPath\n.thumb_set StartPath,0x80d5c21\n.global Copy\n.thumb_set Copy,0x81443fd\n.global PollPath\n.thumb_set PollPath,0x80d6531\n.global Destroy\n.thumb_set Destroy,0x8011429\n.global Coordinates\n.thumb_set Coordinates,0x80d6099\n.global Request\n.thumb_set Request,0x80dcfe5\n.global PollSequence\n.thumb_set PollSequence,0x80d4775\n.global PollSprites\n.thumb_set PollSprites,0x80d5f25\n.global PollCoord\n.thumb_set PollCoord,0x80d6135\n.global Poll\n.thumb_set Poll,0x80dba5d\n");
