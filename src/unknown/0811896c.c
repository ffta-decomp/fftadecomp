typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,unknown2;void *record;u32 word8,word12,word16;u16 id,mode;u32 word24;} Event;
typedef struct Work {u8 selector,unknown1;u16 id;u8 mode,unknown5[3];void *child,*record;u32 unknown16;} Work;
typedef u32 (*Callback)(void*,Event*,void*);
void RetailCall_080d38b4(void);
void *RetailCall_08005b6c(Callback,u16,const Event*,void*);
void *RetailCall_080e051c(void*);
extern Callback gAuthoredCallbacks[5];
extern const u16 gAuthoredPayloadSizes[5];
s32 OriginalActionCallback_0011896C(void *parent,Event *event,Work *work)
{
    Event child_event;
    switch((s32)event->phase) {
    case 0:
        work->id=event->word8;
        work->selector=event->word8-51;
        work->mode=event->mode;
        work->record=event->record;
        break;
    case 1:
        RetailCall_080d38b4();
        break;
    case 256: {
        Callback callback;
        u16 size;
        child_event.id=work->id;
        child_event.mode=work->mode;
        child_event.record=work->record;
        child_event.word8=0;
        child_event.word12=0;
        callback=gAuthoredCallbacks[work->selector];
        size=gAuthoredPayloadSizes[work->selector];
        work->child=RetailCall_08005b6c(callback,size,&child_event,parent);
        event->phase++;
        break;
    }
    case 257:
        work->child=RetailCall_080e051c(work->child);
        if(work->child==0) event->phase=2;
        break;
    }
    return 0;
}
asm(".global gAuthoredCallbacks\n.set gAuthoredCallbacks,0x083a60c8\n.global gAuthoredPayloadSizes\n.set gAuthoredPayloadSizes,0x083a60dc\n");
asm(".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n");
asm(".global RetailCall_080d38b4\n.thumb_set RetailCall_080d38b4,0x080d38b5\n");
asm(".global RetailCall_080e051c\n.thumb_set RetailCall_080e051c,0x080e051d\n");
