typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContext {u16 state;u8 unknown02[2];void *record;};
struct Definition391Work {void *record,*child;};
struct SceneEvent {u32 unknown00;void *record;u8 unknown08[12];u16 definition,selector;u8 unknown24[4];};
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
extern void ActorPhaseSequenceCallback(void) asm("ActorPhaseSequenceCallbackSymbol");
extern void *CreateSceneTask(void(*)(void),u32,const struct SceneEvent*,void*) asm("RetailCall_08005B6C");
extern void *PollSceneTask(void*) asm("RetailCall_080E051C");
typedef char WorkSize[(sizeof(struct Definition391Work)==8)?1:-1];
typedef char EventSize[(sizeof(struct SceneEvent)==28)?1:-1];
u32 AdvanceActorDefinition391(void*,struct SceneContext*,struct Definition391Work*) asm("OriginalSceneDefinitionQuestion_0011D19C");
u32 AdvanceActorDefinition391(void *owner,struct SceneContext *context,struct Definition391Work *work)
{
    struct SceneEvent event;
    s32 state=context->state;
    switch(state) {
    case 0:
        work->record=context->record;
        break;
    case 1:
        RestoreSceneStage();
        break;
    case 256:
        event.definition=391;
        event.selector=0;
        event.record=work->record;
        work->child=CreateSceneTask(ActorPhaseSequenceCallback,60,&event,owner);
        context->state++;
        break;
    case 257:
        work->child=PollSceneTask(work->child);
        if(!work->child) context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global RetailCall_08005B6C\n.thumb_set RetailCall_08005B6C,0x08005b6d");
__asm__(".global RetailCall_080E051C\n.thumb_set RetailCall_080E051C,0x080e051d");
__asm__(".global ActorPhaseSequenceCallbackSymbol\n.thumb_set ActorPhaseSequenceCallbackSymbol,0x08115d75");
