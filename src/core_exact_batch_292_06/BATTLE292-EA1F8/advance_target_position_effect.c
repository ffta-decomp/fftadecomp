typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Task;
struct Event {u16 state;u8 unused2[2];void *record;u8 unused8[12];u16 mode;u8 unused22[6];};
struct Work {u8 mode;u8 unused1[3];s16 x,y;void *record,*actor;u8 output16[16];struct Task *positioned,*auxiliary,*sequence;};
typedef char WorkSize[sizeof(struct Work)==44?1:-1];
extern void *ResolveRecordPosition(void*,s16*,s16*,u32);
extern struct Task *CreatePositioned(s16,s16,u16,u8,u16,void*,const void*,struct Task*);
extern struct Task *CreateRecordEffect(void*,const void*,u8,u16,u16,struct Task*,u16);
extern struct Task *CreateStage(const void*,u8,u16,u16,struct Task*);
extern struct Task *PollPositioned(struct Task*);
extern struct Task *PollAuxiliary(struct Task*);
extern const u8 gPositionSequence[],gStageSequence[];
u32 AdvanceTargetPositionEffect(struct Task*,struct Event*,struct Work*) __asm__("RemainingBand43_000EA1F8");
u32 AdvanceTargetPositionEffect(struct Task *task,struct Event *event,struct Work *work)
{
    switch(event->state) {
    case 0:
        work->mode=event->mode;
        work->record=event->record;
        work->actor=ResolveRecordPosition(work->record,&work->x,&work->y,0);
        break;
    case 1:break;
    case 256: {
        u16 position_mode;
        u16 stage_flags;
        work->positioned=CreatePositioned(work->x,work->y,0,1,4,work->output16,gPositionSequence,task);
        position_mode=(work->mode&1)?4:2;
        work->auxiliary=CreateRecordEffect(work->record,0,12,0,position_mode,task,50);
        stage_flags=(work->mode&1)?16:8;
        work->sequence=CreateStage(gStageSequence,1,stage_flags|4,0,task);
        event->state++;
        break;
    }
    case 257:
        work->positioned=PollPositioned(work->positioned);
        if(work->positioned==0) {
            work->auxiliary=PollAuxiliary(work->auxiliary);
            if(work->auxiliary==0)event->state=2;
        }
        break;
    }
    return 0;
}
__asm__(".global gPositionSequence\n.set gPositionSequence,0x083988f8\n.global gStageSequence\n.set gStageSequence,0x08398958\n.global ResolveRecordPosition\n.thumb_set ResolveRecordPosition,0x080dd749\n.global CreatePositioned\n.thumb_set CreatePositioned,0x080d6099\n.global CreateRecordEffect\n.thumb_set CreateRecordEffect,0x080dcfe5\n.global CreateStage\n.thumb_set CreateStage,0x080dfd8d\n.global PollPositioned\n.thumb_set PollPositioned,0x080d6135\n.global PollAuxiliary\n.thumb_set PollAuxiliary,0x080dba5d");
