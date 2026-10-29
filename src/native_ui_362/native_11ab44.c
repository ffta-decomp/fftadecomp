typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;};
struct Work {u16 delay;u8 unknown2[6];void *aux;struct Ramp first,second;void *child1,*child2;u32 unknown44;};
typedef char WorkSize[sizeof(struct Work)==48?1:-1];
struct Shadow {u16 control;u8 unknown2[56];volatile u8 b58,b59,b60,b61;u8 b62;volatile u8 b63;volatile s8 b64;volatile u8 b65,b66,b67,b68;u8 unknown69[5];volatile u8 b74;};
#define SHADOW ((struct Shadow *)0x03000940)
extern void InitializeRamp(struct Ramp *,u16,u16,u16);
extern void AdvanceRamp(struct Ramp *);
extern u32 RampComplete(struct Ramp *);
extern void *CreateObject(u8,u8,u8,void *);
extern void SetChildFlag(void *,u32);
extern void *CreateAux(const void *,void *);
extern void ApplyCoordinates(void *,u16,u16,u16);
extern void *PollChild(void *);
extern void *PollAux(void *);
u32 AdvanceAuthoredPairedWindow(void *,u16 *,struct Work *) asm("RemainingBand43_0011AB44");
u32 AdvanceAuthoredPairedWindow(void *parent,u16 *phase,struct Work *work)
{
    switch(*phase) {
    case 0:break;
    case 256:
        SHADOW->b66=31;SHADOW->b67=63;SHADOW->b68=31;
        SHADOW->b59=0;SHADOW->b58=0;SHADOW->b63=0;SHADOW->b62=255;
        SHADOW->b61=0;SHADOW->b60=0;SHADOW->b65=0;SHADOW->b64=-1;
        SHADOW->control|=0x6000;
        InitializeRamp(&work->first,0,160,36);
        InitializeRamp(&work->second,0,160,30);
        work->delay=6;
        work->child1=CreateObject(1,0,0,parent);
        work->child2=CreateObject(0,0,0,parent);
        SetChildFlag(work->child1,1);
        SetChildFlag(work->child2,1);
        work->aux=CreateAux((const void *)0x0894d97c,parent);
        ++*phase;
        break;
    case 257: {
        struct Ramp *first=&work->first;
        struct Ramp *second;
        u32 delay;
        register u32 loaded_delay asm("r0");
        AdvanceRamp(first);
        ApplyCoordinates(work->child1,120,64,work->first.value);
        loaded_delay=work->delay;
        asm("" : "+r"(loaded_delay));
        delay=loaded_delay;
        if(delay!=0) {work->delay=loaded_delay-1;break;}
        second=&work->second;
        AdvanceRamp(second);
        ApplyCoordinates(work->child2,120,64,work->second.value);
        if((u8)RampComplete(first) && (u8)RampComplete(second)) {
            SHADOW->b74=delay;
            SHADOW->control&=0x9fff;
            ++*phase;
        }
        break;
    }
    case 258:
        work->child1=PollChild(work->child1);
        if(work->child1)break;
        work->child2=PollChild(work->child2);
        if(work->child2)break;
        work->aux=PollAux(work->aux);
        if(!work->aux)*phase=2;
        break;
    }
    return 0;
}
asm(".global InitializeRamp\n.thumb_set InitializeRamp,0x080e0609\n.global AdvanceRamp\n.thumb_set AdvanceRamp,0x080e064d\n.global RampComplete\n.thumb_set RampComplete,0x080e0691\n.global CreateObject\n.thumb_set CreateObject,0x080dab85\n.global SetChildFlag\n.thumb_set SetChildFlag,0x080d9ba9\n.global CreateAux\n.thumb_set CreateAux,0x080d3e9d\n.global ApplyCoordinates\n.thumb_set ApplyCoordinates,0x080dac41\n.global PollChild\n.thumb_set PollChild,0x080d9b65\n.global PollAux\n.thumb_set PollAux,0x080d3f09\n");
