#ifndef WORKER2_E4844_BATTLE_RECORD_EFFECT_H
#define WORKER2_E4844_BATTLE_RECORD_EFFECT_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct Task Task;
typedef struct EffectCommand {
    u16 state;
    u16 unknown_02;
    void *record;
    u8 unknown_08[12];
    u16 selector;
    u16 flags;
} EffectCommand;
typedef struct RecordEffectState {
    u8 selector;
    u8 flags;
    u16 delay;
    u16 x;
    u16 y;
    void *actor;
    void *record;
    u32 projection_binding;
    Task *projection;
    Task *palette;
    Task *intro_palette;
    Task *auxiliary;
    Task *record_effect;
    Task *timed_effect;
} RecordEffectState;
typedef struct DisplayShadowPrefix {
    u16 control;
} DisplayShadowPrefix;
#define OFFSET_OF(T,M) ((u32)&(((T *)0)->M))
typedef char command_selector_20[(OFFSET_OF(EffectCommand,selector)==20)?1:-1];
typedef char effect_x_4[(OFFSET_OF(RecordEffectState,x)==4)?1:-1];
typedef char effect_binding_16[(OFFSET_OF(RecordEffectState,projection_binding)==16)?1:-1];
typedef char effect_timed_40[(OFFSET_OF(RecordEffectState,timed_effect)==40)?1:-1];
extern DisplayShadowPrefix gDisplayShadow;
extern const void *const InitialPalettes[];
extern const void *const IntroPalettes[];
extern const void *const EmissionDefinitions[];
extern const void *const TimedDefinitions[];
extern const u8 ProjectionDefinition[];
extern const u8 PaletteSequence[];
extern const u8 AuxiliarySequence[];
extern void *ProjectRecord(void *,u16 *,u16 *,u16 *);
extern void CopyPalette(const void *,u32,u32,u32,u32);
/* Word views retain each native caller register, including signed coordinates
 * whose low halfword is consumed by the existing implementation. */
extern Task *CreateProjection(s32,s32,s32,u32,u32,void *,const void *,Task *);
extern Task *CreateRecordEffect(void *,u32,u32,u32,u32,Task *,u32);
extern Task *CreateIntroPalette(const void *,Task *,u32);
extern void EmitDefinition(const void *,u32,u32,s32,s32,u32);
extern Task *CreatePalette(const void *,Task *);
extern Task *CreateAuxiliary(const void *,Task *);
extern u32 DisplayMask(u32);
extern Task *CreateTimedEffect(const void *,u32,u32,u32,Task *);
extern Task *PollProjection(Task *);
extern Task *PollPalette(Task *);
extern Task *PollAuxiliary(Task *);
extern Task *PollRecordEffect(Task *);
#endif


/* Record-selected, coordinate-projected effect lifecycle. The original frame
 * contains only outgoing arguments; the two OUT halfwords belong to instance. */
u32 SequenceRecordEffect(Task *parent, EffectCommand *command,
                         RecordEffectState *instance)
    __asm__("RemainingBand43_000E4844");
u32 SequenceRecordEffect(Task *parent, EffectCommand *command,
                         RecordEffectState *instance)
{
    s32 state = command->state;
    switch (state) {
    case 0:
    {
        void *record;
        instance->selector = command->selector;
        instance->flags = command->flags;
        record = command->record;
        instance->record = record;
        instance->actor = ProjectRecord(record, &instance->x, &instance->y, 0);
        CopyPalette(InitialPalettes[instance->selector], 6, 0, 0, 1);
        break;
    }
    case 256:
    {
        s32 x = (s16)instance->x;
        s32 y = (s16)instance->y;
        u32 one = 1;
        u32 mode;
        instance->projection = CreateProjection(x,
            y, 0, 1, one, &instance->projection_binding,
            ProjectionDefinition, parent);
        one &= instance->flags;
        mode = 2;
        if (one != 0)
            mode = 4;
        instance->record_effect = CreateRecordEffect(instance->record,
            0, 12, 0, mode, parent, 50);
        instance->intro_palette = CreateIntroPalette(
            IntroPalettes[instance->selector], parent, 19);
        instance->delay = 12;
        command->state = command->state + 1;
        break;
    }
    case 257:
    {
        register u32 raw_count __asm__("r0") = instance->delay;
        u32 count;
        u32 mode;
        u32 flag_bit;
        const void *definition;
        /* The native raw decrement stays in R0 through STRH; only its
         * subsequent LOW16 working value becomes the later call argument. */
        raw_count -= 1;
        __asm__("" : "+r" (raw_count));
        instance->delay = raw_count;
        count = (u16)raw_count;
        if (count != 0)
            break;
        EmitDefinition(EmissionDefinitions[instance->selector], 0, 2,
            (s16)instance->x, (s16)instance->y, count);
        instance->palette = CreatePalette(PaletteSequence, parent);
        instance->auxiliary = CreateAuxiliary(AuxiliarySequence, parent);
        {
            u32 mask = DisplayMask(2);
            register u32 display __asm__("r1") = gDisplayShadow.control;
            /* Native R1 is the loaded shadow and destructive OR result, not
             * the helper mask in R0. Both definitions exist in readable C. */
            display |= mask;
            __asm__("" : "+r" (display));
            gDisplayShadow.control = display;
        }
        flag_bit = instance->flags & 1;
        mode = 8;
        if (flag_bit != 0)
            mode = 16;
        definition = TimedDefinitions[instance->selector];
        mode |= 4;
        instance->timed_effect = CreateTimedEffect(
            definition, 1, mode, 0, parent);
        command->state = command->state + 1;
        break;
    }
    case 258:
    {
        u32 palette_was_present;
        u32 palette_snapshot;
        instance->projection = PollProjection(instance->projection);
        if (instance->projection != 0)
            break;
        palette_snapshot = (u32)instance->palette;
        palette_was_present = ((0U - palette_snapshot) | palette_snapshot) >> 31;
        instance->palette = PollPalette((Task *)palette_snapshot);
        if (instance->palette != 0)
            break;
        if (palette_was_present != 0)
            gDisplayShadow.control &= ~DisplayMask(2);
        instance->auxiliary = PollAuxiliary(instance->auxiliary);
        if (instance->auxiliary != 0)
            break;
        instance->intro_palette = PollPalette(instance->intro_palette);
        if (instance->intro_palette != 0)
            break;
        instance->record_effect = PollRecordEffect(instance->record_effect);
        if (instance->record_effect != 0)
            break;
        command->state = 2;
        break;
    }
    }
    return 0;
}

__asm__(
    ".global ProjectRecord\n.thumb_set ProjectRecord,0x080dd749\n"
    ".global CopyPalette\n.thumb_set CopyPalette,0x080d45d1\n"
    ".global CreateProjection\n.thumb_set CreateProjection,0x080d6099\n"
    ".global CreateRecordEffect\n.thumb_set CreateRecordEffect,0x080dcfe5\n"
    ".global CreateIntroPalette\n.thumb_set CreateIntroPalette,0x080d4725\n"
    ".global EmitDefinition\n.thumb_set EmitDefinition,0x080d7221\n"
    ".global CreatePalette\n.thumb_set CreatePalette,0x080d4705\n"
    ".global CreateAuxiliary\n.thumb_set CreateAuxiliary,0x080d3e9d\n"
    ".global DisplayMask\n.thumb_set DisplayMask,0x080035a9\n"
    ".global CreateTimedEffect\n.thumb_set CreateTimedEffect,0x080dfd8d\n"
    ".global PollProjection\n.thumb_set PollProjection,0x080d6135\n"
    ".global PollPalette\n.thumb_set PollPalette,0x080d4775\n"
    ".global PollAuxiliary\n.thumb_set PollAuxiliary,0x080d3f09\n"
    ".global PollRecordEffect\n.thumb_set PollRecordEffect,0x080dba5d\n"
    ".global gDisplayShadow\n.set gDisplayShadow,0x03000940\n"
    ".global InitialPalettes\n.set InitialPalettes,0x08396cdc\n"
    ".global IntroPalettes\n.set IntroPalettes,0x08396cec\n"
    ".global EmissionDefinitions\n.set EmissionDefinitions,0x08396ce4\n"
    ".global TimedDefinitions\n.set TimedDefinitions,0x08396d04\n"
    ".global ProjectionDefinition\n.set ProjectionDefinition,0x08396cc4\n"
    ".global PaletteSequence\n.set PaletteSequence,0x08948d38\n"
    ".global AuxiliarySequence\n.set AuxiliarySequence,0x0894d6d4\n");
