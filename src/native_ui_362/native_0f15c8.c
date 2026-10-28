typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct {u16 phase,pad; void *record;} Event;
typedef struct {s16 x,y;u8 timer,pad[3];void *blend,*scriptA,*scriptB,*window,*record,*aux;} Work;
typedef struct {u16 control;u8 pad[56];volatile u8 b58,b59,b60,b61;u8 b62;volatile u8 b63,b64,b65,b66,b67,b68;u8 pad69[5];volatile u8 b74;} Shadow;
extern void *CreateBlend(const void *,void *) __asm__("0x080D3E9C");
extern void *CreateWindow(int,int,int,void *) __asm__("0x080DAD94");
extern void *CreateScript(const void *,void *) __asm__("0x080D4704");
extern void *CreateAux(const void *,int,int,int,void *) __asm__("0x080DFD8C");
extern void *PollBlend(void *) __asm__("0x080D3F08");
extern void *PollScript(void *) __asm__("0x080D4774");
extern void *PollWindow(void *) __asm__("0x080DAE44");
extern Shadow DisplayShadow __asm__("0x03000940");
u32 RemainingBand43_000F15C8(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 0: work->record=event->record; work->x=104;work->y=40;break;
 case 256: {
 Shadow *shadow;
 work->blend=CreateBlend((void *)0x0894D97C,parent);
 work->window=CreateWindow(work->x,work->y,1,parent);
 shadow=&DisplayShadow;
 shadow->b66=63;
 shadow->b67=63;
 shadow->b68=31;
 shadow->b59=0;
 shadow->b58=0;
 shadow->b63=0;
 shadow->b62=255;
 shadow->b61=0;
 shadow->b60=0;
 shadow->b65=0;
 shadow->b64=-1;
 shadow->control|=0x6000;
 work->scriptA=CreateScript((void *)0x0894B504,parent);
 work->scriptB=CreateScript((void *)0x0894B268,parent);
 work->aux=CreateAux((void *)0x0839A56C,1,4,0,parent);
 work->timer=28;++event->phase;break;
 }
 case 257:
 if(work->timer) {
 Shadow *shadow;
 --work->timer;
 if(work->timer) break;
 shadow=&DisplayShadow;
 shadow->control&=0x9FFF;
 shadow->b74=0;
 }
 work->blend=PollBlend(work->blend);if(work->blend)break;
 work->scriptA=PollScript(work->scriptA);if(work->scriptA)break;
 work->scriptB=PollScript(work->scriptB);if(work->scriptB)break;
 work->window=PollWindow(work->window);if(work->window)break;
 ++event->phase;break;
 case 258:event->phase=2;break;
 }
 return 0;
}
