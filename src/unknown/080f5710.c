typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef struct Node Node;
typedef struct Event {u16 state,unknown2;void *record,*coordinates;unsigned unknown12[2];u16 mode,delay;} Event;
typedef struct Work {u8 mode,direction;u16 delay;s16 x,y;void *actor,*record;Node *effect,*pending;void *coordinates;} Work;
extern void *ResolveRecord(void *,s16 *,s16 *,s16 *);
extern void *CopyBytes(void *,const void *,unsigned);
extern void ReadCoordinates(void *,s16 *,s16 *);
extern void ProjectActor(void *,s16 *,s16 *,s16 *);
extern Node *CreateEffect(const void *,unsigned,int,int,unsigned,unsigned,unsigned,unsigned);
extern void SetEffectDirection(Node *,unsigned);
extern Node *CreatePending(void *,u16,u16,void *);
extern Node *PollEffect(Node *);
extern Node *PollPending(Node *);
extern const u8 DirectionModes[4],DirectionFrames[4],EffectAsset[];
unsigned ProcessPendingDirectionEffect(void *parent,Event *event,Work *work)
{
    switch(event->state) {
    case 0:
        work->mode=event->mode;
        work->delay=event->delay+1;
        work->record=event->record;
        work->coordinates=event->coordinates;
        work->actor=ResolveRecord(work->record,&work->x,&work->y,0);
        break;
    case 256:
        {
            u8 modes[4],frames[4];
            s16 x,y,px,py,pz;
            CopyBytes(modes,DirectionModes,4);
            CopyBytes(frames,DirectionFrames,4);
            work->delay--;
            if(work->delay!=0) break;
            ReadCoordinates(work->coordinates,&x,&y);
            ProjectActor(work->actor,&px,&py,&pz);
            if(x==px) {
                if(y<pz) work->direction=0;
                else work->direction=2;
            } else if(x>px) work->direction=1;
            else work->direction=3;
            work->effect=CreateEffect(EffectAsset,modes[work->direction],work->x,work->y,955,6,1,1);
            SetEffectDirection(work->effect,frames[work->direction]);
            work->pending=CreatePending(work->record,2,0,parent);
            event->state++;
        }
        break;
    case 257:
        work->effect=PollEffect(work->effect);
        if(work->effect==0) {
            work->pending=PollPending(work->pending);
            if(work->pending==0) event->state=2;
        }
        break;
    case 1:
    default:break;
    }
    return 0;
}
asm(".global ResolveRecord\n.thumb_set ResolveRecord,0x080dd749\n"
".global CopyBytes\n.thumb_set CopyBytes,0x081443fd\n"
".global ReadCoordinates\n.thumb_set ReadCoordinates,0x080d8b5d\n"
".global ProjectActor\n.thumb_set ProjectActor,0x080dbd79\n"
".global CreateEffect\n.thumb_set CreateEffect,0x080d5cc1\n"
".global SetEffectDirection\n.thumb_set SetEffectDirection,0x08011119\n"
".global CreatePending\n.thumb_set CreatePending,0x080df9e5\n"
".global PollEffect\n.thumb_set PollEffect,0x08011485\n"
".global PollPending\n.thumb_set PollPending,0x080dba5d\n"
".global DirectionModes\n.set DirectionModes,0x08149d24\n"
".global DirectionFrames\n.set DirectionFrames,0x08149d28\n"
".global EffectAsset\n.set EffectAsset,0x08502560\n");
