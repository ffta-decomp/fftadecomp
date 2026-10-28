typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SequenceContext {u16 state;};
struct Definition413Work {u32 unknown00[2];void *first,*second,*third;u32 unknown14;};
struct DefinitionEvent {u32 words[7];};
extern u16 gSceneControl;
extern u16 gScenePhase;
extern u32 ReadLayerReleaseMask(u32) asm("RetailCall_080035A8");
extern void ClearSceneStage(void) asm("RetailCall_080D4020");
extern void SetSceneMode(u16) asm("RetailCall_080D3AC0");
extern void RestoreSceneStage(void) asm("RetailCall_080D35D8");
extern void *CreateSceneTask(void (*)(void),u16,const struct DefinitionEvent*,void*) asm("RetailCall_08005B6C");
extern u16 *GetChildPayloadFlags(void*) asm("RetailCall_08005BFC");
extern void *PollAndReleaseDefinitionChild(void*) asm("RetailCall_080E051C");
extern void FirstDefinition413Stage(void) asm("Definition413FirstCallback");
extern void SecondDefinition413Stage(void) asm("Definition413SecondCallback");
extern void ThirdDefinition413Stage(void) asm("Definition413ThirdCallback");
typedef char WorkSize[(sizeof(struct Definition413Work)==24)?1:-1];
typedef char EventSize[(sizeof(struct DefinitionEvent)==28)?1:-1];
/* Match the observed getter -> halfword load -> mask-working -> numeric-result
 * phases. Each constraint consumes an actually defined value and emits no
 * instruction; no task/flag initialization or clobber is invented. */
#define RetainChildFlag(child, mask) ({ \
    u16 *flags=GetChildPayloadFlags(child); \
    u32 loaded=*flags; \
    register u32 retained asm("r1")=(mask); \
    register u32 ready asm("r0"); \
    asm("" : "+r"(retained) : "r"(loaded)); \
    retained&=loaded; \
    *flags=retained; \
    if(retained) {ready=1;asm("" : "+r"(ready));} \
    else {ready=0;asm("" : "+r"(ready));} \
    ready; \
})
u32 AdvanceDefinition413ChildHandoffs(void*,struct SequenceContext*,struct Definition413Work*) asm("OriginalSceneDefinitionQuestion_00120724");
u32 AdvanceDefinition413ChildHandoffs(void *owner,struct SequenceContext *context,struct Definition413Work *work)
{
    struct DefinitionEvent first_event;
    struct DefinitionEvent later_event;
    s32 state=context->state;
    switch(state) {
    case 0:
        {u32 mask=ReadLayerReleaseMask(0);gSceneControl&=~mask;}
        {u32 mask=ReadLayerReleaseMask(1);gSceneControl&=~mask;}
        {u32 mask=ReadLayerReleaseMask(2);gSceneControl&=~mask;}
        {u32 mask=ReadLayerReleaseMask(3);gSceneControl&=~mask;}
        ClearSceneStage();
        gScenePhase=state;
        SetSceneMode(0);
        break;
    case 1:
        RestoreSceneStage();
        break;
    case 256:
        /* The original passes these 28 bytes without writing fields here. */
        work->first=CreateSceneTask(FirstDefinition413Stage,124,&first_event,owner);
        context->state++;
        break;
    case 257:
        if(RetainChildFlag(work->first,1)) {
            u16 *flags=GetChildPayloadFlags(work->first);
            *flags&=0x7fff;
            context->state++;
        }
        break;
    case 258:
        if(!work->second && RetainChildFlag(work->first,2))
            work->second=CreateSceneTask(SecondDefinition413Stage,44,&later_event,owner);
        work->first=PollAndReleaseDefinitionChild(work->first);
        if(work->first) break;
        context->state++;
        break;
    case 259:
        if(!work->third && RetainChildFlag(work->second,2))
            work->third=CreateSceneTask(ThirdDefinition413Stage,68,&later_event,owner);
        work->second=PollAndReleaseDefinitionChild(work->second);
        if(work->second) break;
        context->state++;
        break;
    case 260:
        work->third=PollAndReleaseDefinitionChild(work->third);
        if(work->third) break;
        context->state++;
        break;
    case 261:
        context->state=2;
        break;
    }
    return 0;
}
__asm__(".global gSceneControl\n.set gSceneControl,0x03000940\n.global gScenePhase\n.set gScenePhase,0x03003860");
__asm__(".global RetailCall_080035A8\n.thumb_set RetailCall_080035A8,0x080035a9");
__asm__(".global RetailCall_080D4020\n.thumb_set RetailCall_080D4020,0x080d4021");
__asm__(".global RetailCall_080D3AC0\n.thumb_set RetailCall_080D3AC0,0x080d3ac1");
__asm__(".global RetailCall_080D35D8\n.thumb_set RetailCall_080D35D8,0x080d35d9");
__asm__(".global RetailCall_08005B6C\n.thumb_set RetailCall_08005B6C,0x08005b6d");
__asm__(".global RetailCall_08005BFC\n.thumb_set RetailCall_08005BFC,0x08005bfd");
__asm__(".global RetailCall_080E051C\n.thumb_set RetailCall_080E051C,0x080e051d");
__asm__(".global Definition413FirstCallback\n.thumb_set Definition413FirstCallback,0x0811ef59");
__asm__(".global Definition413SecondCallback\n.thumb_set Definition413SecondCallback,0x0811f5e1");
__asm__(".global Definition413ThirdCallback\n.thumb_set Definition413ThirdCallback,0x081204a9");
