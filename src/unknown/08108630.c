typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Actor Actor;
typedef struct Request Request;
typedef struct Event { u16 state; u16 unknown2; Actor *actor; unsigned unknown8[3]; u16 palette_parameter,delay,script_selector,unknown26; } Event;
typedef struct Work { u8 script_selector,palette_parameter,old_slot,unknown3; u16 delay,unknown6; Actor *actor; Request *request; } Work;
extern void RefreshActorDirection(Actor *);
extern unsigned CopyActorPaletteToSlot(Actor *,u8);
extern unsigned ExchangeActorPaletteSlot(Actor *,u8);
extern Request *CreateActorScript(const void *,void *);
extern void BindActorScriptPalette(Request *,u16);
extern Request *ReleaseCompletedActorScript(Request *);
extern const void *const ActorPaletteScripts[];
unsigned ProcessActorPaletteScript(void *parent,Event *event,Work *work)
{
    switch(event->state) {
    case 0:
        work->palette_parameter=event->palette_parameter;
        work->delay=event->delay+1;
        work->script_selector=event->script_selector;
        work->actor=event->actor;
        RefreshActorDirection(work->actor);
        break;
    case 256:
        work->delay--;
        if(work->delay==0) {
            u8 slot=work->palette_parameter+6;
            Request *request;
            work->old_slot=CopyActorPaletteToSlot(work->actor,slot);
            request=CreateActorScript(ActorPaletteScripts[work->script_selector],parent);
            work->request=request;
            BindActorScriptPalette(request,slot);
            event->state++;
        }
        break;
    case 257:
        work->request=ReleaseCompletedActorScript(work->request);
        if(work->request==0) {
            ExchangeActorPaletteSlot(work->actor,work->old_slot);
            event->state=2;
        }
        break;
    case 1:
    default:
        break;
    }
    return 0;
}
asm(".global RefreshActorDirection\n.thumb_set RefreshActorDirection,0x080de269\n"
    ".global CopyActorPaletteToSlot\n.thumb_set CopyActorPaletteToSlot,0x080dbc59\n"
    ".global ExchangeActorPaletteSlot\n.thumb_set ExchangeActorPaletteSlot,0x080dbc19\n"
    ".global CreateActorScript\n.thumb_set CreateActorScript,0x080d4705\n"
    ".global BindActorScriptPalette\n.thumb_set BindActorScriptPalette,0x080d47dd\n"
    ".global ReleaseCompletedActorScript\n.thumb_set ReleaseCompletedActorScript,0x080d4775\n"
    ".global ActorPaletteScripts\n.set ActorPaletteScripts,0x083a107c\n");
