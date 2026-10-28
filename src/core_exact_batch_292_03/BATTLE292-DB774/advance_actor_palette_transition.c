typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct RangeRequest;
struct Actor;
struct PaletteParameters {struct Actor *actor;u16 duration;u8 palette;};
struct PaletteEvent {u16 state,pad;struct PaletteParameters *parameters;u32 unused[3];u16 delay;};
struct PaletteWork {struct Actor *actor;u16 duration;u8 palette,unknown7;u16 delay,unknown10;struct RangeRequest *request;};
extern u8 ActorPaletteBank[];
extern u32 ExchangeActorPalette(struct Actor *,u8);
extern void CopyPaletteHalfwords(const void *,void *,u32);
extern struct RangeRequest *BeginActorPaletteRange(u32,u32,u32,const u16 *);
extern struct RangeRequest *ReleaseActorPaletteRange(struct RangeRequest *);
asm(".global ActorPaletteBank\n.set ActorPaletteBank,0x03003a60\n.global ExchangeActorPalette\n.thumb_set ExchangeActorPalette,0x080dbc19\n.global CopyPaletteHalfwords\n.thumb_set CopyPaletteHalfwords,0x0814186d\n.global BeginActorPaletteRange\n.thumb_set BeginActorPaletteRange,0x08147d2d\n.global ReleaseActorPaletteRange\n.thumb_set ReleaseActorPaletteRange,0x081484cd\n");
u32 AdvanceActorPaletteTransition(u32 ignored,struct PaletteEvent *event,struct PaletteWork *work) asm("RemainingBand43_000DB774");
u32 AdvanceActorPaletteTransition(u32 ignored,struct PaletteEvent *event,struct PaletteWork *work)
{
    switch(event->state) {
    case 0: {
        struct PaletteParameters *parameters=event->parameters;
        work->actor=parameters->actor;
        work->duration=parameters->duration;
        work->palette=parameters->palette;
        work->delay=event->delay;
        break;
    }
    case 1:
        break;
    case 256: {
        u32 delay=work->delay;
        u32 old_palette,first;
        u8 *palette_bank;
        if(delay) {--delay;work->delay=delay;if((u16)delay)break;}
        if(!work->duration) {ExchangeActorPalette(work->actor,15);event->state=2;}
        old_palette=(ExchangeActorPalette(work->actor,work->palette)<<24)>>19;
        palette_bank=ActorPaletteBank;
        CopyPaletteHalfwords(palette_bank+old_palette,palette_bank+work->palette*32,16);
        first=((u32)work->palette<<20)+0x01010000U;
        work->request=BeginActorPaletteRange(first>>16,15,work->duration,(const u16 *)(palette_bank+482));
        event->state++;
        break;
    }
    case 257:
        work->request=ReleaseActorPaletteRange(work->request);
        if(!work->request) {ExchangeActorPalette(work->actor,15);event->state=2;}
        break;
    }
    return 0;
}
