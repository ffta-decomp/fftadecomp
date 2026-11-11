typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {s16 x,y;} Point;
typedef struct {u16 phase,pad;const Point *source,*target;u8 *shared;u8 pad16[4];u16 kind;u8 hold,pad23;} Event;
typedef struct {u16 timer;u8 angle,kind,next,hold,pad6[2];u8 *shared;void *main,*children[3];u8 motionA[80],motionB[80];Point source,target;void *motion;} Work;
extern u32 Angle(int,int) __asm__("0x08141860");
extern u32 Root(u32) __asm__("0x08141898");
extern void Copy(void*,const void*,u32) __asm__("0x081443FC");
extern void *Sprite(const void*,int,int,int,int,int,void*) __asm__("0x080D5DD4");
extern void Mode(void*,int) __asm__("0x0801121C");
extern void Visible(void*,int) __asm__("0x0801115C");
extern void *Motion(void**,const Point*,const Point*,int,int,int,void*,void*,int,int,int,void*) __asm__("0x080D6334");
extern u32 Started(void*) __asm__("0x080D63C8");
extern u32 Complete(void*) __asm__("0x080D6478");
extern void Stop(void*) __asm__("0x080D5C20");
extern void Position(void*,u16*,u16*,u16*) __asm__("0x08011040");
extern void ChildMode(void*,int) __asm__("0x080111A8");
extern void Activate(void*) __asm__("0x08011198");
extern void *Tick(void*) __asm__("0x080D6530");
extern u32 PollAll(void**,int) __asm__("0x080D5F24");
extern void Destroy(void*) __asm__("0x08011428");
extern const u16 SpawnTimes[] __asm__("0x083A2920");
u32 RemainingBand43_0010D728(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 0:{register const Point *source __asm__("r3")=event->source;register const Point *target __asm__("r3");u8 *shared;__asm__("" : "+r"(source));
 work->source.x=source->x;{s16 y=source->y;register s16 *destination __asm__("r3")=&work->source.y;__asm__("" : "+r"(destination));*destination=y;}
 target=event->target;__asm__("" : "+r"(target));work->target.x=target->x;{s16 y=target->y;register s16 *destination __asm__("r3")=&work->target.y;__asm__("" : "+r"(destination));*destination=y;}
 shared=event->shared;work->shared=shared;work->kind=event->kind;work->hold=event->hold+1;*shared=0;break;}
 case 1:break;
 case 256:{void *created;
 register u32 dx __asm__("r0")=(u32)&work->target.x;
 register const s16 *sourceX __asm__("r5")=&work->source.x;
 register u32 scratchX __asm__("r1");
 register u32 dy __asm__("r1");
 register const s16 *sourceY __asm__("r6");
 register u32 scratchY __asm__("r2");
 __asm__("ldrh %0, [%0]\n\tldrh %1, [%2]\n\tsub %0, %0, %1" : "+l"(dx), "=&l"(scratchX) : "l"(sourceX) : "cc", "memory");
 dy=(u32)&work->target.y;sourceY=&work->source.y;
 __asm__("ldrh %0, [%0]\n\tldrh %1, [%2]\n\tsub %0, %0, %1" : "+l"(dy), "=&l"(scratchY) : "l"(sourceY) : "cc", "memory");
 work->angle=(u16)Angle((s16)dx,(s16)dy)>>12;
 created=Sprite((void*)0x0850873C,0,*sourceX,*sourceY,1021,6,0);work->main=created;
 Mode(created,-1);Visible(work->main,0);++event->phase;break;}
 case 257:{u8 a[3],b[3],c[3],d[3];u32 squareX,squareY;s32 distance;u16 duration;
 Copy(a,(void*)0x08149F24,3);Copy(b,(void*)0x08149F27,3);Copy(c,(void*)0x08149F2A,3);Copy(d,(void*)0x08149F2D,3);
 {u32 dx=(s32)work->target.x-work->source.x;squareX=dx*dx;}
 {u32 dy=(s32)work->target.y-work->source.y;squareY=dy*dy;}
 distance=(u16)Root((squareX+squareY)<<8)>>4;
 if(distance>b[work->kind])duration=c[work->kind];
 else duration=b[work->kind]+c[work->kind]-distance;
 if((s16)duration>d[work->kind])duration=d[work->kind];
 work->motion=Motion(&work->main,&work->source,&work->target,0,0,40,work->motionA,work->motionB,0,a[work->kind],(u8)duration,parent);
 ++event->phase;break;}
 case 258:
 if((u8)Started(work->motion)){*work->shared=1;++event->phase;}break;
 case 259:
 if(*work->shared==2){u8 remaining=--work->hold;
 if(!remaining){Visible(work->main,1);Stop(work->motion);work->timer=remaining;++event->phase;}}
 break;
 case 260:
 if(work->next<=2 && work->timer==SpawnTimes[work->next]) {u16 x,y,z;
 Position(work->main,&x,&y,&z);
 work->children[work->next]=Sprite((void*)0x0850873C,0,(s16)x,(s16)y,1021,6,0);
 ChildMode(work->children[work->next],1);Activate(work->children[work->next]);++work->next;
 }
 ++work->timer;
 if((u8)Complete(work->motion)){*work->shared=3;++event->phase;}break;
 case 261:{void *motion=Tick(work->motion);work->motion=motion;
 if(!motion&&(u8)PollAll(work->children,3)){Destroy(work->main);work->main=motion;*work->shared=4;event->phase=2;}
 break;}
 }
 return 0;
}
