typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef struct Node Node;
typedef struct Event {u16 state,unknown2;void *record;unsigned unknown8[3];u16 mode,variant;} Event;
typedef struct Work {u8 mode,variant;s16 x,y;u16 unknown6;void *actor,*record;unsigned parameters;Node *effect,*script,*script_a,*script_b,*definition,*unpolled;} Work;
extern void *ResolveRecord(void *,s16 *,s16 *,s16 *);
extern void CpuSet(const void *,void *,unsigned);
extern void LoadVariantAsset(const void *,unsigned,unsigned,unsigned,unsigned);
extern void PlaceResource(const void *,unsigned,unsigned,int,int,unsigned);
extern Node *CreateScript(const void *,void *);
extern Node *CreateDefinition(void *,const void *,u8,u16,u16,void *,u16);
extern Node *CreateContinuation(const void *,unsigned,unsigned,unsigned,void *);
extern Node *PollScript(Node *);
extern unsigned LayerMask(u8);
extern u16 DisplayShadow;
extern Node *CreateEffect(int,int,unsigned,unsigned,unsigned,void *,const void *,void *);
extern Node *PollEffect(Node *);
extern Node *PollDefinition(Node *);
extern const u8 VariantAsset[],BaseResource[],Script0[],Script1[],ScriptA[],ScriptB[],DefinitionSequence[],ContinuationSequence[],EffectSequence[];
unsigned ProcessVariantEffectSequence(void *parent,Event *event,Work *work)
{
    u16 zero;
    switch(event->state) {
    case 0:
        work->mode=event->mode;
        work->variant=event->variant;
        work->record=event->record;
        work->actor=ResolveRecord(work->record,&work->x,&work->y,0);
        zero=0;
        CpuSet(&zero,(void *)0x03003920,0x01000010);
        if(work->variant==1) LoadVariantAsset(VariantAsset,6,1,1,1);
        break;
    case 256:
        {
            unsigned flags,channels;
            PlaceResource(BaseResource,0,2,work->x,work->y,0);
            if(work->variant==0) work->script=CreateScript(Script0,parent);
            else work->script=CreateScript(Script1,parent);
            work->script_a=CreateScript(ScriptA,parent);
            flags=(work->mode&1)?4:2;
            work->definition=CreateDefinition(work->record,DefinitionSequence,12,50,flags,parent,50);
            channels=(work->mode&1)?16:8;
            work->unpolled=CreateContinuation(ContinuationSequence,1,channels|4,0,parent);
            event->state++;
        }
        break;
    case 257:
        work->script_a=PollScript(work->script_a);
        if(work->script_a==0) {
            unsigned mask=LayerMask(2);
            DisplayShadow&=~mask;
            work->effect=CreateEffect(work->x,work->y,0,1,1,&work->parameters,EffectSequence,parent);
            work->script_b=CreateScript(ScriptB,parent);
            event->state++;
        }
        break;
    case 258:
        work->script=PollScript(work->script);
        if(work->script!=0) break;
        work->script_b=PollScript(work->script_b);
        if(work->script_b!=0) break;
        work->effect=PollEffect(work->effect);
        if(work->effect==0) event->state++;
        break;
    case 259:
        work->definition=PollDefinition(work->definition);
        if(work->definition==0) event->state=2;
        break;
    case 1:
    default:break;
    }
    return 0;
}
asm(".global ResolveRecord\n.thumb_set ResolveRecord,0x080dd749\n"
".global CpuSet\n.thumb_set CpuSet,0x0814186d\n"
".global LoadVariantAsset\n.thumb_set LoadVariantAsset,0x080d45d1\n"
".global PlaceResource\n.thumb_set PlaceResource,0x080d7221\n"
".global CreateScript\n.thumb_set CreateScript,0x080d4705\n"
".global CreateDefinition\n.thumb_set CreateDefinition,0x080dcfe5\n"
".global CreateContinuation\n.thumb_set CreateContinuation,0x080dfd8d\n"
".global PollScript\n.thumb_set PollScript,0x080d4775\n"
".global LayerMask\n.thumb_set LayerMask,0x080035a9\n"
".global DisplayShadow\n.set DisplayShadow,0x03000940\n"
".global CreateEffect\n.thumb_set CreateEffect,0x080d6099\n"
".global PollEffect\n.thumb_set PollEffect,0x080d6135\n"
".global PollDefinition\n.thumb_set PollDefinition,0x080dba5d\n"
".global VariantAsset\n.set VariantAsset,0x088ea2d4\n"
".global BaseResource\n.set BaseResource,0x088f548c\n"
".global Script0\n.set Script0,0x089494e0\n"
".global Script1\n.set Script1,0x0894a410\n"
".global ScriptA\n.set ScriptA,0x08949528\n"
".global ScriptB\n.set ScriptB,0x0894ac90\n"
".global DefinitionSequence\n.set DefinitionSequence,0x08396d88\n"
".global ContinuationSequence\n.set ContinuationSequence,0x08396d9c\n"
".global EffectSequence\n.set EffectSequence,0x08396d70\n");
