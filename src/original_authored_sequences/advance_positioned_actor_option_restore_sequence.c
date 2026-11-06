typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
struct RestoreEvent {u16 phase,unknown02;void *record;u8 unknown08[12];u16 definition,variant;u8 unknown18[4];};
struct RestoreWork {
    u8 unknown00[2],variant,saved_option;
    s16 x,y;
    void *projected;
    u8 positioned_output[16];
    TaskNode *positioned,*auxiliary,*initial;
    void *record;
    TaskNode *secondary,*stage;
};
typedef char RestoreEventSize[sizeof(struct RestoreEvent)==28?1:-1];
typedef char RestoreWorkSize[sizeof(struct RestoreWork)==52?1:-1];
extern const u8 RestoreInitialResource[],RestorePositionedResource[],RestoreStageResource[],RestoreAuxiliaryResource[];
extern TaskNode *CreateRestoreInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupRestoreInputs(void);
extern TaskNode *PollRestoreInitial(TaskNode *);
extern u32 CountRestoreTargets(void *,u8);
extern void *GetRestoreTarget(void *,u8);
extern void *ProjectRestoreTarget(void *,s16 *,s16 *,u8);
extern TaskNode *CreateRestorePositioned(int,int,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateRestoreSecondary(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern TaskNode *CreateRestoreStage(const void *,u8,u16,u16,TaskNode *);
extern u32 ReadProjectedOption(void *,u8);
extern u32 TestRestoreTargetBit7(void *);
extern TaskNode *CreateRestoreAuxiliary(const void *,TaskNode *);
extern void SetRestoreActorMode(void *,u32);
extern TaskNode *PollRestorePositioned(TaskNode *);
extern TaskNode *PollRestoreAuxiliary(TaskNode *);
extern TaskNode *PollRestoreSecondary(TaskNode *);
extern void WriteProjectedOption(void *,u8);

u32 AdvancePositionedActorOptionRestoreSequence(TaskNode *,struct RestoreEvent *,struct RestoreWork *)
    __asm__("OriginalActionCallback_00100D00");
u32 AdvancePositionedActorOptionRestoreSequence(TaskNode *task,struct RestoreEvent *event,struct RestoreWork *work)
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
        count=2;
        if((u8)variant!=0) count=0;
        work->initial=CreateRestoreInitial(record,RestoreInitialResource,count,1,(const s16 *)(u32)entry_phase,task);
        break;
    }
    case 1:
        CleanupRestoreInputs();
        break;
    case 256: {
        void *target;
        work->initial=PollRestoreInitial(work->initial);
        if(work->initial!=0) break;
        if((u8)CountRestoreTargets(work->record,0)==0) {
            event->phase=2;
            break;
        }
        target=GetRestoreTarget(work->record,0);
        work->projected=ProjectRestoreTarget(target,&work->x,&work->y,0);
        work->positioned=CreateRestorePositioned(work->x,work->y,0,1,4,work->positioned_output,
                                                 RestorePositionedResource,task);
        work->secondary=CreateRestoreSecondary(target,0,12,0,4,task,40);
        work->stage=CreateRestoreStage(RestoreStageResource,1,4,0,task);
        work->saved_option=ReadProjectedOption(work->projected,9);
        if((u8)TestRestoreTargetBit7(target)!=0) {
            work->auxiliary=CreateRestoreAuxiliary(RestoreAuxiliaryResource,task);
            SetRestoreActorMode(work->projected,80);
        }
        event->phase++;
        break;
    }
    case 257:
        work->positioned=PollRestorePositioned(work->positioned);
        if(work->positioned!=0) break;
        work->auxiliary=PollRestoreAuxiliary(work->auxiliary);
        if(work->auxiliary!=0) break;
        work->secondary=PollRestoreSecondary(work->secondary);
        if(work->secondary!=0) break;
        WriteProjectedOption(work->projected,work->saved_option);
        event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateRestoreInitial\n.thumb_set CreateRestoreInitial,0x80e03f9");
__asm__(".global CleanupRestoreInputs\n.thumb_set CleanupRestoreInputs,0x80d38b5");
__asm__(".global PollRestoreInitial\n.thumb_set PollRestoreInitial,0x80e05dd");
__asm__(".global CountRestoreTargets\n.thumb_set CountRestoreTargets,0x80d8859");
__asm__(".global GetRestoreTarget\n.thumb_set GetRestoreTarget,0x80dd4a5");
__asm__(".global ProjectRestoreTarget\n.thumb_set ProjectRestoreTarget,0x80dd749");
__asm__(".global CreateRestorePositioned\n.thumb_set CreateRestorePositioned,0x80d6099");
__asm__(".global CreateRestoreSecondary\n.thumb_set CreateRestoreSecondary,0x80dcfe5");
__asm__(".global CreateRestoreStage\n.thumb_set CreateRestoreStage,0x80dfd8d");
__asm__(".global ReadProjectedOption\n.thumb_set ReadProjectedOption,0x80dbc59");
__asm__(".global TestRestoreTargetBit7\n.thumb_set TestRestoreTargetBit7,0x80dd581");
__asm__(".global CreateRestoreAuxiliary\n.thumb_set CreateRestoreAuxiliary,0x80d4705");
__asm__(".global SetRestoreActorMode\n.thumb_set SetRestoreActorMode,0x80de10d");
__asm__(".global PollRestorePositioned\n.thumb_set PollRestorePositioned,0x80d6135");
__asm__(".global PollRestoreAuxiliary\n.thumb_set PollRestoreAuxiliary,0x80d4775");
__asm__(".global PollRestoreSecondary\n.thumb_set PollRestoreSecondary,0x80dba5d");
__asm__(".global WriteProjectedOption\n.thumb_set WriteProjectedOption,0x80dbc19");
__asm__(".global RestoreInitialResource\n.set RestoreInitialResource,0x839ea24");
__asm__(".global RestorePositionedResource\n.set RestorePositionedResource,0x839ea3c");
__asm__(".global RestoreStageResource\n.set RestoreStageResource,0x839ea9c");
__asm__(".global RestoreAuxiliaryResource\n.set RestoreAuxiliaryResource,0x894bdf8");
__asm__(".balign 4,0");
