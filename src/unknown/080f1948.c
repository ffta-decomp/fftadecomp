typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 phase,pad;void *record;} Event;
typedef struct {s16 current;u8 rest[10];} Ramp;
typedef struct {s16 x,y;u8 counter,pad[3];void *model,*blend,*scriptA,*scriptB,*record,*aux;Ramp ramp;} Work;
typedef struct {s32 originX,originY;s16 x,y;u16 scaleX,scaleY,angle,pad;} AffineInput;
typedef struct {s16 values[8];} AffineOutput;
extern void Setup(int,int,int,int,int) __asm__("0x080D49FC");
extern void Layer(int,int,int) __asm__("0x0800BC90");
extern void *Model(int,const void*,int,int) __asm__("0x080D4B64");
extern void Enable(int) __asm__("0x08003620");
extern u32 Mask(u32) __asm__("0x080035A8");
extern void *Blend(const void*,void*) __asm__("0x080D3E9C");
extern void *Script(const void*,void*) __asm__("0x080D4704");
extern void RampInit(Ramp*,int,int,int) __asm__("0x080E0608");
extern void RampStep(Ramp*) __asm__("0x080E064C");
extern u32 RampDone(Ramp*) __asm__("0x080E0690");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void Affine(const AffineInput*,AffineOutput*,int) __asm__("0x08141864");
extern void Submit(const AffineOutput*,int) __asm__("0x080032F8");
extern void *PollBlend(void*) __asm__("0x080D3F08");
extern void *PollScript(void*) __asm__("0x080D4774");
extern void *PollModel(void*,int) __asm__("0x080D4D2C");
extern const u16 AffineScaleTable[] __asm__("0x0839A50C");
u32 RemainingBand43_000F1948(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 0:work->record=event->record;work->x=120;work->y=40;break;
 case 256:
 Setup(0,2,1,work->x,work->y);Layer(0,0,2);
 work->model=Model(0,(void*)0x088F104C,186,6);
 Enable(1);{u32 mask=Mask(2);register u32 merged __asm__("r1")=*(u16*)0x03000940|mask;__asm__("" : "+r"(merged));*(u16*)0x03000940=merged;}
 work->blend=Blend((void*)0x0894DB48,parent);
 work->scriptA=Script((void*)0x089492DC,parent);
 work->scriptB=Script((void*)0x0894B268,parent);
 RampInit(&work->ramp,0,-128,28);
 work->aux=Aux((void*)0x0839A584,1,4,0,parent);
 ++event->phase;break;
 case 257:{AffineInput input;AffineOutput output;Ramp *ramp=&work->ramp;
 RampStep(ramp);
 input.originX=8192;input.originY=12288;
 input.x=work->x;input.y=work->y;
 input.scaleX=AffineScaleTable[work->counter];
 input.scaleY=AffineScaleTable[work->counter];
 input.angle=(u32)(u16)work->ramp.current<<8;
 Affine(&input,&output,1);Submit(&output,2);
 ++work->counter;
 if((u8)RampDone(ramp))++event->phase;
 break;}
 case 258:
 work->blend=PollBlend(work->blend);if(work->blend)break;
 work->scriptA=PollScript(work->scriptA);if(work->scriptA)break;
 work->scriptB=PollScript(work->scriptB);if(work->scriptB)break;
 work->model=PollModel(work->model,0);if(work->model)break;
 {u32 mask=Mask(2);*(u16*)0x03000940&=~mask;}
 Enable(0);event->phase=2;break;
 }
 return 0;
}
