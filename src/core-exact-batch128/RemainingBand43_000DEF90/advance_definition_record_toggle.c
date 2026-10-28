typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
typedef struct Startup { u16 selector, flags; u32 parameter; void *record; } Startup;
typedef struct Event { u16 state, unknown2; Startup *startup; u32 unknown8[5]; } Event;
typedef struct Payload { u16 unknown0, selector; u32 parameter; void *record; TaskNode *pending; u16 sequence[5]; u16 unknown26; } Payload;
typedef void (*CopyRoutine)(void *,const void *,u32);
extern CopyRoutine const gCopyRoutine;
extern const u8 gToggleSequence[10];
extern void CallCopy(void *,const void *,u32,CopyRoutine);
extern TaskNode *CreateAuxiliary(const void *,TaskNode *);
extern TaskNode *PollAuxiliary(TaskNode *);
extern void SetRecordVisibility(void *,u8,u8);
extern void SetSelectedVisibility(u8,u8,u8,void *,u32);
extern void SetRecordFlag(void *,u8);
extern void SetSelectedFlag(u8,u8,void *,u32);
u32 RemainingBand43_000DEF90(TaskNode *task, Event *event, Payload *payload)
{
    Startup *startup;
    CopyRoutine const *copy_cell;
    switch(event->state) {
    case 0:
        startup=event->startup;
        payload->selector=startup->selector;
        payload->parameter=startup->parameter;
        payload->record=startup->record;
        copy_cell=&gCopyRoutine;
        CallCopy(payload->sequence,gToggleSequence,10,*copy_cell);
        payload->sequence[3]=startup->flags;
        break;
    case 256:
        payload->pending=CreateAuxiliary(payload->sequence,task);
        if ((s16)payload->selector == -1)
            SetRecordVisibility((void *)payload->parameter,1,1);
        else
            SetSelectedVisibility((u8)payload->selector,1,1,(void *)payload->parameter,(u32)payload->record);
        event->state++;
        break;
    case 257:
        payload->pending=PollAuxiliary(payload->pending);
        if (payload->pending) break;
        if ((s16)payload->selector == -1) {
            SetRecordFlag((void *)payload->parameter,0);
            SetRecordVisibility((void *)payload->parameter,0,1);
        } else {
            SetSelectedFlag((u8)payload->selector,0,(void *)payload->parameter,(u32)payload->record);
            SetSelectedVisibility((u8)payload->selector,0,1,(void *)payload->parameter,(u32)payload->record);
        }
        event->state=2;
        break;
    case 1:
        break;
    }
    return 0;
}
asm(".global gCopyRoutine\n.set gCopyRoutine,0x0836d4bc\n.global gToggleSequence\n.set gToggleSequence,0x08395618\n.global CallCopy\n.thumb_set CallCopy,0x08142251\n.global CreateAuxiliary\n.thumb_set CreateAuxiliary,0x080d3e9d\n.global PollAuxiliary\n.thumb_set PollAuxiliary,0x080d3f09\n.global SetRecordVisibility\n.thumb_set SetRecordVisibility,0x080dd7b1\n.global SetSelectedVisibility\n.thumb_set SetSelectedVisibility,0x080dd809\n.global SetRecordFlag\n.thumb_set SetRecordFlag,0x080dbeb5\n.global SetSelectedFlag\n.thumb_set SetSelectedFlag,0x080dbed5\n");
