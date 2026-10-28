typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct ScaleSequenceEvent {
    u16 phase,unknown02;
    void *actor;
    u8 unknown08[12];
    s16 definition_id;
    u16 variant;
    u8 unknown18[4];
};
struct SequenceRamp {u16 value;s16 remaining,error;u16 step,period,magnitude;};
struct ScaleSequenceWork {
    u8 variant,unknown01;
    u16 delay;
    s16 x,y;
    void *input_actor,*target,*actor,*resource;
    TaskNode *auxiliary;
    void *positioned_out;
    u32 unknown20;
    TaskNode *positioned,*opening,*motion,*sequence;
    struct SequenceRamp ramp;
};
struct BackgroundAffineInput {
    s32 origin_x,origin_y;
    s16 center_x,center_y,scale_x,scale_y;
    u16 angle;
};
struct BackgroundAffineMatrix {s16 pa,pb,pc,pd;s32 x,y;};
typedef char WorkSize[sizeof(struct ScaleSequenceWork)==64?1:-1];
typedef char EventSize[sizeof(struct ScaleSequenceEvent)==28?1:-1];
typedef char RampSize[sizeof(struct SequenceRamp)==12?1:-1];
typedef char AffineInputSize[sizeof(struct BackgroundAffineInput)==20?1:-1];
typedef char AffineMatrixSize[sizeof(struct BackgroundAffineMatrix)==16?1:-1];
extern const u8 gOpening[],gResource[],gAuxiliary[],gInitialStage[],gPositionedSequence[];
extern const u8 gTargetMotion[],gFlaggedStage[];
extern u16 gDisplayControl;
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDefinitionInputs(void);
extern TaskNode *PollDefinitionEffect(TaskNode *);
extern u32 QueryDefinitionTargetAvailability(void *,u16);
extern void *GetDefinitionTarget(void *,u8);
extern u32 SetDefinitionTargetCoordinateMode(void *,u8,u8);
extern u32 QueryEffectReadiness(void);
extern void *ProjectTargetActor(void *,s16 *,s16 *,u16 *);
extern void ConfigureResourceCoordinates(u8,u8,u16,s16,s16);
extern void ConfigureObjectIndex(u8,u8,u8);
extern void *CreateResource(u8,const void *,u16,u8);
extern void SetResourceEnabled(void *,u8);
extern void MergeDisplayControlByte(u8);
extern void BiosBackgroundAffineSet(const struct BackgroundAffineInput *,struct BackgroundAffineMatrix *,u32);
/* The selected bank switch consumes the complete word, not a byte domain. */
extern void SetDisplayShadowBank(const volatile struct BackgroundAffineMatrix *,u32);
extern u32 ReadDisplayMask(u8);
extern TaskNode *CreateAuxiliary(const void *,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern void InitializeRamp(struct SequenceRamp *,u16,u16,u16);
extern u32 IsRampComplete(const struct SequenceRamp *);
extern void AdvanceRamp(struct SequenceRamp *);
extern TaskNode *PollAuxiliary(TaskNode *);
extern void RemoveResource(void *,u8);
/* Signed caller coordinate words are kept whole; D6098 consumes LOW16. */
extern TaskNode *CreatePositionedTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateTargetMotion(void *,const void *,u8,u16,u32,TaskNode *,u32);
extern u32 TestTargetRecordFlag7(const void *);
extern TaskNode *PollAndReleaseMotion(TaskNode *);
extern TaskNode *CreateActorPaletteRequest(void *,u16,u8,u16,TaskNode *);
extern TaskNode *PollPositionedTask(TaskNode *);
__asm__(
 ".global gOpening\n.set gOpening,0x083a65a4\n"
 ".global gResource\n.set gResource,0x088f378c\n"
 ".global gAuxiliary\n.set gAuxiliary,0x0894debc\n"
 ".global gInitialStage\n.set gInitialStage,0x083a6618\n"
 ".global gPositionedSequence\n.set gPositionedSequence,0x083a65d4\n"
 ".global gTargetMotion\n.set gTargetMotion,0x083a6604\n"
 ".global gFlaggedStage\n.set gFlaggedStage,0x083a6620\n"
 ".global gDisplayControl\n.set gDisplayControl,0x03000940\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080e03f9\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x080d38b5\n"
 ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x080e05dd\n"
 ".global QueryDefinitionTargetAvailability\n.thumb_set QueryDefinitionTargetAvailability,0x080d8859\n"
 ".global GetDefinitionTarget\n.thumb_set GetDefinitionTarget,0x080dd4a5\n"
 ".global SetDefinitionTargetCoordinateMode\n.thumb_set SetDefinitionTargetCoordinateMode,0x080dc12d\n"
 ".global QueryEffectReadiness\n.thumb_set QueryEffectReadiness,0x080d8b4d\n"
 ".global ProjectTargetActor\n.thumb_set ProjectTargetActor,0x080dd749\n"
 ".global ConfigureResourceCoordinates\n.thumb_set ConfigureResourceCoordinates,0x080d49fd\n"
 ".global ConfigureObjectIndex\n.thumb_set ConfigureObjectIndex,0x0800bc91\n"
 ".global CreateResource\n.thumb_set CreateResource,0x080d4b65\n"
 ".global SetResourceEnabled\n.thumb_set SetResourceEnabled,0x0800bda5\n"
 ".global MergeDisplayControlByte\n.thumb_set MergeDisplayControlByte,0x08003621\n"
 ".global BiosBackgroundAffineSet\n.thumb_set BiosBackgroundAffineSet,0x08141865\n"
 ".global SetDisplayShadowBank\n.thumb_set SetDisplayShadowBank,0x080032f9\n"
 ".global ReadDisplayMask\n.thumb_set ReadDisplayMask,0x080035a9\n"
 ".global CreateAuxiliary\n.thumb_set CreateAuxiliary,0x080d3e9d\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x080dfd8d\n"
 ".global InitializeRamp\n.thumb_set InitializeRamp,0x080e0609\n"
 ".global IsRampComplete\n.thumb_set IsRampComplete,0x080e0691\n"
 ".global AdvanceRamp\n.thumb_set AdvanceRamp,0x080e064d\n"
 ".global PollAuxiliary\n.thumb_set PollAuxiliary,0x080d3f09\n"
 ".global RemoveResource\n.thumb_set RemoveResource,0x080d4d15\n"
 ".global CreatePositionedTask\n.thumb_set CreatePositionedTask,0x080d6099\n"
 ".global CreateTargetMotion\n.thumb_set CreateTargetMotion,0x080dcfe5\n"
 ".global TestTargetRecordFlag7\n.thumb_set TestTargetRecordFlag7,0x080dd581\n"
 ".global PollAndReleaseMotion\n.thumb_set PollAndReleaseMotion,0x080dba5d\n"
 ".global CreateActorPaletteRequest\n.thumb_set CreateActorPaletteRequest,0x080dc499\n"
 ".global PollPositionedTask\n.thumb_set PollPositionedTask,0x080d6135");
s32 AdvanceAuthoredTargetScaleSequence(TaskNode *,struct ScaleSequenceEvent *,struct ScaleSequenceWork *)
    __asm__("OriginalActionCallback_0011A1AC");
s32 AdvanceAuthoredTargetScaleSequence(TaskNode *parent,struct ScaleSequenceEvent *event,
                                     struct ScaleSequenceWork *work)
{
    struct BackgroundAffineInput initial_input;
    struct BackgroundAffineMatrix initial_matrix;
    struct BackgroundAffineInput update_input;
    struct BackgroundAffineMatrix update_matrix;
    u16 phase=event->phase;
    switch(phase) {
    case 0: {
        u16 variant=event->variant;
        void *actor;
        u8 count;
        work->variant=(u8)variant;
        actor=event->actor;
        work->input_actor=actor;
        count=4;
        if((u8)variant!=0) count=0;
        work->opening=CreateDefinitionEffectTask(actor,gOpening,count,7,(const s16 *)(u32)phase,parent);
        break;
    }
    case 1:
        CleanupDefinitionInputs();
        break;
    case 256:
        work->opening=PollDefinitionEffect(work->opening);
        if(work->opening!=0) break;
        if((u8)QueryDefinitionTargetAvailability(work->input_actor,0)==0) {
            event->phase=2;
            break;
        }
        work->target=GetDefinitionTarget(work->input_actor,0);
        SetDefinitionTargetCoordinateMode(work->input_actor,0,1);
        ++event->phase;
        break;
    case 257: {
        u32 ready=(u8)QueryEffectReadiness();
        register struct BackgroundAffineInput *destination __asm__("r0");
        u32 scale;
        u32 mask,control;
        if(ready!=0) break;
        work->actor=ProjectTargetActor(work->target,&work->x,&work->y,0);
        work->y=(u16)work->y-12;
        ConfigureResourceCoordinates(0,2,1,work->x,work->y);
        ConfigureObjectIndex(0,0,2);
        work->resource=CreateResource(0,gResource,64,6);
        SetResourceEnabled(work->resource,1);
        MergeDisplayControlByte(1);
        initial_input.origin_x=0x2000;
        initial_input.origin_y=0x2000;
        initial_input.center_x=work->x;
        initial_input.center_y=work->y;
        destination=&initial_input;
        /* Preserve the actual R0 destination before R1 loads the scale. Its
         * last use is the same full-pointer BIOS argument, with no earlier
         * live R0 input or intervening call in this interval. */
        __asm__("" : : "r"(destination));
        /* The initial transform consumes the preexisting ramp value before
         * the original later InitializeRamp call; do not initialize it early. */
        scale=work->ramp.value;
        destination->scale_x=scale;
        destination->scale_y=scale;
        destination->angle=ready;
        BiosBackgroundAffineSet(destination,&initial_matrix,1);
        SetDisplayShadowBank(&initial_matrix,2);
        mask=ReadDisplayMask(2);
        control=gDisplayControl;
        control|=mask;
        gDisplayControl=control;
        work->auxiliary=CreateAuxiliary(gAuxiliary,parent);
        work->sequence=CreateSequenceStage(gInitialStage,1,4,0,parent);
        InitializeRamp(&work->ramp,256,2048,60);
        work->delay=30;
        ++event->phase;
        break;
    }
    case 258: {
        struct SequenceRamp *ramp;
        u32 done,scale;
        TaskNode *remaining;
        u32 mask,control,two;
        s32 position_x,position_y;
        if(work->delay!=0) {
            --work->delay;
            break;
        }
        ramp=&work->ramp;
        done=(u8)IsRampComplete(ramp);
        if(done==0) {
            AdvanceRamp(ramp);
            update_input.origin_x=0x2000;
            update_input.origin_y=0x2000;
            update_input.center_x=work->x;
            update_input.center_y=work->y;
            scale=work->ramp.value;
            update_input.scale_x=scale;
            update_input.scale_y=scale;
            update_input.angle=done;
            BiosBackgroundAffineSet(&update_input,&update_matrix,1);
            SetDisplayShadowBank(&update_matrix,2);
            break;
        }
        remaining=PollAuxiliary(work->auxiliary);
        work->auxiliary=remaining;
        if(remaining!=0) break;
        RemoveResource(work->resource,0);
        work->resource=(void *)remaining;
        mask=ReadDisplayMask(2);
        control=gDisplayControl;
        control&=~mask;
        gDisplayControl=control;
        position_x=work->x;
        position_y=(s16)((u16)work->y+12);
        two=2;
        work->positioned=CreatePositionedTask(position_x,position_y,0,1,two,
                                  &work->positioned_out,gPositionedSequence,parent);
        work->motion=CreateTargetMotion(work->target,gTargetMotion,12,0,two,parent,(u32)remaining);
        if((u8)TestTargetRecordFlag7(work->target)!=0) {
            work->sequence=CreateSequenceStage(gFlaggedStage,1,4,0,parent);
            ++event->phase;
        } else event->phase=260;
        break;
    }
    case 259:
        work->motion=PollAndReleaseMotion(work->motion);
        if(work->motion!=0) break;
        work->motion=CreateActorPaletteRequest(work->actor,16,12,0,parent);
        ++event->phase;
        break;
    case 260:
        work->positioned=PollPositionedTask(work->positioned);
        if(work->positioned!=0) break;
        work->motion=PollAndReleaseMotion(work->motion);
        if(work->motion!=0) break;
        event->phase=2;
        break;
    }
    return 0;
}
