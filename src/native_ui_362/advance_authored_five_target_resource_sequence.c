typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
typedef void (*TaskCallback)(TaskNode *,u16 *,void *);
struct ResourceSequenceEvent {
    u16 phase,unknown02;
    void *actor;
    u8 unknown08[12];
    s16 definition_id;
    u16 variant;
    u8 unknown18[4];
};
struct ResourceTargetEvent {
    u32 unknown00;
    void *target;
    u8 unknown08[12];
    u16 ordinal,special,unknown18,unknown1a;
};
struct ResourceSequenceWork {
    u8 variant,byte_delay,unknown02,count;
    u16 ordinal;
    u8 special,unknown07;
    s16 x,y;
    u8 completion,unknown0d[3];
    TaskNode *children[5];
    void *actor,*record;
    TaskNode *opening;
    void *positioned_out;
    TaskNode *positioned_task;
    void *resource;
    TaskNode *auxiliary,*palette;
    u32 unknown44;
    TaskNode *record_child,*sequence;
};
typedef char EventSize[sizeof(struct ResourceSequenceEvent)==28?1:-1];
typedef char TargetEventSize[sizeof(struct ResourceTargetEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct ResourceSequenceWork)==80?1:-1];
extern const u8 gOpening[],gPaletteA[],gPaletteB[],gPaletteC[],gRecordSequence[];
extern const u8 gPositionedSequence[],gStageA[],gRecordFollowup[],gResource[];
extern const u8 gAuxiliary[],gPaletteSequenceA[],gPaletteSequenceB[],gStageB[];
extern u16 gDisplayControl;
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDefinitionInputs(void);
extern TaskNode *PollDefinitionEffect(TaskNode *);
extern void CopyPaletteGroups(const void *,u32,u32,u32,u32);
extern u32 ReadDefinitionTargetCount(void *);
extern void *GetActorNestedRecord(void *);
extern u32 ReadNestedType(void *);
extern TaskNode *CreateRecordSequence(void *,void **,u16,u8,u8 *,const void *,u16,u16,TaskNode *);
extern void ProjectRecordPosition(const void *,s16 *,s16 *);
/* The second scalar travels as the original signed caller word. D6098 consumes
 * its LOW16 as a coordinate; preserve the actual LDRSH argument transport. */
extern TaskNode *CreatePositionedTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollPositionedTask(TaskNode *);
extern void SelectRecordFlag(void *,u8);
extern void RemoveTaskBranch(TaskNode *);
extern TaskNode *CreateFollowupSequence(void *,u8,u8 *,const void *,u16,u16,TaskNode *);
extern u32 QueryRecordBoundary(void *);
extern u32 QueryEffectReadiness(void);
extern void ReadActorCoordinates(void *,s16 *,s16 *);
extern void ConfigureResourceCoordinates(u8,u8,u16,s16,s16);
extern void *CreateResource(u8,const void *,u16,u8);
extern u32 ReadDisplayMask(u8);
extern TaskNode *CreateAuxiliary(const void *,TaskNode *);
extern TaskNode *CreatePaletteSequence(const void *,TaskNode *);
extern u32 QueryDefinitionTargets(void *,u16,u16,TaskNode *);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTarget(void *,u8);
extern TaskNode *CreateOppositePhaseChild(TaskCallback,u16,const u32 *,TaskNode *);
extern void RunResourceTargetChild(TaskNode *,u16 *,void *);
extern void *PollResource(void *,u8);
extern TaskNode *PollAuxiliary(TaskNode *);
extern TaskNode *PollPaletteSequence(TaskNode *);
extern u32 PollRecordHandles(void *);
__asm__(
 ".global gOpening\n.set gOpening,0x0839bd08\n"
 ".global gPaletteA\n.set gPaletteA,0x088ea7f0\n"
 ".global gPaletteB\n.set gPaletteB,0x088ea81c\n"
 ".global gPaletteC\n.set gPaletteC,0x088eab24\n"
 ".global gRecordSequence\n.set gRecordSequence,0x0839bdb4\n"
 ".global gPositionedSequence\n.set gPositionedSequence,0x0839bd74\n"
 ".global gStageA\n.set gStageA,0x0839bdbc\n"
 ".global gRecordFollowup\n.set gRecordFollowup,0x0839bdb8\n"
 ".global gResource\n.set gResource,0x088ef44c\n"
 ".global gDisplayControl\n.set gDisplayControl,0x03000940\n"
 ".global gAuxiliary\n.set gAuxiliary,0x0894d91c\n"
 ".global gPaletteSequenceA\n.set gPaletteSequenceA,0x0894abf0\n"
 ".global gPaletteSequenceB\n.set gPaletteSequenceB,0x0894ac40\n"
 ".global gStageB\n.set gStageB,0x0839bdc4\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080e03f9\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x080d38b5\n"
 ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x080e05dd\n"
 ".global CopyPaletteGroups\n.thumb_set CopyPaletteGroups,0x080d45d1\n"
 ".global ReadDefinitionTargetCount\n.thumb_set ReadDefinitionTargetCount,0x080dd495\n"
 ".global GetActorNestedRecord\n.thumb_set GetActorNestedRecord,0x080dd47d\n"
 ".global ReadNestedType\n.thumb_set ReadNestedType,0x080dd709\n"
 ".global CreateRecordSequence\n.thumb_set CreateRecordSequence,0x080ddf69\n"
 ".global ProjectRecordPosition\n.thumb_set ProjectRecordPosition,0x080dbdc9\n"
 ".global CreatePositionedTask\n.thumb_set CreatePositionedTask,0x080d6099\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x080dfd8d\n"
 ".global PollPositionedTask\n.thumb_set PollPositionedTask,0x080d6135\n"
 ".global SelectRecordFlag\n.thumb_set SelectRecordFlag,0x080de3bd\n"
 ".global RemoveTaskBranch\n.thumb_set RemoveTaskBranch,0x080dba51\n"
 ".global CreateFollowupSequence\n.thumb_set CreateFollowupSequence,0x080de4f5\n"
 ".global QueryRecordBoundary\n.thumb_set QueryRecordBoundary,0x080d8cd5\n"
 ".global QueryEffectReadiness\n.thumb_set QueryEffectReadiness,0x080d8b4d\n"
 ".global ReadActorCoordinates\n.thumb_set ReadActorCoordinates,0x080d8c59\n"
 ".global ConfigureResourceCoordinates\n.thumb_set ConfigureResourceCoordinates,0x080d49fd\n"
 ".global CreateResource\n.thumb_set CreateResource,0x080d4b65\n"
 ".global ReadDisplayMask\n.thumb_set ReadDisplayMask,0x080035a9\n"
 ".global CreateAuxiliary\n.thumb_set CreateAuxiliary,0x080d3e9d\n"
 ".global CreatePaletteSequence\n.thumb_set CreatePaletteSequence,0x080d4705\n"
 ".global QueryDefinitionTargets\n.thumb_set QueryDefinitionTargets,0x080d8925\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x080e0571\n"
 ".global GetDefinitionTarget\n.thumb_set GetDefinitionTarget,0x080dd4a5\n"
 ".global CreateOppositePhaseChild\n.thumb_set CreateOppositePhaseChild,0x08005b6d\n"
 ".global RunResourceTargetChild\n.thumb_set RunResourceTargetChild,0x080f7a35\n"
 ".global PollResource\n.thumb_set PollResource,0x080d4d2d\n"
 ".global PollAuxiliary\n.thumb_set PollAuxiliary,0x080d3f09\n"
 ".global PollPaletteSequence\n.thumb_set PollPaletteSequence,0x080d4775\n"
 ".global PollRecordHandles\n.thumb_set PollRecordHandles,0x080de1f1");
s32 AdvanceAuthoredFiveTargetResourceSequence(TaskNode *,struct ResourceSequenceEvent *,struct ResourceSequenceWork *)
    __asm__("OriginalActionCallback_000F7B18");
s32 AdvanceAuthoredFiveTargetResourceSequence(TaskNode *parent,struct ResourceSequenceEvent *event,
                                             struct ResourceSequenceWork *work)
{
    s16 actor_x,actor_y;
    u16 phase=event->phase;
    switch(phase) {
    case 0: {
        u16 variant;
        u8 opening_count;
        void *actor;
        work->special=(u8)phase;
        if(event->definition_id==0x147) work->special=1;
        variant=event->variant;
        work->variant=(u8)variant;
        actor=event->actor;
        work->actor=actor;
        opening_count=5;
        if((u8)variant!=0) opening_count=0;
        work->opening=CreateDefinitionEffectTask(actor,gOpening,opening_count,0,(const s16 *)(u32)phase,parent);
        break;
    }
    case 1:
        CleanupDefinitionInputs();
        break;
    case 256: {
        u8 special;
        u16 value;
        work->opening=PollDefinitionEffect(work->opening);
        if(work->opening!=0) break;
        special=work->special;
        if(special==1) {
            CopyPaletteGroups(gPaletteA,6,1,6,special);
            CopyPaletteGroups(gPaletteB,7,1,1,special);
            CopyPaletteGroups(gPaletteA,8,1,6,special);
            CopyPaletteGroups(gPaletteC,6,0,2,special);
        }
        if(work->variant!=0) {
            work->count=(u8)ReadDefinitionTargetCount(work->actor);
            work->byte_delay=1;
            event->phase=261;
            break;
        }
        value=144;
        if(work->special==1) {
            u16 type=(u16)ReadNestedType(GetActorNestedRecord(work->actor));
            if(type==97) value=84;
            else if(type==101) value=88;
        }
        work->record_child=CreateRecordSequence(work->actor,&work->record,value,1,
                   &work->completion,gRecordSequence,0,0,parent);
        ProjectRecordPosition(work->record,&work->x,&work->y);
        ++event->phase;
        break;
    }
    case 257:
        if(work->completion==0) break;
        work->positioned_task=CreatePositionedTask(work->x,work->y,0,1,1,
                                            &work->positioned_out,gPositionedSequence,parent);
        work->sequence=CreateSequenceStage(gStageA,1,4,0,parent);
        ++event->phase;
        break;
    case 258: {
        TaskNode *remaining=PollPositionedTask(work->positioned_task);
        work->positioned_task=remaining;
        if(remaining!=0) break;
        SelectRecordFlag(work->record,0);
        RemoveTaskBranch(work->record_child);
        work->record_child=CreateFollowupSequence(work->record,1,&work->completion,
                                  gRecordFollowup,(u32)remaining,(u32)remaining,parent);
        ++event->phase;
        break;
    }
    case 259:
        if(work->completion==0) break;
        QueryRecordBoundary(work->actor);
        work->ordinal=4;
        ++event->phase;
        break;
    case 260: {
        u32 remaining=work->ordinal;
        u32 count;
        if(remaining!=0) {
            --remaining;
            work->ordinal=(u16)remaining;
            if((u16)remaining!=0) break;
        }
        if((u8)QueryEffectReadiness()!=0) break;
        ReadActorCoordinates(work->actor,&actor_x,&actor_y);
        ConfigureResourceCoordinates(0,2,0,actor_x,actor_y);
        work->resource=CreateResource(0,gResource,0x39d,6);
        {
            /* The original acquires the shadow address after the mask call. */
            u32 mask=ReadDisplayMask(2);
            register u32 shadow __asm__("r1")=gDisplayControl;
            shadow|=mask;
            /* This initialized full-word result is the original R1 store
             * consumer. No live input home or call crosses this interval. */
            __asm__("" : "+r"(shadow));
            gDisplayControl=(u16)shadow;
        }
        work->auxiliary=CreateAuxiliary(gAuxiliary,parent);
        if(work->special==0)
            work->palette=CreatePaletteSequence(gPaletteSequenceA,parent);
        else
            work->palette=CreatePaletteSequence(gPaletteSequenceB,parent);
        work->sequence=CreateSequenceStage(gStageB,1,4,0,parent);
        count=QueryDefinitionTargets(work->actor,0,40,parent);
        work->count=(u8)count;
        if((u8)count==0) event->phase=262;
        else {
            work->byte_delay=20;
            ++event->phase;
        }
        break;
    }
    case 261: {
        TaskNode **children=work->children;
        u32 remaining;
        PollDefinitionTaskArray(children,5);
        remaining=work->byte_delay-1;
        work->byte_delay=(u8)remaining;
        if((u8)remaining!=0) break;
        {
            /* Real late 28-byte template, after the independent OUT coordinates
             * have become addressable. No fake stack padding or scratch union. */
            struct ResourceTargetEvent child_event;
            struct ResourceTargetEvent *child=&child_event;
            u32 ordinal;
            /* Materialize the real destination before its original H4 load. */
            __asm__("" : : "r"(child));
            ordinal=work->ordinal;
            child->ordinal=(u16)ordinal;
            child->special=work->special;
            child->target=GetDefinitionTarget(work->actor,(u8)ordinal);
            work->children[work->ordinal]=CreateOppositePhaseChild(RunResourceTargetChild,36,
                                                                (const u32 *)child,parent);
        }
        work->byte_delay=40;
        ++work->ordinal;
        if(work->ordinal==work->count) ++event->phase;
        break;
    }
    case 262:
        if((u8)PollDefinitionTaskArray(work->children,5)==0) break;
        work->resource=PollResource(work->resource,0);
        if(work->resource!=0) break;
        work->auxiliary=PollAuxiliary(work->auxiliary);
        if(work->auxiliary!=0) break;
        work->palette=PollPaletteSequence(work->palette);
        if(work->palette!=0) break;
        if((u8)PollRecordHandles(work->record)!=0) event->phase=2;
        break;
    }
    return 0;
}
