typedef unsigned char u8;
typedef unsigned short u16;
typedef struct {void *actor;u8 a,b,kind,control;unsigned unknown8;void *bufferA,*bufferB;} Init;
typedef struct {unsigned unknown0;Init *data;unsigned unknown8[3];u16 mode,layer;unsigned unknown24;} Event;
extern void *CreateTask(void*,unsigned,const void*,void*);
extern void ActorEffectCallback(void);
void *CreateActorLayer3Effect(void *actor,void *bufferA,void *bufferB,u8 mode,void *parent)
{
 Event event;
 Init init;
 init.actor=actor;
 init.a=0;
 init.b=0;
 init.kind=9;
 init.bufferA=bufferA;
 init.bufferB=bufferB;
 init.control=0;
 event.mode=mode;
 event.layer=3;
 event.data=&init;
 return CreateTask(ActorEffectCallback,44,&event,parent);
}
__asm__(".global CreateTask\n.thumb_set CreateTask,0x08005b6d\n.global ActorEffectCallback\n.thumb_set ActorEffectCallback,0x080db541\n");
