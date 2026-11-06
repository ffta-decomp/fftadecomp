typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Event { u32 word[5]; u16 h20,h22; u32 word24; } Event;
typedef struct Work {
    s16 restore_x,restore_y; u16 h4; u8 mode,pad7;
    s16 x,y; u32 word12; void *cell_a,*cell_b;
    void *child24,*child28,*child32,*child36,*child40,*child44,*child48,*child52;
    void *opening,*record,*effect,*delay;
} Work;
extern void *CreateSequence(u32,u32,Event *,void *);
extern void *PollSequence(void *);
extern void *PollOpening(void *);
extern void *StartDelay(u32,u32,void *);
extern void *PollDelay(void *);
extern void *CreateOpening(void *,u32,u32,u32,u32,void *);
extern void CapturePair(s16 *,s16 *);
extern void NativeCaseOne(void);
extern void PreparePair(void);
extern void CaptureBytePair(u8 *,u8 *);
extern u32 PairMask(u32);
extern void RestorePair(int,int);
extern void RestorePairEnd(void);
extern void ClearRecord(void *);
extern void *StartRecordEffect(void *,u32,void *);
extern void *PollRecordEffect(void *);
#define PHASE(e) (*(u16 *)(e))
/* Each value is a real post-helper load; the final H0 store may be shared. */
#define ADVANCE(e) do { u32 next = PHASE(e) + 1; __asm__ volatile ("" : "+r"(next)); PHASE(e) = next; } while (0)
u32 AdvanceAuthoredDualSpriteSequence(void *parent, Event *event_arg, Work *work_arg)
{
    Event a,b,c,d,e,f,g,h;
    u8 first,second;
    register Event *event __asm__("r6") = event_arg;
    register Work *work __asm__("r5") = work_arg;
    int phase;
    __asm__("" : "+r"(event), "+r"(work));
    phase = PHASE(event);
    switch (phase) {
    case 0: {
        u32 mode = event->h22;
        void *record;
        u32 style;
        work->mode = mode;
        record = (void *)event->word[1];
        work->record = record;
        style = 8;
        if ((u8)mode != 0) style = 0;
        work->opening = CreateOpening(record,0x083a3848,style,7,phase,parent);
        CapturePair(&work->restore_x,&work->restore_y);
        break;
    }
    case 1: NativeCaseOne(); break;
    case 256:
        if (work->mode) {
            work->opening = PollOpening(work->opening);
            if (!work->opening) {
                register u32 completed_phase __asm__("r0")=266;
                __asm__("" : "+r"(completed_phase));
                PHASE(event)=completed_phase;
            }
        } else {
            work->opening = PollOpening(work->opening);
            if (!work->opening) {
                work->delay = StartDelay(1,30,parent);
                ADVANCE(event);
            }
        }
        break;
    case 257:
        work->delay = PollDelay(work->delay);
        if (!work->delay) {
            a.word[1]=(u32)&work->x; a.word[2]=(u32)&work->y;
            work->child24=CreateSequence(0x08113fed,352,&a,parent);
            ADVANCE(event);
        }
        break;
    case 258:
        work->child24=PollSequence(work->child24);
        if (!work->child24) {
            b.word[1]=(u32)&work->cell_a; b.word[2]=(u32)&work->cell_b;
            work->child28=CreateSequence(0x081141ed,44,&b,parent);
            ADVANCE(event);
        }
        break;
    case 259:
        work->child28=PollSequence(work->child28);
        if (!work->child28) {
            c.word[1]=(u32)&work->cell_a; c.word[2]=(u32)&work->cell_b;
            work->child32=CreateSequence(0x08114439,128,&c,parent);
            ADVANCE(event);
        }
        break;
    case 260:
        work->child32=PollSequence(work->child32);
        if (!work->child32) {
            d.word[1]=(u32)&work->cell_a; d.word[2]=(u32)&work->cell_b;
            work->child36=CreateSequence(0x08114911,416,&d,parent);
            ADVANCE(event);
        }
        break;
    case 261:
        work->child36=PollSequence(work->child36);
        if (!work->child36) {
            e.h20=work->x; e.h22=work->y;
            work->child40=CreateSequence(0x08114dbd,36,&e,parent);
            ADVANCE(event);
        }
        break;
    case 262:
        work->child40=PollSequence(work->child40);
        if (!work->child40) {
            work->child44=CreateSequence(0x08114f1d,36,&f,parent);
            ADVANCE(event);
        }
        break;
    case 263:
        work->child44=PollSequence(work->child44);
        if (!work->child44) {
            work->child48=CreateSequence(0x081151a1,48,&g,parent);
            ADVANCE(event);
        }
        break;
    case 264:
        work->child48=PollSequence(work->child48);
        if (!work->child48) {
            work->child52=CreateSequence(0x081154d9,16,&h,parent);
            ADVANCE(event);
        }
        break;
    case 265: {
        register u32 mask_arg __asm__("r0");
        u32 mask;
        volatile u16 *shadow;
        PreparePair();
        CaptureBytePair(&first,&second);
        __asm__ volatile ("add %0, sp, #232\n\tldrb %0, [%0]" : "=l"(mask_arg) : : "memory");
        mask=PairMask(mask_arg);
        shadow=(volatile u16 *)0x03000940;
        __asm__("" : "+r"(shadow));
        {
            register u32 shadow_value __asm__("r1")=*shadow;
            __asm__("" : "+r"(shadow_value));
            shadow_value |= mask;
            __asm__("" : "+r"(shadow_value));
            *shadow=shadow_value;
        }
        __asm__ volatile ("mov %0, sp\n\tadd %0, #233\n\tldrb %0, [%0]" : "=l"(mask_arg) : : "memory");
        mask=PairMask(mask_arg);
        {
            register u32 shadow_value __asm__("r1")=*shadow;
            __asm__("" : "+r"(shadow_value));
            shadow_value |= mask;
            __asm__("" : "+r"(shadow_value));
            *shadow=shadow_value;
        }
        RestorePair(work->restore_x,work->restore_y);
        RestorePairEnd();
        ClearRecord(work->record);
        work->delay=StartDelay(0,30,parent);
        ADVANCE(event);
        break;
    }
    case 266:
        work->delay=PollDelay(work->delay);
        if (!work->delay) {
            work->child52=PollSequence(work->child52);
            if (!work->child52) {
                work->effect=StartRecordEffect(work->record,4,parent);
                ADVANCE(event);
            }
        }
        break;
    case 267:
        work->effect=PollRecordEffect(work->effect);
        if (!work->effect) PHASE(event)=2;
        break;
    default: break;
    }
    return 0;
}
__asm__(".global CreateSequence\n.thumb_set CreateSequence,0x8005b6d");
__asm__(".global PollSequence\n.thumb_set PollSequence,0x80e051d");
__asm__(".global PollOpening\n.thumb_set PollOpening,0x80e05dd");
__asm__(".global StartDelay\n.thumb_set StartDelay,0x80dfd69");
__asm__(".global PollDelay\n.thumb_set PollDelay,0x80dfed9");
__asm__(".global CreateOpening\n.thumb_set CreateOpening,0x80e03f9");
__asm__(".global CapturePair\n.thumb_set CapturePair,0x801e6f1");
__asm__(".global NativeCaseOne\n.thumb_set NativeCaseOne,0x80d38b5");
__asm__(".global PreparePair\n.thumb_set PreparePair,0x801e2a5");
__asm__(".global CaptureBytePair\n.thumb_set CaptureBytePair,0x801e611");
__asm__(".global PairMask\n.thumb_set PairMask,0x80035a9");
__asm__(".global RestorePair\n.thumb_set RestorePair,0x801e5e1");
__asm__(".global RestorePairEnd\n.thumb_set RestorePairEnd,0x801b879");
__asm__(".global ClearRecord\n.thumb_set ClearRecord,0x8115acd");
__asm__(".global StartRecordEffect\n.thumb_set StartRecordEffect,0x8115ae5");
__asm__(".global PollRecordEffect\n.thumb_set PollRecordEffect,0x8115b41");
__asm__(".global OriginalAuthoredSequence_00115560\n.thumb_set OriginalAuthoredSequence_00115560,AdvanceAuthoredDualSpriteSequence");
