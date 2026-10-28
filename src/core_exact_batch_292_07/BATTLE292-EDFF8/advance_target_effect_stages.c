typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Task;
struct Event {u16 state;u8 unused2[2];void *record;u8 unused8[12];u16 mode;u8 unused22[6];};
struct Work {u16 timer;s16 x,y;u8 mode,unused7;void *actor,*record;u8 output16[12];struct Task *positioned,*auxiliary,*palette,*record_effect,*sequence;};
typedef char WorkSize[sizeof(struct Work)==48?1:-1];
extern void *ResolveRecordPosition(void*,s16*,s16*,u32);
extern struct Task *CreatePositioned(s16,s16,u16,u8,u16,void*,const void*,struct Task*);
extern void LoadPositionedResource(const void*,u8,u8,s16,s16,u16);
extern struct Task *CreatePalette(const void*,struct Task*);
extern struct Task *CreateAuxiliary(const void*,struct Task*);
extern struct Task *CreateRecordEffect(void*,const void*,u8,u16,u16,struct Task*,u16);
extern struct Task *CreateStage(const void*,u8,u16,u16,struct Task*);
extern struct Task *PollPositioned(struct Task*);
extern struct Task *PollAuxiliary(struct Task*);
extern struct Task *PollPalette(struct Task*);
extern struct Task *PollRecordEffect(struct Task*);
extern const u8 gPositionSequence[],gResource[],gPalette[],gAuxiliary[],gRecordSequence[],gStageSequence[];
u32 AdvanceTargetEffectStages(struct Task*,struct Event*,struct Work*) __asm__("RemainingBand43_000EDFF8");
u32 AdvanceTargetEffectStages(struct Task *task,struct Event *event,struct Work *work)
{
    switch(event->state) {
    case 0:
        work->record=event->record;
        work->mode=event->mode;
        work->actor=ResolveRecordPosition(work->record,&work->x,&work->y,0);
        break;
    case 256: {
        u16 position_mode;
        u16 stage_flags;
        work->positioned=CreatePositioned(work->x,work->y,0,1,3,work->output16,gPositionSequence,task);
        LoadPositionedResource(gResource,0,2,work->x,work->y,0);
        work->palette=CreatePalette(gPalette,task);
        work->auxiliary=CreateAuxiliary(gAuxiliary,task);
        position_mode=(work->mode&1)?2:4;
        work->record_effect=CreateRecordEffect(work->record,gRecordSequence,12,42,position_mode,task,42);
        stage_flags=(work->mode&1)?8:16;
        work->sequence=CreateStage(gStageSequence,1,stage_flags|4,0,task);
        work->timer=12;
        event->state++;
        break;
    }
    case 257:
        work->auxiliary=PollAuxiliary(work->auxiliary);
        if(work->auxiliary==0) {
            work->palette=PollPalette(work->palette);
            if(work->palette==0) {
                work->positioned=PollPositioned(work->positioned);
                if(work->positioned==0)event->state++;
            }
        }
        break;
    case 258:
        work->record_effect=PollRecordEffect(work->record_effect);
        if(work->record_effect==0)event->state=2;
        break;
    }
    return 0;
}
__asm__(".global gPositionSequence\n.set gPositionSequence,0x83995b8\n.global gResource\n.set gResource,0x88f4f80\n.global gPalette\n.set gPalette,0x89497c0\n.global gAuxiliary\n.set gAuxiliary,0x894d69c\n.global gRecordSequence\n.set gRecordSequence,0x8399600\n.global gStageSequence\n.set gStageSequence,0x8399614\n.global ResolveRecordPosition\n.thumb_set ResolveRecordPosition,0x80dd749\n.global CreatePositioned\n.thumb_set CreatePositioned,0x80d6099\n.global LoadPositionedResource\n.thumb_set LoadPositionedResource,0x80d7221\n.global CreatePalette\n.thumb_set CreatePalette,0x80d4705\n.global CreateAuxiliary\n.thumb_set CreateAuxiliary,0x80d3e9d\n.global CreateRecordEffect\n.thumb_set CreateRecordEffect,0x80dcfe5\n.global CreateStage\n.thumb_set CreateStage,0x80dfd8d\n.global PollPositioned\n.thumb_set PollPositioned,0x80d6135\n.global PollAuxiliary\n.thumb_set PollAuxiliary,0x80d3f09\n.global PollPalette\n.thumb_set PollPalette,0x80d4775\n.global PollRecordEffect\n.thumb_set PollRecordEffect,0x80dba5d\n");
