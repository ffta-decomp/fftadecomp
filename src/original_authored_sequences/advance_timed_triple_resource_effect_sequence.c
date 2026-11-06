typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
struct TripleEvent {
    u16 phase,unknown02;
    void *record;
    u32 word8,word12,word16;
    u16 definition,variant;
    u32 word24;
};
struct TripleRamp {u16 value;s16 remaining,error;u16 step,period,magnitude;};
struct TripleWork {
    u8 variant,effect_result;
    s16 x,y;
    u16 timer;
    u8 unknown08[4];
    void *record;
    TaskNode *initial,*resources[3];
    struct TripleRamp ramp;
    TaskNode *child,*stage;
};
typedef char TripleEventSize[sizeof(struct TripleEvent)==28?1:-1];
typedef char TripleRampSize[sizeof(struct TripleRamp)==12?1:-1];
typedef char TripleWorkSize[sizeof(struct TripleWork)==52?1:-1];
extern const u8 TripleInitialResource[],TripleStageResource[],TripleObjectResource[];
extern TaskNode *CreateTripleInitial(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupTripleInputs(void);
extern TaskNode *PollTripleInitial(TaskNode *);
extern u32 TriggerTriplePositionEffect(void *,u16,u16,TaskNode *);
extern TaskNode *CreateTripleStage(const void *,u8,u16,u16,TaskNode *);
extern void ReadTripleRecordPosition(void *,s16 *,s16 *);
extern TaskNode *CreateTripleObject(const void *,u8,int,int,u16,u8,u32,u32);
extern void InitializeTripleRamp(struct TripleRamp *,u16,u16,u16);
extern u8 UpdateTripleResources(TaskNode **,struct TripleRamp *,s16,s16);
extern u32 TripleFollowupChild(TaskNode *,struct TripleEvent *,void *);
extern TaskNode *CreateTripleChild(u32 (*)(TaskNode *,struct TripleEvent *,void *),u32,struct TripleEvent *,TaskNode *);
extern TaskNode *PollTripleChild(TaskNode *);

u32 AdvanceTimedTripleResourceEffectSequence(TaskNode *,struct TripleEvent *,struct TripleWork *)
    __asm__("OriginalActionCallback_0010438C");
u32 AdvanceTimedTripleResourceEffectSequence(TaskNode *task,struct TripleEvent *event,struct TripleWork *work)
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
        work->initial=CreateTripleInitial(record,TripleInitialResource,count,1,(const s16 *)(u32)entry_phase,task);
        break;
    }
    case 1:
        CleanupTripleInputs();
        break;
    case 256: {
        u32 effect_result;
        u8 index;
        TaskNode **resources;
        struct TripleRamp *ramp;
        work->initial=PollTripleInitial(work->initial);
        if(work->initial!=0) break;
        effect_result=TriggerTriplePositionEffect(work->record,0,60,task);
        work->effect_result=effect_result;
        if(work->variant!=0) {
            if((u8)effect_result==0) event->phase=259;
            else event->phase=258;
            break;
        }
        work->stage=CreateTripleStage(TripleStageResource,1,4,0,task);
        if(work->effect_result==0) {
            event->phase=259;
            break;
        }
        ReadTripleRecordPosition(work->record,&work->x,&work->y);
        index=0;
        resources=work->resources;
        ramp=&work->ramp;
        do {
            TaskNode *created;
            TaskNode **destination;
            created=CreateTripleObject(TripleObjectResource,index,0,0,997,7,0,0);
            destination=resources+index;
            *destination=created;
            index++;
        } while(index<=2);
        InitializeTripleRamp(ramp,60,316,164);
        UpdateTripleResources(resources,ramp,work->x,work->y);
        work->timer=90;
        event->phase++;
        break;
    }
    case 257:
        UpdateTripleResources(work->resources,&work->ramp,work->x,work->y);
        work->timer--;
        if(work->timer==0) event->phase++;
        break;
    case 258: {
        struct TripleEvent child_event;
        child_event.definition=223;
        child_event.variant=work->variant;
        child_event.record=work->record;
        child_event.word8=0;
        child_event.word12=1;
        work->child=CreateTripleChild(TripleFollowupChild,48,&child_event,task);
        UpdateTripleResources(work->resources,&work->ramp,work->x,work->y);
        event->phase++;
        break;
    }
    case 259:
        if(UpdateTripleResources(work->resources,&work->ramp,work->x,work->y)==0) break;
        work->child=PollTripleChild(work->child);
        if(work->child==0) event->phase=2;
        break;
    }
    return 0;
}
__asm__(".global CreateTripleInitial\n.thumb_set CreateTripleInitial,0x80e03f9");
__asm__(".global CleanupTripleInputs\n.thumb_set CleanupTripleInputs,0x80d38b5");
__asm__(".global PollTripleInitial\n.thumb_set PollTripleInitial,0x80e05dd");
__asm__(".global TriggerTriplePositionEffect\n.thumb_set TriggerTriplePositionEffect,0x80d8925");
__asm__(".global CreateTripleStage\n.thumb_set CreateTripleStage,0x80dfd8d");
__asm__(".global ReadTripleRecordPosition\n.thumb_set ReadTripleRecordPosition,0x80d8c59");
__asm__(".global CreateTripleObject\n.thumb_set CreateTripleObject,0x80d5cc1");
__asm__(".global InitializeTripleRamp\n.thumb_set InitializeTripleRamp,0x80e0609");
__asm__(".global UpdateTripleResources\n.thumb_set UpdateTripleResources,0x81042c9");
__asm__(".global TripleFollowupChild\n.thumb_set TripleFollowupChild,0x80e8b25");
__asm__(".global CreateTripleChild\n.thumb_set CreateTripleChild,0x8005b6d");
__asm__(".global PollTripleChild\n.thumb_set PollTripleChild,0x80e051d");
__asm__(".global TripleInitialResource\n.set TripleInitialResource,0x839f488");
__asm__(".global TripleStageResource\n.set TripleStageResource,0x839f4b8");
__asm__(".global TripleObjectResource\n.set TripleObjectResource,0x8506ba8");
