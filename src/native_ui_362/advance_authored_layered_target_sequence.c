typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct LayeredTargetEvent {
    u16 phase,unknown02;
    void *actor;
    u8 unknown08[12];
    s16 definition_id;
    u16 variant;
    u8 unknown18[4];
};
struct SequenceRamp {
    u16 value;
    s16 remaining,error;
    u16 step,period,magnitude;
};
struct LayeredTargetWork {
    u16 unknown00;
    u8 variant,special,status,unknown05[3];
    s16 x,y;
    TaskNode *continuation;
    u32 unknown10;
    void *actor,*target,*resources[2];
    TaskNode *palette,*object;
    void *input_actor;
    TaskNode *opening,*layer,*motion;
    u32 unknown3c;
    TaskNode *sequence;
    struct SequenceRamp ramp;
    u32 unknown50[3];
};
struct SequenceDisplayShadow {
    u16 control;
    u8 unknown02[56];
    volatile u8 byte58,byte59;
    u8 unknown60[2];
    volatile u8 byte62,byte63;
    u8 unknown64[2];
    volatile u8 byte66;
    u8 unknown67;
    volatile u8 byte68;
};
struct SequenceLayerContext {u8 unknown00[194];u16 field194;};
struct TargetMotionRecord {u8 bytes[20];};
typedef char EventSize[sizeof(struct LayeredTargetEvent)==28?1:-1];
typedef char RampSize[sizeof(struct SequenceRamp)==12?1:-1];
typedef char WorkSize[sizeof(struct LayeredTargetWork)==92?1:-1];
extern const u8 gOpening[],gSpecialPalette[],gLayerResource[],gOpeningStage[];
extern const u8 gTargetResource[],gPaletteSequence[];
extern const struct TargetMotionRecord gTargetMotions[];
extern struct SequenceDisplayShadow gDisplayShadow;
extern struct SequenceLayerContext gLayerContext;
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDefinitionInputs(void);
extern TaskNode *PollDefinitionEffect(TaskNode *);
extern void CopyPaletteGroups(const void *,u32,u32,u32,u32);
extern TaskNode *CreateRecordContinuation(void *,u8,u8,u32,TaskNode *);
extern void *GetDefinitionTarget(void *,u8);
extern void *ProjectTargetActor(void *,s16 *,s16 *,u16 *);
extern TaskNode *CreateActorLayer(void *,void *,void *,u8,TaskNode *);
/* Original stack words remain full; the callee performs its own LOW16
 * signed-coordinate and flag normalization. */
extern void LoadLayerResource(const void *,u8,u8,s16,s32,u32,u8);
extern TaskNode *CreateDefinitionObject(u8,u8,u8,TaskNode *);
extern void InitializeRamp(struct SequenceRamp *,u16,u16,u16);
extern void ReadCurrentBytePair(u8 *,u8 *);
extern u32 ReadLowDisplayMask(u8);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern u32 IsRampComplete(const struct SequenceRamp *);
extern void AdvanceRamp(struct SequenceRamp *);
/* Preserve signed caller words; this helper consumes each coordinate LOW16. */
extern void ConfigureDefinitionObject(TaskNode *,s32,s32,u32,u16);
extern void UpdateDefinitionObject(TaskNode *);
extern TaskNode *PollAndReleaseMotion(TaskNode *);
/* The wrapper normalizes these scalar transport words inside the callee. */
extern void *CreateTargetResource(const void *,u32,s32,s32,u32,u32,u32,u32);
extern TaskNode *CreatePaletteSequence(const void *,TaskNode *);
extern u32 PollResourceArray(void **,u16);
extern TaskNode *CreateLayerExit(void *,u8,u16,TaskNode *);
extern void ClearDefinitionObject(TaskNode *);
extern u32 ReadHighDisplayMask(u8);
extern TaskNode *CreateTargetMotion(void *,const struct TargetMotionRecord *,u8,u16,u32,TaskNode *,u32);
extern TaskNode *PollPaletteSequence(TaskNode *);
extern TaskNode *PollRecordContinuation(TaskNode *);
extern TaskNode *PollDefinitionObject(TaskNode *);
__asm__(
 ".global gOpening\n.set gOpening,0x0839d498\n"
 ".global gSpecialPalette\n.set gSpecialPalette,0x088eacd8\n"
 ".global gLayerResource\n.set gLayerResource,0x088f46cc\n"
 ".global gOpeningStage\n.set gOpeningStage,0x0839d4f0\n"
 ".global gTargetResource\n.set gTargetResource,0x08502c00\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x0894aab0\n"
 ".global gTargetMotions\n.set gTargetMotions,0x0839d4c8\n"
 ".global gDisplayShadow\n.set gDisplayShadow,0x03000940\n"
 ".global gLayerContext\n.set gLayerContext,0x03003860\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080e03f9\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x080d38b5\n"
 ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x080e05dd\n"
 ".global CopyPaletteGroups\n.thumb_set CopyPaletteGroups,0x080d45d1\n"
 ".global CreateRecordContinuation\n.thumb_set CreateRecordContinuation,0x080fde59\n"
 ".global GetDefinitionTarget\n.thumb_set GetDefinitionTarget,0x080dd4a5\n"
 ".global ProjectTargetActor\n.thumb_set ProjectTargetActor,0x080dd749\n"
 ".global CreateActorLayer\n.thumb_set CreateActorLayer,0x080dc269\n"
 ".global LoadLayerResource\n.thumb_set LoadLayerResource,0x080d72c9\n"
 ".global CreateDefinitionObject\n.thumb_set CreateDefinitionObject,0x080dab85\n"
 ".global InitializeRamp\n.thumb_set InitializeRamp,0x080e0609\n"
 ".global ReadCurrentBytePair\n.thumb_set ReadCurrentBytePair,0x0801e611\n"
 ".global ReadLowDisplayMask\n.thumb_set ReadLowDisplayMask,0x080035d1\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x080dfd8d\n"
 ".global IsRampComplete\n.thumb_set IsRampComplete,0x080e0691\n"
 ".global AdvanceRamp\n.thumb_set AdvanceRamp,0x080e064d\n"
 ".global ConfigureDefinitionObject\n.thumb_set ConfigureDefinitionObject,0x080dac81\n"
 ".global UpdateDefinitionObject\n.thumb_set UpdateDefinitionObject,0x080d9b99\n"
 ".global PollAndReleaseMotion\n.thumb_set PollAndReleaseMotion,0x080dba5d\n"
 ".global CreateTargetResource\n.thumb_set CreateTargetResource,0x080d5cc1\n"
 ".global CreatePaletteSequence\n.thumb_set CreatePaletteSequence,0x080d4705\n"
 ".global PollResourceArray\n.thumb_set PollResourceArray,0x080d5f25\n"
 ".global CreateLayerExit\n.thumb_set CreateLayerExit,0x080dc2f1\n"
 ".global ClearDefinitionObject\n.thumb_set ClearDefinitionObject,0x080dadfd\n"
 ".global ReadHighDisplayMask\n.thumb_set ReadHighDisplayMask,0x080035a9\n"
 ".global CreateTargetMotion\n.thumb_set CreateTargetMotion,0x080dcfe5\n"
 ".global PollPaletteSequence\n.thumb_set PollPaletteSequence,0x080d4775\n"
 ".global PollRecordContinuation\n.thumb_set PollRecordContinuation,0x080fdebd\n"
 ".global PollDefinitionObject\n.thumb_set PollDefinitionObject,0x080d9b65");
s32 AdvanceAuthoredLayeredTargetSequence(TaskNode *,struct LayeredTargetEvent *,struct LayeredTargetWork *)
    __asm__("OriginalActionCallback_000FCB90");
s32 AdvanceAuthoredLayeredTargetSequence(TaskNode *parent,struct LayeredTargetEvent *event,
                                       struct LayeredTargetWork *work)
{
    u8 first,second;
    u16 phase=event->phase;
    switch(phase) {
    case 0: {
        u16 variant;
        void *actor;
        u8 count;
        work->special=(u8)phase;
        if(event->definition_id==326) work->special=1;
        variant=event->variant;
        work->variant=(u8)variant;
        actor=event->actor;
        work->input_actor=actor;
        count=4;
        if((u8)variant!=0) count=0;
        work->opening=CreateDefinitionEffectTask(actor,gOpening,count,0,(const s16 *)(u32)phase,parent);
        break;
    }
    case 1:
        CleanupDefinitionInputs();
        break;
    case 256: {
        u32 first_parameter;
        u8 special;
        work->opening=PollDefinitionEffect(work->opening);
        if(work->opening!=0) break;
        first_parameter=0;
        special=work->special;
        if(special==1) {
            CopyPaletteGroups(gSpecialPalette,6,1,1,special);
            first_parameter=6;
        }
        work->continuation=CreateRecordContinuation(work->input_actor,first_parameter,0,(u32)&work->status,parent);
        if(work->continuation==0) event->phase=2;
        else ++event->phase;
        break;
    }
    case 257: {
        u32 status=work->status;
        u32 zero;
        const u8 *layer_resource;
        struct SequenceDisplayShadow *shadow;
        u32 masks,available;
        if(status==0) break;
        if(status==2) {
            event->phase=260;
            break;
        }
        work->target=GetDefinitionTarget(work->input_actor,0);
        work->actor=ProjectTargetActor(work->target,&work->x,&work->y,0);
        work->layer=CreateActorLayer(work->actor,(void *)0x0600f9c0,(void *)0x06005000,0,parent);
        if(work->special==1) gLayerContext.field194=22;
        layer_resource=gLayerResource;
        /* The actual resource address is defined before the preserved zero. */
        __asm__("" : : "r"(layer_resource));
        zero=0;
        LoadLayerResource(layer_resource,0,2,0,zero,zero,1);
        work->object=CreateDefinitionObject(0,0,0,parent);
        InitializeRamp(&work->ramp,0,24,32);
        ReadCurrentBytePair(&first,&second);
        shadow=&gDisplayShadow;
        shadow->byte59=zero;
        shadow->byte58=zero;
        shadow->byte63=zero;
        shadow->byte62=160;
        masks=ReadLowDisplayMask(first);
        masks|=ReadLowDisplayMask(second);
        available=63;
        shadow->byte66=available&~masks;
        shadow->byte68=available&~ReadLowDisplayMask(2);
        shadow->control|=0x2000;
        work->sequence=CreateSequenceStage(gOpeningStage,1,4,0,parent);
        ++event->phase;
        break;
    }
    case 258: {
        struct SequenceRamp *ramp=&work->ramp;
        TaskNode *remaining;
        if((u8)IsRampComplete(ramp)==0) {
            AdvanceRamp(ramp);
            ConfigureDefinitionObject(work->object,work->x,work->y,ramp->value,
                                                     (u16)((s16)ramp->value>>1));
            UpdateDefinitionObject(work->object);
            break;
        }
        remaining=PollAndReleaseMotion(work->layer);
        work->layer=remaining;
        if(remaining!=0) break;
        work->resources[0]=CreateTargetResource(gTargetResource,0,work->x,work->y,980,6,
                                                        (u32)remaining,(u32)remaining);
        work->resources[1]=CreateTargetResource(gTargetResource,1,work->x,work->y,980,6,1,(u32)remaining);
        work->palette=CreatePaletteSequence(gPaletteSequence,parent);
        ++event->phase;
        break;
    }
    case 259:
        if((u8)PollResourceArray(work->resources,2)==0) break;
        InitializeRamp(&work->ramp,24,0,32);
        work->layer=CreateLayerExit(work->actor,0,12,parent);
        ++event->phase;
        break;
    case 260: {
        struct SequenceRamp *ramp=&work->ramp;
        TaskNode *remaining;
        if((u8)IsRampComplete(ramp)==0) {
            AdvanceRamp(ramp);
            ClearDefinitionObject(work->object);
            ConfigureDefinitionObject(work->object,work->x,work->y,ramp->value,
                                                     (u16)((s16)ramp->value>>1));
            UpdateDefinitionObject(work->object);
            if((u8)IsRampComplete(ramp)!=0) {
                u32 mask=ReadHighDisplayMask(2);
                u32 control=gDisplayShadow.control;
                control&=~mask;
                control&=0xdfff;
                gDisplayShadow.control=control;
            }
            break;
        }
        remaining=PollAndReleaseMotion(work->layer);
        work->layer=remaining;
        if(remaining!=0) break;
        work->motion=CreateTargetMotion(work->target,&gTargetMotions[work->special],12,0,12,parent,(u32)remaining);
        ++event->phase;
        break;
    }
    case 261:
        work->palette=PollPaletteSequence(work->palette);
        if(work->palette!=0) break;
        work->continuation=PollRecordContinuation(work->continuation);
        if(work->continuation!=0) break;
        work->object=PollDefinitionObject(work->object);
        if(work->object!=0) break;
        work->motion=PollAndReleaseMotion(work->motion);
        if(work->motion!=0) break;
        event->phase=2;
        break;
    }
    return 0;
}
