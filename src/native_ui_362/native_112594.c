typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {u16 value,opaque[5];} Curve;
typedef struct {u16 phase,pad[9],x,y;} Event;
typedef struct {u16 counter,pad[2],x,y,pad10;void *object;Curve scroll,jitter;void *aux;} SequenceWork;
extern void InitCurve(Curve *,s32,s32,u32) __asm__("0x080E0608");
extern void TickCurve(Curve *) __asm__("0x080E064C");
extern u32 CurveDone(Curve *) __asm__("0x080E0690");
extern void SetupLayer(u32,u32,u32,s32,s32,void *,void *) __asm__("0x080D74E0");
extern u32 LayerMask(u32) __asm__("0x080035A8");
extern void SetLayerY(s32,u32) __asm__("0x08003558");
extern void *CreateAux(const void *,u32,u32,u32,void *) __asm__("0x080DFD8C");
extern void *CreateObject(const void *,u32,s32,s32,u32,u32,u32,u32) __asm__("0x080D5CC0");
extern void SetPosition(void *,s32,s32,u32) __asm__("0x080107D4");
extern void DestroyObject(void *) __asm__("0x08011428");
u32 RemainingBand43_00112594(void *parent,Event *event,SequenceWork *work)
{
    switch(event->phase) {
    case 0: {
        u32 mask;
        register u32 combined __asm__("r1");
        work->x=event->x;
        work->y=event->y;
        InitCurve(&work->scroll,224,106,60);
        SetupLayer(1,2,1,(s16)(u16)(work->x-120),(s16)(u16)(work->y-work->scroll.value),(void *)0x06008000,(void *)0x06007000);
        mask=LayerMask(1);
        combined=*(u16 *)0x03000940|mask;
        __asm__("" : "+r" (combined));
        *(u16 *)0x03000940=combined;
        work->aux=CreateAux((const void *)0x083A33D4,1,4,0,parent);
        work->counter=52;
        break;
    }
    case 1:
        break;
    case 256: {
        u16 remaining;
        if(!(u8)CurveDone(&work->scroll)) {
            TickCurve(&work->scroll);
            SetLayerY((s16)(u16)(work->y-work->scroll.value),1);
        }
        remaining=--work->counter;
        if(!remaining) {
            InitCurve(&work->jitter,12,104,8);
            work->object=CreateObject((const void *)0x08504D8C,3,120,(s16)work->jitter.value,779,8,remaining,remaining);
            ++event->phase;
        }
        break;
    }
    case 257: {
        u32 bothDone=1;
        if(!(u8)CurveDone(&work->scroll)) {
            TickCurve(&work->scroll);
            SetLayerY((s16)(u16)(work->y-work->scroll.value),1);
            bothDone=0;
        }
        if(!(u8)CurveDone(&work->jitter)) {
            u32 phase;
            u16 y;
            TickCurve(&work->jitter);
            phase=work->counter&3;
            y=work->jitter.value;
            if(phase==1) y=(((u32)y<<16)+0x00020000U)>>16;
            else if(phase==3) y=(((u32)y<<16)+0xFFFE0000U)>>16;
            ++work->counter;
            SetPosition(work->object,({u32 x=120;__asm__("" : "+r" (x));x;}),(s16)y,0);
            bothDone=0;
        }
        if(bothDone) {
            DestroyObject(work->object);
            work->object=0;
            event->phase=2;
        }
        break;
    }
    }
    return 0;
}
