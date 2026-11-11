#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef struct TaskNode TaskNode;
struct DirectionEvent {u16 phase,unknown02;void *record;u8 unknown08[12];u16 definition,variant;u8 unknown18[4];};
struct DirectionWork {
    u8 unknown00[2],variant,ready,direction,unknown05;
    s16 x,y;
    u8 unknown0A[2];
    TaskNode *bridge;
    void *actor,*projected,*target;
    TaskNode *secondary_resource,*primary_resource,*positioned;
    u8 positioned_output[4];
    void *record;
    TaskNode *initial,*secondary,*stage;
};
typedef char DirectionEventSize[sizeof(struct DirectionEvent)==28?1:-1];
typedef char DirectionWorkSize[sizeof(struct DirectionWork)==60?1:-1];
extern const u8 DirectionInitialResource[],DirectionPrimaryResource[],DirectionSecondaryResource[];
extern const u8 DirectionPositionedResource[],DirectionFollowupResource[],DirectionInitialStage[],DirectionFollowupStage[];
extern const u8 DirectionImageTable[],DirectionVariantTable[];
extern TaskNode *CreateDirectionInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDirectionInputs(void);
extern TaskNode *PollDirectionInitial(TaskNode *);
extern TaskNode *CreateDirectionBridge(void *,u8,void *,TaskNode *);
extern void *CopyDirectionTable(void *,const void *,u32);
extern void *GetDirectionActor(void *);
extern void *GetDirectionTarget(void *,u8);
extern void *ProjectDirectionTarget(void *,s16 *,s16 *,u8);
extern u32 CompareProjectedDirection(void *,void *);
extern TaskNode *CreateDirectionResource(const void *,u8,int,int,u16,u8,u32,u32);
extern void SetDirectionResourceVariant(void *,u8);
extern TaskNode *CreateDirectionStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollDirectionResource(TaskNode *);
extern u32 TestDirectionTargetBit7(void *);
extern TaskNode *CreateDirectionPositioned(int,int,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateDirectionFollowup(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern TaskNode *PollDirectionPositioned(TaskNode *);
extern TaskNode *PollDirectionBridge(TaskNode *);
extern TaskNode *PollDirectionFollowup(TaskNode *);

u32 AdvanceDirectionalActorResourceSequence(TaskNode *,struct DirectionEvent *,struct DirectionWork *)
    __asm__("OriginalActionCallback_00101A8C");
u32 AdvanceDirectionalActorResourceSequence(TaskNode *task,struct DirectionEvent *event,struct DirectionWork *work)
{
    u16 entry_phase=event->phase;
    switch(entry_phase) {
    case 0: {
        u16 variant;
        void *record;
        u8 count;
        variant=event->variant;
        work->variant=variant;
        record=event->record;
        work->record=record;
        count=4;
        if((u8)variant!=0) count=0;
        work->initial=CreateDirectionInitial(record,DirectionInitialResource,count,0,(const s16 *)(u32)entry_phase,task);
        break;
    }
    case 1:
        CleanupDirectionInputs();
        break;
    case 256:
        work->initial=PollDirectionInitial(work->initial);
        if(work->initial!=0) break;
        work->bridge=CreateDirectionBridge(work->record,2,&work->ready,task);
        if(work->bridge==0) event->phase=2;
        else event->phase++;
        break;
    case 257: {
        u8 images[4],variants[4];
        u8 *variant_base;
        CopyDirectionTable(images,DirectionImageTable,4);
        variant_base=variants;
        CopyDirectionTable(variant_base,DirectionVariantTable,4);
        if(work->ready==0) break;
        if(work->ready==2) {
            event->phase=259;
            break;
        }
        work->actor=GetDirectionActor(work->record);
        work->target=GetDirectionTarget(work->record,0);
        work->projected=ProjectDirectionTarget(work->target,&work->x,&work->y,0);
        work->direction=CompareProjectedDirection(work->projected,work->actor);
        work->primary_resource=CreateDirectionResource(DirectionPrimaryResource,
            *(const u8 *)((u32)images+(u32)work->direction),work->x,work->y,917,7,0,0);
        work->secondary_resource=CreateDirectionResource(DirectionSecondaryResource,6,work->x,work->y,947,6,0,0);
        SetDirectionResourceVariant(work->primary_resource,
            *(const u8 *)((u32)variant_base+(u32)work->direction));
        if(work->direction>1) SetDirectionResourceVariant(work->secondary_resource,1);
        work->stage=CreateDirectionStage(DirectionInitialStage,1,4,0,task);
        event->phase++;
        break;
    }
    case 258: {
        TaskNode *completed;
        completed=PollDirectionResource(work->primary_resource);
        work->primary_resource=completed;
        if(completed!=0) break;
        if((u8)TestDirectionTargetBit7(work->target)!=0) {
            work->positioned=CreateDirectionPositioned(work->x,work->y,0,1,1,work->positioned_output,
                                                       DirectionPositionedResource,task);
            work->stage=CreateDirectionStage(DirectionFollowupStage,1,4,0,task);
        }
        work->secondary=CreateDirectionFollowup(work->target,DirectionFollowupResource,12,40,4,task,(u32)completed);
        event->phase++;
        break;
    }
    case 259:
        work->secondary_resource=PollDirectionResource(work->secondary_resource);
        if(work->secondary_resource!=0) break;
        work->positioned=PollDirectionPositioned(work->positioned);
        if(work->positioned!=0) break;
        work->bridge=PollDirectionBridge(work->bridge);
        if(work->bridge!=0) break;
        work->secondary=PollDirectionFollowup(work->secondary);
        if(work->secondary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateDirectionInitial\n.thumb_set CreateDirectionInitial,0x80e03f9");
__asm__(".global CleanupDirectionInputs\n.thumb_set CleanupDirectionInputs,0x80d38b5");
__asm__(".global PollDirectionInitial\n.thumb_set PollDirectionInitial,0x80e05dd");
__asm__(".global CreateDirectionBridge\n.thumb_set CreateDirectionBridge,0x8102b49");
__asm__(".global CopyDirectionTable\n.thumb_set CopyDirectionTable,0x81443fd");
__asm__(".global GetDirectionActor\n.thumb_set GetDirectionActor,0x80dd47d");
__asm__(".global GetDirectionTarget\n.thumb_set GetDirectionTarget,0x80dd4a5");
__asm__(".global ProjectDirectionTarget\n.thumb_set ProjectDirectionTarget,0x80dd749");
__asm__(".global CompareProjectedDirection\n.thumb_set CompareProjectedDirection,0x80dbcd5");
__asm__(".global CreateDirectionResource\n.thumb_set CreateDirectionResource,0x80d5cc1");
__asm__(".global SetDirectionResourceVariant\n.thumb_set SetDirectionResourceVariant,0x8011119");
__asm__(".global CreateDirectionStage\n.thumb_set CreateDirectionStage,0x80dfd8d");
__asm__(".global PollDirectionResource\n.thumb_set PollDirectionResource,0x8011485");
__asm__(".global TestDirectionTargetBit7\n.thumb_set TestDirectionTargetBit7,0x80dd581");
__asm__(".global CreateDirectionPositioned\n.thumb_set CreateDirectionPositioned,0x80d6099");
__asm__(".global CreateDirectionFollowup\n.thumb_set CreateDirectionFollowup,0x80dcfe5");
__asm__(".global PollDirectionPositioned\n.thumb_set PollDirectionPositioned,0x80d6135");
__asm__(".global PollDirectionBridge\n.thumb_set PollDirectionBridge,0x8102ba9");
__asm__(".global PollDirectionFollowup\n.thumb_set PollDirectionFollowup,0x80dba5d");
__asm__(".global DirectionInitialResource\n.set DirectionInitialResource,0x839ed34");
__asm__(".global DirectionPrimaryResource\n.set DirectionPrimaryResource,0x8502560");
__asm__(".global DirectionSecondaryResource\n.set DirectionSecondaryResource,0x8502ed8");
__asm__(".global DirectionPositionedResource\n.set DirectionPositionedResource,0x839ed64");
__asm__(".global DirectionFollowupResource\n.set DirectionFollowupResource,0x839ed7c");
__asm__(".global DirectionInitialStage\n.set DirectionInitialStage,0x839ed90");
__asm__(".global DirectionFollowupStage\n.set DirectionFollowupStage,0x839ed98");
__asm__(".global DirectionImageTable\n.set DirectionImageTable,0x8149dd8");
__asm__(".global DirectionVariantTable\n.set DirectionVariantTable,0x8149ddc");
