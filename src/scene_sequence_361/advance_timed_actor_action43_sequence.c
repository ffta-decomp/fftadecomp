typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ActorSequenceContext {u16 state;u8 unknown02[2];void *actor;};
struct ActorActionOutput {u8 unknown00[52];u16 action;};
struct TimedActorSequence {
    u16 timer;u8 unknown02[6];void *actor;
    struct ActorActionOutput *output;void *palette,*overlay;
};
extern const u8 gActionPalette[],gActionOverlay[];
extern struct ActorActionOutput *GetActorActionOutput(void*) asm("RetailCall_080DD350");
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
extern void *CreateDefinitionPaletteTask(const void*,void*) asm("RetailCall_080D4704");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void ApplyDefinitionRecordCurrentValue(void*,u16) asm("RetailCall_080DE10C");
extern void *PollAndReleaseDefinitionPalette(void*) asm("RetailCall_080D4774");
typedef char WorkSize[(sizeof(struct TimedActorSequence)==24)?1:-1];
u32 AdvanceTimedActorAction43Sequence(void*,struct ActorSequenceContext*,struct TimedActorSequence*) asm("OriginalSceneDefinitionQuestion_0011E7E0");
u32 AdvanceTimedActorAction43Sequence(void *owner,struct ActorSequenceContext *context,struct TimedActorSequence *work)
{
    s32 state=context->state;
    switch(state) {
    case 0:
        work->actor=context->actor;
        work->output=GetActorActionOutput(work->actor);
        break;
    case 1:
        RestoreSceneStage();
        break;
    case 256:
        work->palette=CreateDefinitionPaletteTask(gActionPalette,owner);
        work->overlay=StartSceneOverlay(gActionOverlay,1,4,0,owner);
        work->timer=10;
        context->state++;
        break;
    case 257:
        if(--work->timer!=0) break;
        work->output->action=43;
        ApplyDefinitionRecordCurrentValue(work->actor,16);
        context->state++;
        break;
    case 258:
        work->palette=PollAndReleaseDefinitionPalette(work->palette);
        if(work->palette) break;
        context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080DD350\n.thumb_set RetailCall_080DD350,0x080dd351");
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global RetailCall_080D4704\n.thumb_set RetailCall_080D4704,0x080d4705");
__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C,0x080dfd8d");
__asm__(".global RetailCall_080DE10C\n.thumb_set RetailCall_080DE10C,0x080de10d");
__asm__(".global RetailCall_080D4774\n.thumb_set RetailCall_080D4774,0x080d4775");
__asm__(".global gActionPalette\n.set gActionPalette,0x0894c898");
__asm__(".global gActionOverlay\n.set gActionOverlay,0x083a736c");
