typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {u16 value,opaque[5];} Curve;
typedef struct {u16 counter,padding;u32 unused;void *object;Curve curve;u32 tail;} ChildWork;
extern void InitCurve(Curve *,s32,s32,u32) __asm__("0x080E0608");
extern void TickCurve(Curve *) __asm__("0x080E064C");
extern void *CreateObject(const void *,u32,s32,s32,u32,u32,u32,u32) __asm__("0x080D5CC0");
extern void SetPosition(void *,s32,s32,u32) __asm__("0x080107D4");
extern void DestroyObject(void *) __asm__("0x08011428");
u32 RemainingBand43_00111C7C(void *unused,u16 *event,ChildWork *work)
{
    switch(*event) {
    case 0:
        work->counter=5;
        break;
    case 1:
        break;
    case 256: {
        u16 remaining=--work->counter;
        if(!remaining) {
            InitCurve(&work->curve,136,172,7);
            work->object=CreateObject((const void *)0x08504D8C,3,120,(s16)work->curve.value,779,8,remaining,remaining);
            ++*event;
        }
        break;
    }
    case 257: {
        u32 phase=work->counter&3;
        u16 y=work->curve.value;
        if(phase==1) y=((u32)y<<16)+0x00020000U>>16;
        else if(phase==3) y=((u32)y<<16)+0xFFFE0000U>>16;
        SetPosition(work->object,({u32 x=120; __asm__("" : "+r" (x)); x;}),(s16)y,0);
        TickCurve(&work->curve);
        if(work->counter<=7) ++work->counter;
        else {
            DestroyObject(work->object);
            work->object=0;
            *event=2;
        }
        break;
    }
    }
    return 0;
}
