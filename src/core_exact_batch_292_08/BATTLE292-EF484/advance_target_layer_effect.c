typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Task;
struct Event {u16 state;u8 unused2[18];s16 x,y;u8 unused24[4];};
struct Interpolator {s16 value;u8 unknown2[10];};
struct Work {s16 x,y;u16 counter,unused6;struct Interpolator interpolation;void *resource;struct Task *auxiliary,*scanline,*sequence;};
typedef char WorkSize[sizeof(struct Work)==36?1:-1];
extern void ConfigureResource(u8,u8,u16,s16,s16);
extern void *CreateResource(u8,const void*,u16,u8);
extern u32 GetLayerMask(u8);
extern struct Task *CreateAuxiliary(const void*,struct Task*);
extern void BeginInterpolation(struct Interpolator*,s16,s16,u16);
extern struct Task *CreateStage(const void*,u8,u16,u16,struct Task*);
extern void AdvanceInterpolation(struct Interpolator*);
extern void SetLayerPosition(u8,s16,s16);
extern u32 InterpolationFinished(struct Interpolator*);
extern struct Task *PollAuxiliary(struct Task*);
extern struct Task *CreateScanlineTask(u8,u8,struct Task*);
extern u32 ReadResourcePosition(u8,u8);
extern u16 *GetScanlineBuffer(struct Task*);
extern void SetScanlineFlagFour(struct Task*,u8);
extern struct Task *PollScanline(struct Task*);
extern void *PollResource(void*,u8);
extern volatile u16 gDisplayControl;
extern const u8 gResource[],gAuxiliary[],gStageSequence[];
u32 AdvanceTargetLayerEffect(struct Task*,struct Event*,struct Work*) __asm__("RemainingBand43_000EF484");
u32 AdvanceTargetLayerEffect(struct Task *task,struct Event *event,struct Work *work)
{
    switch(event->state) {
    case 0: {
        u32 mask;
        register u32 control __asm__("r1");
        work->x=event->x;
        work->y=event->y;
        ConfigureResource(1,3,0,work->x,work->y);
        work->resource=CreateResource(1,gResource,930,6);
        mask=GetLayerMask(3);
        control=mask|gDisplayControl;
        /* The native OR result remains in R1 until its halfword store. */
        __asm__("" : "+r"(control));
        gDisplayControl=control;
        work->auxiliary=CreateAuxiliary(gAuxiliary,task);
        BeginInterpolation(&work->interpolation,work->y,(s16)(work->y-24),60);
        work->sequence=CreateStage(gStageSequence,1,4,0,task);
        break;
    }
    case 1:break;
    case 256:
        AdvanceInterpolation(&work->interpolation);
        SetLayerPosition(1,work->x,work->interpolation.value);
        if((u8)InterpolationFinished(&work->interpolation)) {
            work->auxiliary=PollAuxiliary(work->auxiliary);
            if(work->auxiliary==0) {
                work->counter=86;
                event->state++;
            }
        }
        break;
    case 257:
        work->counter--;
        if(work->counter==0) {
            struct Task *scanline=CreateScanlineTask(3,1,task);
            u16 fill=ReadResourcePosition(3,1);
            u16 *buffer=GetScanlineBuffer(scanline);
            u16 index;
            for(index=0;index<=159;index++)buffer[index]=fill;
            SetScanlineFlagFour(scanline,1);
            work->scanline=scanline;
            work->counter=0;
            event->state++;
        }
        break;
    case 258: {
        u16 *buffer=GetScanlineBuffer(work->scanline);
        u16 index;
        for(index=0;index<work->counter;index++)buffer[index]+=2;
        work->counter+=2;
        if(work->counter>72) {
            u32 mask=GetLayerMask(3);
            gDisplayControl&=~mask;
            event->state++;
        }
        break;
    }
    case 259:
        work->scanline=PollScanline(work->scanline);
        if(work->scanline==0) {
            work->resource=PollResource(work->resource,1);
            if(work->resource==0)event->state=2;
        }
        break;
    }
    return 0;
}
__asm__(".global gResource\n.set gResource,0x88ed8cc\n.global gAuxiliary\n.set gAuxiliary,0x894d804\n.global gStageSequence\n.set gStageSequence,0x8399b2c\n.global gDisplayControl\n.set gDisplayControl,0x3000940\n.global ConfigureResource\n.thumb_set ConfigureResource,0x80d49fd\n.global CreateResource\n.thumb_set CreateResource,0x80d4b65\n.global GetLayerMask\n.thumb_set GetLayerMask,0x80035a9\n.global CreateAuxiliary\n.thumb_set CreateAuxiliary,0x80d3e9d\n.global BeginInterpolation\n.thumb_set BeginInterpolation,0x80e0609\n.global CreateStage\n.thumb_set CreateStage,0x80dfd8d\n.global AdvanceInterpolation\n.thumb_set AdvanceInterpolation,0x80e064d\n.global SetLayerPosition\n.thumb_set SetLayerPosition,0x800bc09\n.global InterpolationFinished\n.thumb_set InterpolationFinished,0x80e0691\n.global PollAuxiliary\n.thumb_set PollAuxiliary,0x80d3f09\n.global CreateScanlineTask\n.thumb_set CreateScanlineTask,0x80d9915\n.global ReadResourcePosition\n.thumb_set ReadResourcePosition,0x80d499d\n.global GetScanlineBuffer\n.thumb_set GetScanlineBuffer,0x80d996d\n.global SetScanlineFlagFour\n.thumb_set SetScanlineFlagFour,0x80d9ba9\n.global PollScanline\n.thumb_set PollScanline,0x80d9b65\n.global PollResource\n.thumb_set PollResource,0x80d4d2d\n");
