typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {s16 x,y,z,pad;} Vec;
typedef union {Vec v;struct {u32 xy;u32 z:16,pad:16;} words;struct {u32 x:16,y:16,z:16,pad:16;} fields;} Target;
typedef struct {u16 phase,pad;void *record;u8 *shared;u8 reserved[8];u16 kind;} Event;
typedef struct {u16 unused,delay,id,pad6;u8 *shared;u8 kind,pad13[3];void *main,*children[3];u8 motionWork[80];u8 angle,childAngles[3];Vec source,target;void *record,*motion,*aux;} Work;
extern void *Nested(void*) __asm__("0x080DD47C");
extern void Source(void*,s16*,s16*,s16*) __asm__("0x080DBD5C");
extern void Destination(void*,s16*,s16*,s16*) __asm__("0x080D8B7C");
extern u32 Id(void*) __asm__("0x080DD488");
extern void *Create(int,int,int,int,int,void*,int,void*) __asm__("0x080D5FD8");
extern void Enable(void*,int) __asm__("0x08010884");
extern void Visible(void*,int) __asm__("0x0801115C");
extern void FlagA(void*,int) __asm__("0x080110F8");
extern void FlagB(void*,int) __asm__("0x080112E8");
extern void **SpriteInfo(void*) __asm__("0x08010FEC");
extern void *Child(void*,int,int,int,int,int,int,int,int,int) __asm__("0x08011348");
extern void ChildMode(void*,int) __asm__("0x080111A8");
extern void *Motion(void**,const void*,const void*,int,int,void*,int,int,void*) __asm__("0x080D6284");
extern u32 Started(void*) __asm__("0x080D63C8");
extern void Attach(void*,void**,int) __asm__("0x080D659C");
extern void Stop(void*) __asm__("0x080D5C20");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void Transform(void*,int,int,int) __asm__("0x080112CC");
extern void *Tick(void*) __asm__("0x080D6530");
extern void UpdateRecord(void*) __asm__("0x080D8CD4");
extern void Position(void*,int,int,int) __asm__("0x080107D4");
extern u32 Busy(void) __asm__("0x080D8B4C");
extern u32 Complete(void*) __asm__("0x080D6478");
extern void Destroy(void*) __asm__("0x08011428");
extern void DestroyChildren(void**,int) __asm__("0x080D5F74");
extern const u16 InitialAngles[] __asm__("0x0839EB58");
extern u16 ReturnAngles[] __asm__("0x0839EB5E");
u32 RemainingBand43_00100EF0(void *node,Event *event,Work *work)
{
 switch(event->phase){
 case 0:
 work->record=event->record;work->shared=event->shared;work->kind=event->kind;
 Source(Nested(work->record),&work->source.x,&work->source.y,&work->source.z);work->source.y+=48;
 Destination(work->record,&work->target.x,&work->target.y,&work->target.z);work->id=Id(work->record);*work->shared=0;break;
 case 1:break;
 case 256:{void **info;u8 i;
 work->main=Create(work->id,2,work->source.x,work->source.y,work->source.z,(void*)0x06017BA0,8,node);
 Enable(work->main,1);Visible(work->main,0);FlagA(work->main,1);FlagB(work->main,1);info=SpriteInfo(work->main);
 for(i=0;i<3;++i){work->children[i]=Child(*info,0,0,2,work->source.x,work->source.y,work->source.z,989,8,134);Visible(work->children[i],0);ChildMode(work->children[i],1);FlagA(work->children[i],1);FlagB(work->children[i],1);work->childAngles[i]=InitialAngles[i];}
 ++event->phase;break;}
 case 257:{Target target;
 target.fields.x=(u16)work->source.x;target.fields.y=(u16)work->source.y+208;target.fields.z=(u16)work->source.z;
 work->motion=Motion(&work->main,&work->source,&target,36,0,work->motionWork,0,0,node);++event->phase;break;}
 case 258:if((u8)Started(work->motion)){u8 i;for(i=0;i<3;++i)Attach(work->motion,&work->children[i],InitialAngles[i]);*work->shared=1;++event->phase;}break;
 case 259:if(*work->shared==2){Stop(work->motion);Visible(work->main,1);work->aux=Aux((void*)0x0839EB48,1,4,0,node);++event->phase;}break;
 case 260:{u8 i;void *motion;
 ++work->angle;Transform(work->main,256,256,(u16)(work->angle<<12));
 for(i=0;i<3;++i){++work->childAngles[i];Transform(work->children[i],256,256,(u16)(work->childAngles[i]<<12));}
 motion=Tick(work->motion);work->motion=motion;
 if(!motion){Target from;int duration;u16 y;
 UpdateRecord(work->record);*work->shared=3;
 from.fields.x=(u16)work->target.x;y=work->target.y;from.fields.y=y+208;from.fields.z=(u16)work->target.z;duration=24;
 if(work->kind){work->target.y=y+64;duration=20;}
 work->motion=Motion(&work->main,&from,&work->target,duration,0,work->motionWork,0,0,node);
 Position(work->main,from.v.x,from.v.y,from.v.z);work->delay=30;++event->phase;}
 break;}
 case 261:
 if(work->delay && --work->delay)break;
 {u8 busy=(u8)Busy();if(!busy&&(u8)Started(work->motion)){u8 i;work->angle=busy;Transform(work->main,256,256,0);
 for(i=0;i<3;++i){Attach(work->motion,&work->children[i],ReturnAngles[i]);work->childAngles[i]=ReturnAngles[i];Transform(work->children[i],256,256,(u16)(work->childAngles[i]<<12));}
 Stop(work->motion);Visible(work->main,1);work->aux=Aux((void*)0x0839EB48,1,4,0,node);++event->phase;}}
 break;
 case 262:{u8 i;void *motion;
 ++work->angle;Transform(work->main,256,256,(u16)(work->angle<<12));
 for(i=0;i<3;++i){++work->childAngles[i];Transform(work->children[i],256,256,(u16)(work->childAngles[i]<<12));}
 if(*work->shared!=4&&(u8)Complete(work->motion))*work->shared=4;
 motion=Tick(work->motion);work->motion=motion;
 if(!motion){Destroy(work->main);work->main=motion;DestroyChildren(work->children,3);++event->phase;}break;}
 case 263:event->phase=2;break;
 }return 0;
}
