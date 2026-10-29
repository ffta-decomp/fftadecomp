typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;};
struct Event {u16 phase,unknown2;void *record;};
struct Work {u16 unknown0;s16 x,y;u16 unknown6;void *record,*aux,*sequence;struct Ramp first,second;void *child1,*child2;};
typedef char WorkSize[sizeof(struct Work)==52?1:-1];
struct Shadow {u16 control;u8 unknown2[56];volatile u8 b58,b59,b60,b61;u8 b62;volatile u8 b63;volatile s8 b64;volatile u8 b65,b66,b67,b68;};
#define SHADOW ((struct Shadow *)0x03000940)
extern void ProjectRecord(void *,s16 *,s16 *);
extern u32 ReadLowMask(u32);
extern u32 ReadHighMask(u32);
extern void InitializeRamp(struct Ramp *,u16,u16,u16);
extern void AdvanceRamp(struct Ramp *);
extern u32 RampComplete(struct Ramp *);
extern void *CreateObject(u8,u8,u8,void *);
extern void SetChildFlag(void *,u32);
extern void ConfigureResource(const void *,u32,u32,u32,u32,u32);
extern void *CreateAux(const void *,void *);
extern void ConfigureAux(void *,u32,u32);
extern void *CreateSequence(const void *,void *);
extern void RefreshChild(void *);
extern void ApplyWindow(void *,s32,s32,u32,u32);
extern void *PollChild(void *);
extern void *PollAux(void *);
extern void *PollSequence(void *);
u32 AdvanceAuthoredInitialTarget(void *,struct Event *,struct Work *) asm("RemainingBand43_00116F98");
u32 AdvanceAuthoredInitialTarget(void *parent,struct Event *event,struct Work *work)
{
    switch(event->phase) {
    case 0:
        work->record=event->record;
        ProjectRecord(work->record,&work->x,&work->y);
        work->y-=8;
        break;
    case 256:
        SHADOW->b66=63&~ReadLowMask(3);
        SHADOW->b67=63;
        SHADOW->b68=63&~ReadLowMask(3);
        SHADOW->b59=0;SHADOW->b58=0;SHADOW->b63=0;SHADOW->b62=255;
        SHADOW->b61=0;SHADOW->b60=0;SHADOW->b65=0;SHADOW->b64=-1;
        SHADOW->control|=0x6000;
        InitializeRamp(&work->first,64,0,30);
        InitializeRamp(&work->second,48,0,30);
        work->child1=CreateObject(1,0,0,parent);
        work->child2=CreateObject(0,0,0,parent);
        SetChildFlag(work->child1,1);
        SetChildFlag(work->child2,1);
        ConfigureResource((const void *)0x088f46cc,1,3,0,0,0);
        work->aux=CreateAux((const void *)0x0894d69c,parent);
        ConfigureAux(work->aux,8,255);
        work->sequence=CreateSequence((const void *)0x0894c514,parent);
        ++event->phase;
        break;
    case 257: {
        struct Ramp *first=&work->first;
        struct Ramp *second;
        AdvanceRamp(first);
        second=&work->second;
        AdvanceRamp(second);
        RefreshChild(work->child1);
        RefreshChild(work->child2);
        ApplyWindow(work->child1,work->x,(s16)(work->y+2),work->first.value,(u16)((s16)work->first.value>>1));
        ApplyWindow(work->child2,work->x,work->y,work->second.value,(u16)((s16)work->second.value>>1));
        if((u8)RampComplete(first) && (u8)RampComplete(second)) {
            u32 mask;
            SHADOW->control&=0x9fff;
            mask=ReadHighMask(3);
            SHADOW->control&=~mask;
            ++event->phase;
        }
        break;
    }
    case 258:
        work->child1=PollChild(work->child1);
        if(work->child1)break;
        work->child2=PollChild(work->child2);
        if(work->child2)break;
        work->aux=PollAux(work->aux);
        if(work->aux)break;
        work->sequence=PollSequence(work->sequence);
        if(!work->sequence)event->phase=2;
        break;
    }
    return 0;
}
asm(".global ProjectRecord\n.thumb_set ProjectRecord,0x080dbdc9\n.global ReadLowMask\n.thumb_set ReadLowMask,0x080035d1\n.global ReadHighMask\n.thumb_set ReadHighMask,0x080035a9\n.global InitializeRamp\n.thumb_set InitializeRamp,0x080e0609\n.global AdvanceRamp\n.thumb_set AdvanceRamp,0x080e064d\n.global RampComplete\n.thumb_set RampComplete,0x080e0691\n.global CreateObject\n.thumb_set CreateObject,0x080dab85\n.global SetChildFlag\n.thumb_set SetChildFlag,0x080d9ba9\n.global ConfigureResource\n.thumb_set ConfigureResource,0x080d7221\n.global CreateAux\n.thumb_set CreateAux,0x080d3e9d\n.global ConfigureAux\n.thumb_set ConfigureAux,0x080d3f85\n.global CreateSequence\n.thumb_set CreateSequence,0x080d4705\n.global RefreshChild\n.thumb_set RefreshChild,0x080dadfd\n.global ApplyWindow\n.thumb_set ApplyWindow,0x080dac81\n.global PollChild\n.thumb_set PollChild,0x080d9b65\n.global PollAux\n.thumb_set PollAux,0x080d3f09\n.global PollSequence\n.thumb_set PollSequence,0x080d4775\n");
