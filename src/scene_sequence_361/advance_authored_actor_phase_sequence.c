typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *record;u8 unknown08[12];s16 definition;u16 selector;};
struct ActorPhaseSequence {
    s16 x,y;u16 delay;u8 special,direct,selector,actor_ready,gate,phase;
    void *actor,*coordinate_state,*actor_record,*child_a,*child_b,*record,*prelude;
    void *positioned_output,*positioned,*resource,*movement,*overlay;
};
struct SceneEvent {u32 unknown00;void *record;u8 *phase;u8 unknown12[16];};
extern u16 gScenePalette[];
extern const u8 gActorPrelude[],gActorResource[],gActorTransition[],gInitialPositionedSequence[],gInitialOverlay[],gMiddleOverlay[],gFinalPositionedSequence[],gFinalResource[];
extern void ActorPhaseCallbackA(void) asm("ActorPhaseCallbackASymbol");
extern void ActorPhaseCallbackB(void) asm("ActorPhaseCallbackBSymbol");
extern void *StartActorPrelude(void*,const void*,u32,u32,u32,void*) asm("RetailCall_080E03F8");
extern void RestoreSceneStage(void) asm("RetailCall_080D38B4");
extern void *PollActorPrelude(void*) asm("RetailCall_080E05DC");
extern u8 IsRecordSceneBlocked(void*) asm("RetailCall_080D3B54");
extern void *ResolveRecordActor(void*) asm("RetailCall_080DD47C");
extern void SetActorSceneResource(const void*,u32,u32,u32,u32) asm("RetailCall_080D45D0");
extern u16 ReadActorKind(void*) asm("RetailCall_080DD6E0");
extern void *StartRecordActorTransition(void*,void**,u16,u8,u8*,const void*,u16,u16,void*) asm("RetailCall_080DDF68");
extern void SetActorMode(void*,u32) asm("RetailCall_080DD720");
extern void SetActorSequenceFrame(void*,u32,u32) asm("RetailCall_080DE150");
extern void *StartDirectActorTransition(void*,u8*,u32,u32,u32,u32,u32,void*) asm("RetailCall_080DE4B0");
extern void ReadActorCoordinates(void*,s16*,s16*) asm("RetailCall_080DBDC8");
extern void *StartPositionedSequence(s32,s32,s32,u8,u32,void*,const void*,void*) asm("RetailCall_080D6098");
extern void *StartSceneOverlay(const void*,u32,u32,u32,void*) asm("RetailCall_080DFD8C");
extern void *PollPositionedSequence(void*) asm("RetailCall_080D6134");
extern void SetRecordSceneState(void*,u32) asm("RetailCall_080DBFFC");
extern u8 IsSceneStageBusy(void) asm("RetailCall_080D8B4C");
extern u8 IsRecordPhaseAvailable(void*,u32) asm("RetailCall_080D8858");
extern void *CreateSceneTask(void(*)(void),u32,const struct SceneEvent*,void*) asm("RetailCall_08005B6C");
extern void *ResolveRecordActorPhase(void*,u32) asm("RetailCall_080DD4A4");
extern void *ReadActorPhaseCoordinates(void*,s16*,s16*,u32) asm("RetailCall_080DD748");
extern void DeleteSceneTask(void*) asm("RetailCall_08005B58");
extern void *StartActorPhaseResource(void*,const void*,u32,u32,u32,void*,u32) asm("RetailCall_080DCFE4");
extern void *PollSceneTask(void*) asm("RetailCall_080E051C");
extern u8 IsActorSequenceFinished(void*) asm("RetailCall_080DE1F0");
extern void *PollActorPhaseResource(void*) asm("RetailCall_080DBA5C");
typedef char WorkSize[(sizeof(struct ActorPhaseSequence)==60)?1:-1];
typedef char EventSize[(sizeof(struct SceneEvent)==28)?1:-1];
u32 AdvanceActorPhaseSequence(void*,struct SceneContext*,struct ActorPhaseSequence*) asm("OriginalSceneDefinitionChild_00115D74");
u32 AdvanceActorPhaseSequence(void *owner,struct SceneContext *context,struct ActorPhaseSequence *work)
{
    struct SceneEvent first_event;
    struct SceneEvent second_event;
    s32 state=context->state;
    switch(state) {
    case 0: {
        u32 initial_mode;
        u32 mode;
        work->special=state;
        work->direct=state;
        initial_mode=0;
        if(context->definition==315) {
            work->special=1;
        } else if(context->definition==391) {
            work->special=1;
            work->direct=1;
            initial_mode=7;
        }
        if(!work->direct) {
            work->selector=context->selector;
            work->record=context->record;
        } else work->actor=context->record;
        mode=5;
        if(work->selector) mode=0;
        work->prelude=StartActorPrelude(work->record,gActorPrelude,mode,initial_mode,0,owner);
        gScenePalette[113]=0x39CE;
        break;
    }
    case 1:
        RestoreSceneStage();
        break;
    case 256: {
        void *completed=PollActorPrelude(work->prelude);
        work->prelude=completed;
        if(completed) break;
        if(!work->direct) {
            u32 mode,special;
            if(IsRecordSceneBlocked(work->record)) {context->state=2;break;}
            work->actor=ResolveRecordActor(work->record);
            mode=7;
            special=work->special;
            if(special==1) {
                SetActorSceneResource(gActorResource,6,0,1,special);
                if(ReadActorKind(work->actor)==13) mode=16;
            }
            work->movement=StartRecordActorTransition(work->record,&work->actor,mode|0x8000,2,&work->actor_ready,gActorTransition,5,0,owner);
        } else {
            SetActorMode(work->actor,2);
            SetActorSequenceFrame(work->actor,7,45);
            work->movement=StartDirectActorTransition(work->actor,&work->actor_ready,3,2,(u32)completed,(u32)completed,(u32)completed,owner);
        }
        ReadActorCoordinates(work->actor,&work->x,&work->y);
        context->state++;
        break;
    }
    case 257:
        if(!work->actor_ready) break;
        work->positioned=StartPositionedSequence(work->x,work->y,0,1,1,&work->positioned_output,gInitialPositionedSequence,owner);
        work->overlay=StartSceneOverlay(gInitialOverlay,1,4,0,owner);
        work->delay=24;
        context->state++;
        break;
    case 258:
        if(work->direct) {
            work->positioned=PollPositionedSequence(work->positioned);
            if(!work->positioned) context->state=2;
        } else {
            work->delay--;
            if(work->delay) break;
            SetRecordSceneState(work->record,0);
            context->state++;
        }
        break;
    case 259:
        if(!work->gate) break;
        if(IsSceneStageBusy()) break;
        work->positioned=PollPositionedSequence(work->positioned);
        if(work->positioned) break;
        if(!IsRecordPhaseAvailable(work->record,0)) {context->state=2;break;}
        first_event.record=work->record;
        first_event.phase=&work->phase;
        work->child_a=CreateSceneTask(ActorPhaseCallbackA,32,&first_event,owner);
        work->actor_record=ResolveRecordActorPhase(work->record,0);
        work->coordinate_state=ReadActorPhaseCoordinates(work->actor_record,&work->x,&work->y,0);
        work->overlay=StartSceneOverlay(gMiddleOverlay,2,4,0,owner);
        context->state++;
        break;
    case 260:
        if(!work->phase) break;
        second_event.record=work->record;
        second_event.phase=&work->phase;
        work->child_b=CreateSceneTask(ActorPhaseCallbackB,20,&second_event,owner);
        context->state++;
        break;
    case 261:
        if(!work->phase) break;
        DeleteSceneTask(work->child_a);
        work->child_a=0;
        work->positioned=StartPositionedSequence(work->x,work->y,0,1,1,&work->positioned_output,gFinalPositionedSequence,owner);
        context->state++;
        break;
    case 262: {
        void *completed=PollPositionedSequence(work->positioned);
        work->positioned=completed;
        if(completed) break;
        work->resource=StartActorPhaseResource(work->actor_record,gFinalResource,12,0,4,owner,(u32)completed);
        context->state++;
        break;
    }
    case 263:
        work->child_b=PollSceneTask(work->child_b);
        if(work->child_b) break;
        if(!IsActorSequenceFinished(work->actor)) break;
        work->resource=PollActorPhaseResource(work->resource);
        if(!work->resource) context->state=2;
        break;
    }
    return 0;
}

__asm__(".global RetailCall_08005B58\n.thumb_set RetailCall_08005B58,0x08005b59");

__asm__(".global RetailCall_08005B6C\n.thumb_set RetailCall_08005B6C,0x08005b6d");

__asm__(".global RetailCall_080D38B4\n.thumb_set RetailCall_080D38B4,0x080d38b5");

__asm__(".global RetailCall_080D3B54\n.thumb_set RetailCall_080D3B54,0x080d3b55");

__asm__(".global RetailCall_080D45D0\n.thumb_set RetailCall_080D45D0,0x080d45d1");

__asm__(".global RetailCall_080D6098\n.thumb_set RetailCall_080D6098,0x080d6099");

__asm__(".global RetailCall_080D6134\n.thumb_set RetailCall_080D6134,0x080d6135");

__asm__(".global RetailCall_080D8858\n.thumb_set RetailCall_080D8858,0x080d8859");

__asm__(".global RetailCall_080D8B4C\n.thumb_set RetailCall_080D8B4C,0x080d8b4d");

__asm__(".global RetailCall_080DBA5C\n.thumb_set RetailCall_080DBA5C,0x080dba5d");

__asm__(".global RetailCall_080DBDC8\n.thumb_set RetailCall_080DBDC8,0x080dbdc9");

__asm__(".global RetailCall_080DBFFC\n.thumb_set RetailCall_080DBFFC,0x080dbffd");

__asm__(".global RetailCall_080DCFE4\n.thumb_set RetailCall_080DCFE4,0x080dcfe5");

__asm__(".global RetailCall_080DD47C\n.thumb_set RetailCall_080DD47C,0x080dd47d");

__asm__(".global RetailCall_080DD4A4\n.thumb_set RetailCall_080DD4A4,0x080dd4a5");

__asm__(".global RetailCall_080DD6E0\n.thumb_set RetailCall_080DD6E0,0x080dd6e1");

__asm__(".global RetailCall_080DD720\n.thumb_set RetailCall_080DD720,0x080dd721");

__asm__(".global RetailCall_080DD748\n.thumb_set RetailCall_080DD748,0x080dd749");

__asm__(".global RetailCall_080DDF68\n.thumb_set RetailCall_080DDF68,0x080ddf69");

__asm__(".global RetailCall_080DE150\n.thumb_set RetailCall_080DE150,0x080de151");

__asm__(".global RetailCall_080DE1F0\n.thumb_set RetailCall_080DE1F0,0x080de1f1");

__asm__(".global RetailCall_080DE4B0\n.thumb_set RetailCall_080DE4B0,0x080de4b1");

__asm__(".global RetailCall_080DFD8C\n.thumb_set RetailCall_080DFD8C,0x080dfd8d");

__asm__(".global RetailCall_080E03F8\n.thumb_set RetailCall_080E03F8,0x080e03f9");

__asm__(".global RetailCall_080E051C\n.thumb_set RetailCall_080E051C,0x080e051d");

__asm__(".global RetailCall_080E05DC\n.thumb_set RetailCall_080E05DC,0x080e05dd");

__asm__(".global gScenePalette\n.set gScenePalette,0x3003860");

__asm__(".global gActorPrelude\n.set gActorPrelude,0x83a3d6c");

__asm__(".global gActorResource\n.set gActorResource,0x88eabb8");

__asm__(".global gActorTransition\n.set gActorTransition,0x83a3dec");

__asm__(".global gInitialPositionedSequence\n.set gInitialPositionedSequence,0x83a3dc0");

__asm__(".global gInitialOverlay\n.set gInitialOverlay,0x83a3e04");

__asm__(".global gMiddleOverlay\n.set gMiddleOverlay,0x83a3df4");

__asm__(".global gFinalPositionedSequence\n.set gFinalPositionedSequence,0x83a3da8");

__asm__(".global gFinalResource\n.set gFinalResource,0x83a3dd8");

__asm__(".global ActorPhaseCallbackASymbol\n.thumb_set ActorPhaseCallbackASymbol,0x8115b6d");

__asm__(".global ActorPhaseCallbackBSymbol\n.thumb_set ActorPhaseCallbackBSymbol,0x8115ce5");
