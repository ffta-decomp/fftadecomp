typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ActorRecordContext {u16 state;u8 unknown02[2];void *record;};
struct ActorRecordSequence {void *record,*child;};
struct DefinitionEvent {
    u32 unknown00;void *record;u32 parameter,flags,unknown10;
    u16 definition,type_and_flags,identifier,unknown1A;
};
extern void DefinitionEffectCallback(void) asm("InitialDefinitionEffectCallback");
extern void FollowupDefinitionCallback(void) asm("FollowupRecordDefinitionCallback");
extern void *CreateSceneTask(void(*)(void),u16,const struct DefinitionEvent*,void*) asm("RetailCall_08005B6C");
extern void *PollAndReleaseDefinitionChild(void*) asm("RetailCall_080E051C");
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
typedef char WorkSize[(sizeof(struct ActorRecordSequence)==8)?1:-1];
typedef char EventSize[(sizeof(struct DefinitionEvent)==28)?1:-1];
u32 AdvanceDefinition409ActorRecordSequence(void*,struct ActorRecordContext*,struct ActorRecordSequence*) asm("OriginalSceneDefinitionQuestion_0011EA68");
u32 AdvanceDefinition409ActorRecordSequence(void *owner,struct ActorRecordContext *context,struct ActorRecordSequence *work)
{
    struct DefinitionEvent first_event;
    struct DefinitionEvent remaining_event;
    s32 state=context->state;
    switch(state) {
    case 0:
        work->record=context->record;
        break;
    case 1:
        RestoreSceneStage();
        break;
    case 256:
        first_event.definition=345;
        first_event.type_and_flags=12;
        first_event.identifier=412;
        first_event.record=work->record;
        work->child=CreateSceneTask(DefinitionEffectCallback,40,&first_event,owner);
        context->state++;
        break;
    case 257: {
        u32 reply=(u32)PollAndReleaseDefinitionChild(work->child);
        work->child=(void*)reply;
        if(reply) break;
        remaining_event.definition=412;
        /* Preserve the full poll result's actual zero projection. */
        remaining_event.type_and_flags=reply;
        remaining_event.record=work->record;
        work->child=CreateSceneTask(FollowupDefinitionCallback,56,&remaining_event,owner);
        context->state++;
        break;
    }
    case 258:
        work->child=PollAndReleaseDefinitionChild(work->child);
        if(work->child) break;
        context->state=2;
        break;
    }
    return 0;
}
__asm__(".global RetailCall_08005B6C\n.thumb_set RetailCall_08005B6C,0x08005b6d");
__asm__(".global RetailCall_080E051C\n.thumb_set RetailCall_080E051C,0x080e051d");
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global InitialDefinitionEffectCallback\n.thumb_set InitialDefinitionEffectCallback,0x080e2399");
__asm__(".global FollowupRecordDefinitionCallback\n.thumb_set FollowupRecordDefinitionCallback,0x08105d41");
