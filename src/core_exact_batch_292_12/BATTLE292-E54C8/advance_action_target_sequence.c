typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Task;
struct Event {u16 state;u8 unused2[2];void *record;u8 unused8[12];u16 index,mode;u8 unused24[4];};
/* Slot four aliases the palette handle and is also the native all-busy destination. */
struct Work {u8 count,index,delay,mode;struct Task *prelude,*second,*targets[5];void *action;struct Task *opening;u32 unused40;};
typedef char WorkSize[sizeof(struct Work)==44?1:-1];
extern struct Task *CreateTask(const void*,u32,struct Event*,struct Task*);
extern struct Task *CreateOpening(void*,const void*,u8,u8,u16,struct Task*);
extern struct Task *PollOpening(struct Task*);
extern struct Task *PollTask(struct Task*);
extern struct Task *CreatePalette(const void*,struct Task*);
extern struct Task *PollPalette(struct Task*);
extern u32 CountTargets(void*,u8);
extern void *GetTarget(void*,u8);
extern u32 PollTargets(struct Task**,u8);
extern void RunService(void);
extern const u8 gOpeningDefinition[],gPreludeEntry[],gSecondEntry[],gTargetEntry[],gPaletteDefinition[];
u32 AdvanceActionTargetSequence(struct Task*,struct Event*,struct Work*) __asm__("Battle292_000E54C8");
u32 AdvanceActionTargetSequence(struct Task *parent,struct Event *event,struct Work *work)
{
    switch(event->state) {
    case 0: {
        u8 opening_index;
        void *action;
        work->mode=event->mode;
        action=event->record;
        work->action=action;
        opening_index=5;
        if(work->mode!=0)opening_index=0;
        work->opening=CreateOpening(action,gOpeningDefinition,opening_index,1,0,parent);
        break;
    }
    case 1:RunService();break;
    case 256:
        work->opening=PollOpening(work->opening);
        if(work->opening!=0)break;
        work->delay=1;
        if(work->mode!=0) {
            work->count=CountTargets(work->action,0);
            event->state=259;
        } else {
            struct Event prelude_event;
            work->prelude=CreateTask(gPreludeEntry,116,&prelude_event,parent);
            work->targets[4]=CreatePalette(gPaletteDefinition,parent);
            event->state++;
        }
        break;
    case 257:
        work->prelude=PollTask(work->prelude);
        if(work->prelude==0) {
            struct Event second_event;
            work->second=CreateTask(gSecondEntry,44,&second_event,parent);
            event->state++;
        }
        break;
    case 258:
        work->second=PollTask(work->second);
        if(work->second!=0)break;
        work->targets[4]=PollPalette(work->targets[4]);
        if(work->targets[4]!=0)break;
        work->index=0;
        work->count=CountTargets(work->action,0);
        if(work->count!=0)event->state++;
        else event->state=2;
        break;
    case 259: {
        u8 slot;
        struct Event target_event;
        PollTargets(work->targets,4);
        work->delay--;
        if(work->delay!=0)break;
        slot=0;
        if(work->targets[0]!=0) {
            do {
                slot++;
                if(slot>3)break;
            } while(work->targets[slot]!=0);
        }
        /* Native all-busy behavior selects slot four, aliasing the next word. */
        target_event.index=work->index;
        target_event.record=GetTarget(work->action,work->index);
        work->targets[slot]=CreateTask(gTargetEntry,20,&target_event,parent);
        work->delay=30;
        work->index++;
        if(work->index==work->count)event->state++;
        break;
    }
    case 260:
        if((u8)PollTargets(work->targets,4))event->state=2;
        break;
    }
    return 0;
}
__asm__(".global CreateTask\n.thumb_set CreateTask,0x08005b6d\n.global CreateOpening\n.thumb_set CreateOpening,0x080e03f9\n.global PollOpening\n.thumb_set PollOpening,0x080e05dd\n.global PollTask\n.thumb_set PollTask,0x080e051d\n.global CreatePalette\n.thumb_set CreatePalette,0x080d4705\n.global PollPalette\n.thumb_set PollPalette,0x080d4775\n.global CountTargets\n.thumb_set CountTargets,0x080d8859\n.global GetTarget\n.thumb_set GetTarget,0x080dd4a5\n.global PollTargets\n.thumb_set PollTargets,0x080e0571\n.global RunService\n.thumb_set RunService,0x080d38b5\n.global gOpeningDefinition\n.set gOpeningDefinition,0x08396ddc\n.global gPreludeEntry\n.set gPreludeEntry,0x080e4eb1\n.global gSecondEntry\n.set gSecondEntry,0x080e5311\n.global gTargetEntry\n.set gTargetEntry,0x080e5439\n.global gPaletteDefinition\n.set gPaletteDefinition,0x0894adac");
