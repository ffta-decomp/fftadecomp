typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef struct Node Node;
typedef struct Event {u16 state,unknown2;void *record;unsigned unknown8[3];u16 selector,mode;} Event;
typedef struct Work {u8 selector,mode;s16 x,y;u16 unknown6;void *record,*actor;Node *graphic;unsigned parameters[3];Node *effect,*script,*delayed,*definition,*unpolled;} Work;
extern void *ResolveRecord(void *,s16 *,s16 *,s16 *);
extern unsigned ActorPredicate(void *);
extern void PositionGraphic(unsigned,unsigned,unsigned,int,int);
extern Node *CreateGraphic(unsigned,const void *,u16,unsigned);
extern unsigned LayerMask(u8);
extern u16 DisplayShadow;
extern Node *CreateEffect(int,int,unsigned,unsigned,unsigned,void *,const void *,void *);
extern Node *CreateScript(const void *,void *);
extern Node *CreateDelayedScript(const void *,void *,u16);
extern Node *CreateDefinition(void *,const void *,u8,u16,u16,void *,u16);
extern Node *CreateContinuation(const void *,unsigned,unsigned,unsigned,void *);
extern Node *PollGraphic(Node *,unsigned);
extern Node *PollEffect(Node *);
extern Node *PollScript(Node *);
extern Node *PollDelayedScript(Node *);
extern Node *PollDefinition(Node *);
extern const u16 GraphicYOffset[],GraphicTiles[];
extern const void *const GraphicAssets[];
extern const void *const EffectSequences[];
extern const void *const ScriptSequences[];
extern const void *const DelayedSequences[];
extern const void *const ContinuationSequences[];
extern const u8 EffectModes[],DelayedTimes[],DefinitionTimes[],DefinitionSequence[];
unsigned ProcessIndexedEffectSequence(void *parent,Event *event,Work *work)
{
    switch(event->state) {
    case 0:
        work->selector=event->selector;
        work->mode=event->mode;
        work->record=event->record;
        work->actor=ResolveRecord(work->record,&work->x,&work->y,0);
        if((u8)ActorPredicate(work->actor)!=0) work->y-=8;
        break;
    case 256:
        {
            unsigned mask,flags,channels;
            PositionGraphic(0,2,0,work->x,(s16)(work->y+GraphicYOffset[work->selector]));
            work->graphic=CreateGraphic(0,GraphicAssets[work->selector],GraphicTiles[work->selector],6);
            mask=LayerMask(2);
            {
                register unsigned shadow asm("r1")=DisplayShadow|mask;
                asm("" : "+r" (shadow));
                DisplayShadow=shadow;
            }
            work->effect=CreateEffect(work->x,work->y,0,1,EffectModes[work->selector],work->parameters,EffectSequences[work->selector],parent);
            work->script=CreateScript(ScriptSequences[work->selector],parent);
            work->delayed=CreateDelayedScript(DelayedSequences[work->selector],parent,DelayedTimes[work->selector]);
            flags=(work->mode&1)?4:2;
            work->definition=CreateDefinition(work->record,DefinitionSequence,12,DefinitionTimes[work->selector],flags,parent,DefinitionTimes[work->selector]);
            channels=(work->mode&1)?16:8;
            work->unpolled=CreateContinuation(ContinuationSequences[work->selector],1,channels|4,0,parent);
            event->state++;
        }
        break;
    case 257:
        {
            unsigned done=1;
            unsigned old_handle=(unsigned)work->graphic;
            unsigned was_nonnull=((0u-old_handle)|old_handle)>>31;
            work->graphic=PollGraphic((Node *)old_handle,0);
            if(work->graphic!=0) done=0;
            if(was_nonnull && work->graphic==0) {
                unsigned mask=LayerMask(2);
                DisplayShadow&=~mask;
            }
            work->effect=PollEffect(work->effect);
            if(work->effect!=0) done=0;
            work->script=PollScript(work->script);
            if(work->script!=0) done=0;
            work->delayed=PollDelayedScript(work->delayed);
            if(work->delayed!=0) done=0;
            if(done!=0) event->state++;
        }
        break;
    case 258:
        work->definition=PollDefinition(work->definition);
        if(work->definition==0) event->state=2;
        break;
    case 1:
    default:break;
    }
    return 0;
}
asm(".global ResolveRecord\n.thumb_set ResolveRecord,0x080dd749\n"
".global ActorPredicate\n.thumb_set ActorPredicate,0x080dd73d\n"
".global PositionGraphic\n.thumb_set PositionGraphic,0x080d49fd\n"
".global CreateGraphic\n.thumb_set CreateGraphic,0x080d4b65\n"
".global LayerMask\n.thumb_set LayerMask,0x080035a9\n"
".global DisplayShadow\n.set DisplayShadow,0x03000940\n"
".global CreateEffect\n.thumb_set CreateEffect,0x080d6099\n"
".global CreateScript\n.thumb_set CreateScript,0x080d3e9d\n"
".global CreateDelayedScript\n.thumb_set CreateDelayedScript,0x080d4725\n"
".global CreateDefinition\n.thumb_set CreateDefinition,0x080dcfe5\n"
".global CreateContinuation\n.thumb_set CreateContinuation,0x080dfd8d\n"
".global PollGraphic\n.thumb_set PollGraphic,0x080d4d2d\n"
".global PollEffect\n.thumb_set PollEffect,0x080d6135\n"
".global PollScript\n.thumb_set PollScript,0x080d3f09\n"
".global PollDelayedScript\n.thumb_set PollDelayedScript,0x080d4775\n"
".global PollDefinition\n.thumb_set PollDefinition,0x080dba5d\n"
".global GraphicYOffset\n.set GraphicYOffset,0x08397f6c\n"
".global GraphicTiles\n.set GraphicTiles,0x08397f48\n"
".global GraphicAssets\n.set GraphicAssets,0x08397f3c\n"
".global EffectSequences\n.set EffectSequences,0x08397f2c\n"
".global ScriptSequences\n.set ScriptSequences,0x08397f60\n"
".global DelayedSequences\n.set DelayedSequences,0x08397f50\n"
".global ContinuationSequences\n.set ContinuationSequences,0x08397fb0\n"
".global EffectModes\n.set EffectModes,0x08397f38\n"
".global DelayedTimes\n.set DelayedTimes,0x08397f5c\n"
".global DefinitionTimes\n.set DefinitionTimes,0x08397f8c\n"
".global DefinitionSequence\n.set DefinitionSequence,0x08397f78\n");
