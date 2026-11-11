#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef struct TaskNode TaskNode;
typedef struct DefinitionObject DefinitionObject;
struct VariantEvent {
    u16 phase,unknown02;
    void *record;
    u8 unknown08[12],definition_low,unknown15;
    u16 variant;
    u8 unknown18[4];
};
struct VariantWork {
    u8 variant,index;
    u16 timer;
    u8 direction,unknown05;
    s16 x,y;
    u8 ready,unknown0B;
    DefinitionObject *primary,*secondary_object;
    u8 first_output[8];
    TaskNode *first_positioned;
    u8 followup_output[8];
    TaskNode *followup_positioned;
    u8 extra_output[4];
    TaskNode *extra_positioned,*palette;
    void *record,*actor,*projected,*target;
    TaskNode *initial,*secondary,*actor_sequence,*stage;
};
typedef char VariantEventSize[sizeof(struct VariantEvent)==28?1:-1];
typedef char VariantWorkSize[sizeof(struct VariantWork)==88?1:-1];
extern const u8 VariantInitialResource[],VariantOffsetTable[],VariantIndexTwoObject[],VariantSecondaryObject[];
extern const u8 VariantFirstPositioned[],VariantInitialStage[],VariantActorSequenceResource[];
extern const u8 VariantPaletteSequence[],VariantTargetStage[],VariantFollowupPositioned[],VariantExtraPositioned[];
extern const u8 VariantExtraStage[],VariantSecondaryRows[],VariantIndexedDestination[];
extern TaskNode *CreateVariantInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupVariantInputs(void);
extern TaskNode *PollVariantInitial(TaskNode *);
extern u32 ShouldSkipVariantSequence(void *);
extern void *GetVariantActor(void *);
extern void RestoreVariantActorPresentation(void *);
extern void ReadVariantActorPosition(void *,s16 *,s16 *);
extern void *GetVariantTarget(void *,u8);
extern int ReadVariantActorDirection(void *);
extern void *CopyVariantOffsets(void *,const void *,u32);
extern s16 ReadVariantTargetDefinition(void *);
extern DefinitionObject *CreateVariantIndexedObject(u16,u8,int,int,u16,const void *,u8,TaskNode *);
extern DefinitionObject *CreateVariantObject(const void *,u8,int,int,u16,u8,u32,u32);
extern void SetVariantObjectVariant(DefinitionObject *,u8);
extern void SetVariantObjectSortKey(DefinitionObject *,s16);
extern void SetVariantObjectFlag8(DefinitionObject *,u8);
extern void SetVariantObjectHidden(DefinitionObject *,u8);
extern TaskNode *CreateVariantPositioned(int,int,int,u8,u32,void *,const void *,TaskNode *);
extern void SetVariantPositionedOption(TaskNode *,u8);
extern TaskNode *CreateVariantStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollVariantPositioned(TaskNode *);
extern void ReleaseVariantObject(DefinitionObject *);
extern TaskNode *CreateVariantActorSequence(void *,void **,u16,u8,u8 *,const void *,u32,u32,TaskNode *);
extern void ConfigureVariantRecord(void *,u8,u32);
extern u32 IsVariantSequenceBusy(void);
extern u32 CountVariantTargets(void *,u8);
extern void *ProjectVariantTarget(void *,s16 *,s16 *,u8);
extern u32 TestVariantTargetBit7(void *);
extern void SetVariantObjectCoordinates(DefinitionObject *,int,int,u16);
extern TaskNode *CreateVariantPalette(const void *,TaskNode *,u16);
extern TaskNode *PollVariantPalette(TaskNode *);
extern TaskNode *CreateVariantSecondary(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern u32 IsVariantActorFinished(void *);
extern TaskNode *PollVariantSecondary(TaskNode *);

u32 AdvanceVariantActorResourceHandoff(TaskNode *,struct VariantEvent *,struct VariantWork *)
    __asm__("OriginalActionCallback_00103E14");
u32 AdvanceVariantActorResourceHandoff(TaskNode *task,struct VariantEvent *event,struct VariantWork *work)
{
    u16 entry_phase=event->phase;
    switch(entry_phase) {
    case 0: {
        u16 variant;
        void *record;
        u8 count;
        work->index=event->definition_low+36;
        variant=event->variant;
        work->variant=variant;
        record=event->record;
        work->record=record;
        count=7;
        if((u8)variant!=0) count=0;
        work->initial=CreateVariantInitial(record,VariantInitialResource,count,0,(const s16 *)(u32)entry_phase,task);
        break;
    }
    case 1:
        CleanupVariantInputs();
        break;
    case 256: {
        s16 actor_x,actor_y;
        u8 skip;
        DefinitionObject *secondary_object;
        TaskNode *positioned;
        register void *actor_input __asm__("r0");
        register u32 index_working __asm__("r0");
        work->initial=PollVariantInitial(work->initial);
        if(work->initial!=0) break;
        skip=(u8)ShouldSkipVariantSequence(work->record);
        if(skip!=0) {
            event->phase=2;
            break;
        }
        work->actor=GetVariantActor(work->record);
        RestoreVariantActorPresentation(work->actor);
        actor_input=work->actor;
        __asm__("" : : "r"(actor_input));
        {
        s16 *actor_x_source=&actor_x;
        register s16 *initial_y_source __asm__("r4")=&actor_y;
        u16 offsets[4];
        s16 *actor_y_source;
        __asm__("" : "+r"(initial_y_source));
        ReadVariantActorPosition(actor_input,actor_x_source,initial_y_source);
        work->target=GetVariantTarget(work->record,0);
        work->direction=ReadVariantActorDirection(work->actor);
        index_working=work->index;
        __asm__("" : : "r"(index_working));
        actor_y_source=initial_y_source;
        __asm__("" : "+r"(actor_y_source));
        if(index_working!=2) {
            u32 offset_address;
            u16 definition;
            register u32 offset __asm__("r2");
            register u32 actor_x_working __asm__("r3");
            int object_x,object_y;
            offset_address=(u32)offsets;
            CopyVariantOffsets((void *)offset_address,VariantOffsetTable,8);
            definition=(u16)ReadVariantTargetDefinition(work->target);
            actor_x_working=(u32)&actor_x;
            __asm__("" : : "r"(actor_x_working));
            offset_address+=(u32)work->direction*2;
            offset=*(const u16 *)offset_address;
            __asm__("" : "+r"(offset));
            actor_x_working=*(const u16 *)actor_x_working;
            __asm__("" : "+r"(actor_x_working));
            object_x=(s16)(offset+actor_x_working);
            object_y=(s16)((u16)*actor_y_source-35);
            work->primary=CreateVariantIndexedObject(definition,0,object_x,object_y,skip,
                                                       VariantIndexedDestination,8,task);
        } else {
            u32 offset_address;
            register const void *object_source __asm__("r0");
            register u32 offset __asm__("r2");
            register u32 actor_x_working __asm__("r3");
            int object_x,object_y;
            offset_address=(u32)offsets;
            CopyVariantOffsets((void *)offset_address,VariantOffsetTable,8);
            object_source=VariantIndexTwoObject;
            __asm__("" : "+r"(object_source));
            actor_x_working=(u32)&actor_x;
            __asm__("" : : "r"(actor_x_working));
            offset_address+=(u32)work->direction*2;
            offset=*(const u16 *)offset_address;
            __asm__("" : "+r"(offset));
            actor_x_working=*(const u16 *)actor_x_working;
            __asm__("" : "+r"(actor_x_working));
            object_x=(s16)(offset+actor_x_working);
            object_y=(s16)((u16)*actor_y_source-35);
            work->primary=CreateVariantObject(object_source,0,object_x,object_y,992,8,skip,skip);
        }
        secondary_object=CreateVariantObject(VariantSecondaryObject,0,actor_x,*actor_y_source,1007,6,0,0);
        work->secondary_object=secondary_object;
        if(work->direction>1) SetVariantObjectVariant(secondary_object,1);
        SetVariantObjectSortKey(work->primary,1);
        SetVariantObjectSortKey(work->secondary_object,2);
        SetVariantObjectFlag8(work->primary,1);
        SetVariantObjectFlag8(work->secondary_object,1);
        positioned=CreateVariantPositioned(actor_x,*actor_y_source,0,1,2,work->first_output,
                                             VariantFirstPositioned,task);
        work->first_positioned=positioned;
        if(work->direction>1) SetVariantPositionedOption(positioned,1);
        work->stage=CreateVariantStage(VariantInitialStage,1,4,0,task);
        work->timer=6;
        event->phase++;
        }
        break;
    }
    case 257:
        if(work->timer!=0) {
            work->timer--;
            if(work->timer==0) {
                SetVariantObjectFlag8(work->primary,0);
                SetVariantObjectFlag8(work->secondary_object,0);
            }
        }
        work->first_positioned=PollVariantPositioned(work->first_positioned);
        if(work->first_positioned!=0) break;
        SetVariantObjectFlag8(work->primary,1);
        SetVariantObjectFlag8(work->secondary_object,1);
        work->timer=6;
        event->phase++;
        break;
    case 258: {
        u32 raw_timer,timer_working;
        raw_timer=(u32)work->timer-1;
        work->timer=raw_timer;
        timer_working=(u16)raw_timer;
        if(timer_working!=0) break;
        SetVariantObjectFlag8(work->primary,0);
        SetVariantObjectHidden(work->primary,0);
        ReleaseVariantObject(work->secondary_object);
        work->secondary_object=(DefinitionObject *)(u32)timer_working;
        work->actor_sequence=CreateVariantActorSequence(work->record,0,0x8007,1,&work->ready,
                                                           VariantActorSequenceResource,5,timer_working,task);
        event->phase++;
        break;
    }
    case 259:
        if(work->ready==0) break;
        ConfigureVariantRecord(work->record,0,0);
        work->timer=10;
        event->phase++;
        /* The original immediately enters the following timer stage. */
    case 260: {
        u8 target_count,target_flag;
        if(work->timer!=0) {
            work->timer--;
            if(work->timer!=0) break;
        }
        if((u8)IsVariantSequenceBusy()!=0) break;
        target_count=(u8)CountVariantTargets(work->record,0);
        if(target_count==0) {
            ReleaseVariantObject(work->primary);
            work->primary=(DefinitionObject *)(u32)target_count;
            event->phase=2;
            break;
        }
        work->projected=ProjectVariantTarget(work->target,&work->x,&work->y,0);
        target_flag=(u8)TestVariantTargetBit7(work->target);
        if(target_flag==0) {
            ReleaseVariantObject(work->primary);
            work->primary=(DefinitionObject *)(u32)target_flag;
            event->phase=262;
            break;
        }
        SetVariantObjectHidden(work->primary,1);
        SetVariantObjectCoordinates(work->primary,work->x,(s16)((u16)work->y-32),0);
        work->palette=CreateVariantPalette(VariantPaletteSequence,task,20);
        work->stage=CreateVariantStage(VariantTargetStage,1,4,0,task);
        event->phase++;
        break;
    }
    case 261: {
        TaskNode *completed;
        completed=PollVariantPalette(work->palette);
        work->palette=completed;
        if(completed!=0) break;
        ReleaseVariantObject(work->primary);
        work->primary=(DefinitionObject *)completed;
        work->followup_positioned=CreateVariantPositioned(work->x,work->y,0,1,2,work->followup_output,
                                                            VariantFollowupPositioned,task);
        if(work->index==2 && (u8)TestVariantTargetBit7(work->target)!=0) {
            work->extra_positioned=CreateVariantPositioned(work->x,work->y,0,1,1,work->extra_output,
                                                             VariantExtraPositioned,task);
            work->stage=CreateVariantStage(VariantExtraStage,1,4,0,task);
        }
        event->phase++;
        break;
    }
    case 262: {
        TaskNode *completed;
        work->followup_positioned=PollVariantPositioned(work->followup_positioned);
        if(work->followup_positioned!=0) break;
        completed=PollVariantPositioned(work->extra_positioned);
        work->extra_positioned=completed;
        if(completed!=0) break;
        work->secondary=CreateVariantSecondary(work->target,
            (const void *)((u32)VariantSecondaryRows+(u32)work->index*20),12,0,12,task,(u32)completed);
        event->phase++;
        break;
    }
    case 263:
        if((u8)IsVariantActorFinished(work->actor)==0) break;
        work->secondary=PollVariantSecondary(work->secondary);
        if(work->secondary==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateVariantInitial\n.thumb_set CreateVariantInitial,0x80e03f9");
__asm__(".global CleanupVariantInputs\n.thumb_set CleanupVariantInputs,0x80d38b5");
__asm__(".global PollVariantInitial\n.thumb_set PollVariantInitial,0x80e05dd");
__asm__(".global ShouldSkipVariantSequence\n.thumb_set ShouldSkipVariantSequence,0x80d3b55");
__asm__(".global GetVariantActor\n.thumb_set GetVariantActor,0x80dd47d");
__asm__(".global RestoreVariantActorPresentation\n.thumb_set RestoreVariantActorPresentation,0x80de391");
__asm__(".global ReadVariantActorPosition\n.thumb_set ReadVariantActorPosition,0x80dbdc9");
__asm__(".global GetVariantTarget\n.thumb_set GetVariantTarget,0x80dd4a5");
__asm__(".global ReadVariantActorDirection\n.thumb_set ReadVariantActorDirection,0x80dbc89");
__asm__(".global CopyVariantOffsets\n.thumb_set CopyVariantOffsets,0x81443fd");
__asm__(".global ReadVariantTargetDefinition\n.thumb_set ReadVariantTargetDefinition,0x80dd56d");
__asm__(".global CreateVariantIndexedObject\n.thumb_set CreateVariantIndexedObject,0x80d5fd9");
__asm__(".global CreateVariantObject\n.thumb_set CreateVariantObject,0x80d5cc1");
__asm__(".global SetVariantObjectVariant\n.thumb_set SetVariantObjectVariant,0x8011119");
__asm__(".global SetVariantObjectSortKey\n.thumb_set SetVariantObjectSortKey,0x8011059");
__asm__(".global SetVariantObjectFlag8\n.thumb_set SetVariantObjectFlag8,0x80111a9");
__asm__(".global SetVariantObjectHidden\n.thumb_set SetVariantObjectHidden,0x801115d");
__asm__(".global CreateVariantPositioned\n.thumb_set CreateVariantPositioned,0x80d6099");
__asm__(".global SetVariantPositionedOption\n.thumb_set SetVariantPositionedOption,0x80d6195");
__asm__(".global CreateVariantStage\n.thumb_set CreateVariantStage,0x80dfd8d");
__asm__(".global PollVariantPositioned\n.thumb_set PollVariantPositioned,0x80d6135");
__asm__(".global ReleaseVariantObject\n.thumb_set ReleaseVariantObject,0x8011429");
__asm__(".global CreateVariantActorSequence\n.thumb_set CreateVariantActorSequence,0x80ddf69");
__asm__(".global ConfigureVariantRecord\n.thumb_set ConfigureVariantRecord,0x80dc12d");
__asm__(".global IsVariantSequenceBusy\n.thumb_set IsVariantSequenceBusy,0x80d8b4d");
__asm__(".global CountVariantTargets\n.thumb_set CountVariantTargets,0x80d8859");
__asm__(".global ProjectVariantTarget\n.thumb_set ProjectVariantTarget,0x80dd749");
__asm__(".global TestVariantTargetBit7\n.thumb_set TestVariantTargetBit7,0x80dd581");
__asm__(".global SetVariantObjectCoordinates\n.thumb_set SetVariantObjectCoordinates,0x80107d5");
__asm__(".global CreateVariantPalette\n.thumb_set CreateVariantPalette,0x80d4725");
__asm__(".global PollVariantPalette\n.thumb_set PollVariantPalette,0x80d4775");
__asm__(".global CreateVariantSecondary\n.thumb_set CreateVariantSecondary,0x80dcfe5");
__asm__(".global IsVariantActorFinished\n.thumb_set IsVariantActorFinished,0x80de245");
__asm__(".global PollVariantSecondary\n.thumb_set PollVariantSecondary,0x80dba5d");
__asm__(".global VariantInitialResource\n.set VariantInitialResource,0x839f31c");
__asm__(".global VariantOffsetTable\n.set VariantOffsetTable,0x8149e30");
__asm__(".global VariantIndexTwoObject\n.set VariantIndexTwoObject,0x85028e0");
__asm__(".global VariantSecondaryObject\n.set VariantSecondaryObject,0x8502630");
__asm__(".global VariantFirstPositioned\n.set VariantFirstPositioned,0x839f370");
__asm__(".global VariantInitialStage\n.set VariantInitialStage,0x839f428");
__asm__(".global VariantActorSequenceResource\n.set VariantActorSequenceResource,0x839f424");
__asm__(".global VariantPaletteSequence\n.set VariantPaletteSequence,0x894a76c");
__asm__(".global VariantTargetStage\n.set VariantTargetStage,0x839f430");
__asm__(".global VariantFollowupPositioned\n.set VariantFollowupPositioned,0x839f3a0");
__asm__(".global VariantExtraPositioned\n.set VariantExtraPositioned,0x839f3d0");
__asm__(".global VariantExtraStage\n.set VariantExtraStage,0x839f438");
__asm__(".global VariantSecondaryRows\n.set VariantSecondaryRows,0x839f3e8");
__asm__(".global VariantIndexedDestination\n.set VariantIndexedDestination,0x6017c00");
