typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Task;
struct Event {u16 state;u8 unused2[2];void *record;u8 unused8[12];u16 mode;u8 unused22[6];};
struct Work {s16 x,y;u8 mode,unused5[3];u8 output8[4];struct Task *positioned,*auxiliary,*palettes[2];void *record;struct Task *sequence;};
typedef char WorkSize[sizeof(struct Work)==36?1:-1];
extern struct Task *CreatePositioned(s16,s16,u16,u8,u16,void*,const void*,struct Task*);
extern void LoadPositionedResource(const void*,u8,u8,s16,s16,u16);
extern struct Task *CreateAuxiliary(const void*,struct Task*);
extern struct Task *CreatePalette(const void*,struct Task*);
extern struct Task *CreateStage(const void*,u8,u16,u16,struct Task*);
extern struct Task *PollPositioned(struct Task*);
extern struct Task *PollAuxiliary(struct Task*);
extern u32 PollPalettes(struct Task**,u16);
extern u32 GetLayerMask(u8);
extern volatile u16 gDisplayControl;
extern const u8 gPositionSequence[],gResource[],gAuxiliary[],gPalette7[],gPalette8First[],gPalette8Second[],gPaletteDefault[],gPaletteCommon[],gStage9[],gStageDefault[];
u32 AdvanceSelectedActionStage(struct Task*,struct Event*,struct Work*) __asm__("RemainingBand43_000F2CDC");
u32 AdvanceSelectedActionStage(struct Task *task,struct Event *event,struct Work *work)
{
    switch(event->state) {
    case 0: {
        u16 mode=event->mode;
        work->mode=mode;
        work->record=event->record;
        work->x=120;
        work->y=128;
        if((u8)mode!=7)work->y=96;
        break;
    }
    case 256:
        work->positioned=CreatePositioned(work->x,work->y,0,1,1,work->output8,gPositionSequence,task);
        LoadPositionedResource(gResource,0,2,work->x,work->y,0);
        work->auxiliary=CreateAuxiliary(gAuxiliary,task);
        if(work->mode==7) {
            work->palettes[0]=CreatePalette(gPalette7,task);
            work->palettes[1]=CreatePalette(gPaletteCommon,task);
        } else if(work->mode==8) {
            work->palettes[0]=CreatePalette(gPalette8First,task);
            work->palettes[1]=CreatePalette(gPalette8Second,task);
        } else {
            work->palettes[0]=CreatePalette(gPaletteDefault,task);
            work->palettes[1]=CreatePalette(gPaletteCommon,task);
        }
        if(work->mode==9)work->sequence=CreateStage(gStage9,1,4,0,task);
        else work->sequence=CreateStage(gStageDefault,1,4,0,task);
        event->state++;
        break;
    case 257:
        work->positioned=PollPositioned(work->positioned);
        if(work->positioned==0) {
            work->auxiliary=PollAuxiliary(work->auxiliary);
            if(work->auxiliary==0) {
                if((u8)PollPalettes(work->palettes,2)) {
                    u32 mask=GetLayerMask(2);
                    gDisplayControl &= ~mask;
                    event->state++;
                }
            }
        }
        break;
    case 258:event->state=2;break;
    }
    return 0;
}
__asm__(".global gPositionSequence\n.set gPositionSequence,0x839a880\n.global gResource\n.set gResource,0x88f4e9c\n.global gAuxiliary\n.set gAuxiliary,0x894db6c\n.global gPalette7\n.set gPalette7,0x894b914\n.global gPalette8First\n.set gPalette8First,0x894c528\n.global gPalette8Second\n.set gPalette8Second,0x894c578\n.global gPaletteDefault\n.set gPaletteDefault,0x894c424\n.global gPaletteCommon\n.set gPaletteCommon,0x894b964\n.global gStage9\n.set gStage9,0x839a8e0\n.global gStageDefault\n.set gStageDefault,0x839a8d8\n.global gDisplayControl\n.set gDisplayControl,0x3000940\n.global CreatePositioned\n.thumb_set CreatePositioned,0x80d6099\n.global LoadPositionedResource\n.thumb_set LoadPositionedResource,0x80d7221\n.global CreateAuxiliary\n.thumb_set CreateAuxiliary,0x80d3e9d\n.global CreatePalette\n.thumb_set CreatePalette,0x80d4705\n.global CreateStage\n.thumb_set CreateStage,0x80dfd8d\n.global PollPositioned\n.thumb_set PollPositioned,0x80d6135\n.global PollAuxiliary\n.thumb_set PollAuxiliary,0x80d3f09\n.global PollPalettes\n.thumb_set PollPalettes,0x80d48dd\n.global GetLayerMask\n.thumb_set GetLayerMask,0x80035a9\n");
