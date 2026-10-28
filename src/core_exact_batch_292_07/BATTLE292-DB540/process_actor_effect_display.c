typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef struct Node Node;
typedef struct Init {void *actor;unsigned fields[4];} Init;
typedef struct Event {u16 state,unknown2;const Init *data;unsigned unknown8[3];u16 mode,layer;} Event;
typedef struct Work {s16 x,y;u8 layer,mode;u16 unknown6;Node *child,*script,*scripts[2];Init data;} Work;
extern void (*const CopyDispatch)(void *,const void *,unsigned);
extern Node *CreateTask(void *,unsigned,const void *,void *);
extern void ChildCallback(void);
extern Node *PollTask(Node *);
extern void *CopyBytes(void *,const void *,unsigned);
extern unsigned MapBits(unsigned),TileBits(const void *);
extern void SetLayerControl(u16,u8);
extern unsigned LayerMask(u8);
extern u16 DisplayShadow;
extern void ProjectActor(void *,s16 *,s16 *);
extern void ResolveOffsets(void *,s16,s16,s16 *,s16 *);
extern void SetLayerX(s16,u8),SetLayerY(s16,u8);
extern Node *CreateScript(const void *,void *);
extern Node *CreateChildScript(const void *,void *);
extern void ConfigureScript(Node *,u8,u8);
extern unsigned PollScripts(Node **,unsigned);
extern Node *PollScript(Node *);
extern void SetActorMode(void *,u8);
extern const u8 LayerModes[4],ScriptResource[],ScriptA[],ScriptB[];
extern const u16 ModeControl[4];
unsigned ProcessActorEffectDisplay(void *parent,Event *event,Work *work)
{
    unsigned init[7];
    u8 layer_modes[4];
    u16 mode_control[4];
    s16 x,y;
    switch(event->state) {
    case 0:
        CopyDispatch(&work->data,event->data,20);
        work->mode=event->mode;
        work->layer=event->layer;
        break;
    case 256:
        init[1]=(unsigned)&work->data;
        work->child=CreateTask(ChildCallback,4376,init,parent);
        event->state++;
        break;
    case 257:
        {
            u16 control;
            unsigned mask;
            Node *script;
            CopyBytes(layer_modes,LayerModes,4);
            CopyBytes(mode_control,ModeControl,8);
            work->child=PollTask(work->child);
            if(work->child!=0) break;
            control=MapBits(work->data.fields[3])|TileBits((void *)0x06008000)|mode_control[work->mode];
            SetLayerControl(control,work->layer);
            mask=LayerMask(work->layer);
            {
                register unsigned shadow asm("r1")=DisplayShadow|mask;
                asm("" : "+r" (shadow));
                DisplayShadow=shadow;
            }
            ProjectActor(work->data.actor,&work->x,&work->y);
            ResolveOffsets(work->data.actor,work->x,work->y,&x,&y);
            SetLayerX(x,work->layer);
            SetLayerY(y,work->layer);
            script=CreateScript(ScriptResource,parent);
            work->script=script;
            ConfigureScript(script,layer_modes[work->layer],63);
            work->scripts[0]=CreateChildScript(ScriptA,parent);
            work->scripts[1]=CreateChildScript(ScriptB,parent);
            event->state++;
        }
        break;
    case 258:
        if((u8)PollScripts(work->scripts,2)!=0) {
            work->script=PollScript(work->script);
            if(work->script==0) {
                SetActorMode(work->data.actor,0);
                event->state=2;
            }
        }
        break;
    case 1:
    default:break;
    }
    return 0;
}
asm(".global CreateChildScript\n.thumb_set CreateChildScript,0x080d4705\n"
".global CopyDispatch\n.set CopyDispatch,0x0836d4bc\n"
".global CreateTask\n.thumb_set CreateTask,0x08005b6d\n"
".global ChildCallback\n.thumb_set ChildCallback,0x080db00d\n"
".global PollTask\n.thumb_set PollTask,0x080dba5d\n"
".global CopyBytes\n.thumb_set CopyBytes,0x081443fd\n"
".global MapBits\n.thumb_set MapBits,0x08003a75\n"
".global TileBits\n.thumb_set TileBits,0x08003a81\n"
".global SetLayerControl\n.thumb_set SetLayerControl,0x080034b9\n"
".global LayerMask\n.thumb_set LayerMask,0x080035a9\n"
".global DisplayShadow\n.set DisplayShadow,0x03000940\n"
".global ProjectActor\n.thumb_set ProjectActor,0x080dbdc9\n"
".global ResolveOffsets\n.thumb_set ResolveOffsets,0x080dc225\n"
".global SetLayerX\n.thumb_set SetLayerX,0x08003509\n"
".global SetLayerY\n.thumb_set SetLayerY,0x08003559\n"
".global CreateScript\n.thumb_set CreateScript,0x080d3e9d\n"
".global ConfigureScript\n.thumb_set ConfigureScript,0x080d3f85\n"
".global PollScripts\n.thumb_set PollScripts,0x080d48dd\n"
".global PollScript\n.thumb_set PollScript,0x080d3f09\n"
".global SetActorMode\n.thumb_set SetActorMode,0x080dbeb5\n"
".global LayerModes\n.set LayerModes,0x08149b64\n"
".global ModeControl\n.set ModeControl,0x08149b68\n"
".global ScriptResource\n.set ScriptResource,0x0894da30\n"
".global ScriptA\n.set ScriptA,0x0894a77c\n"
".global ScriptB\n.set ScriptB,0x0894a7cc\n");
