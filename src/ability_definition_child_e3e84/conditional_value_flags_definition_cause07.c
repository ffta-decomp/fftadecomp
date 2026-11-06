typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
typedef signed short s16;
typedef signed int s32;

struct DefinitionEvent {
    u16 state, unknown02;
    void *record;
    u32 unknown08[3];
    u16 orientation, variant;
    u32 unknown24;
};
struct PositionWords { u32 words[3]; };
/* E3F28..E3F30 scales variant by20, independently of the12B OUT object. */
struct MotionSequence { u32 words[5]; };
typedef char MotionSequenceSize[(sizeof(struct MotionSequence) == 20) ? 1 : -1];
struct SequenceTriplet { const void *sequence[3]; };
struct DefinitionEffect {
    u8 orientation, variant;
    u16 delay;
    s16 x, y;
    void *actor;
    void *record;
    struct PositionWords position;
    TaskNode *positioned;
    TaskNode *palette;
    TaskNode *accent_palette;
    TaskNode *motion;
    TaskNode *stage;
};
typedef char EventSize[(sizeof(struct DefinitionEvent) == 28) ? 1 : -1];
typedef char EffectSize[(sizeof(struct DefinitionEffect) == 48) ? 1 : -1];
extern const u8 gPositionSequence[];
extern const struct MotionSequence gMotionSequences[];
extern const u8 gStageSequence[];
extern const u8 gBackgroundImage[];
extern const struct SequenceTriplet gPaletteSequences;
extern const struct SequenceTriplet gAccentSequences;
extern void *ProjectActorWithDefaultTransition(void *, u16 *, u16 *, u16 *);
extern void ApplyDefinitionRecordCurrentValue(void *, u16);
extern void SelectActorFlag256(void *, u8);
/* The caller passes signed coordinate words; the callee stores their LOW16. */
extern TaskNode *CreatePositionedDefinitionTask(s32, s32, s32, u8, u32,
        void *, const void *, TaskNode *);
extern TaskNode *CreateDefinitionMotion(void *, const void *, u8, u16,
        u16, TaskNode *, u16);
extern TaskNode *CreateDefinitionStageTask(const void *, u8, u16, u16, TaskNode *);
extern void SetDefinitionBackground(const void *, u8, u8, s32, s32, u16);
extern TaskNode *CreateDefinitionPaletteTask(const void *, TaskNode *);
extern TaskNode *CreateDefinitionAccentTask(const void *, TaskNode *, u16);
extern void ResetDefinitionActor(void *);
extern TaskNode *PollPositionedDefinition(TaskNode *);
extern TaskNode *PollDefinitionPalette(TaskNode *);
extern TaskNode *PollDefinitionMotion(TaskNode *);

u32 AdvanceDefinitionEffect(TaskNode *, struct DefinitionEvent *, struct DefinitionEffect *) __asm__("RemainingBand43_000E3E84");
u32 AdvanceDefinitionEffect(TaskNode *task, struct DefinitionEvent *event,
                            struct DefinitionEffect *effect)
{
    switch (event->state) {
    case 0: {
        void *actor;
        void *record;
        effect->orientation = event->orientation;
        effect->variant = event->variant;
        /* The original captures this owner before publishing it to payload. */
        record = event->record;
        effect->record = record;
        actor = ProjectActorWithDefaultTransition(record,
                (u16 *)&effect->x, (u16 *)&effect->y, 0);
        effect->actor = actor;
        if (effect->variant == 1) {
            ApplyDefinitionRecordCurrentValue(actor, 36);
            SelectActorFlag256(effect->actor, 1);
        }
        break;
    }
    /* Task removal really invokes state1; this routine has no cleanup arm. */
    case 1:
        break;
    case 256: {
        u32 flags;
        u16 stage_flags;
        effect->positioned = CreatePositionedDefinitionTask(effect->x, effect->y,
                0, 1, 3, &effect->position, gPositionSequence, task);
        flags = (effect->orientation & 1) ? 4 : 2;
        effect->motion = CreateDefinitionMotion(effect->record,
                &gMotionSequences[effect->variant], 12, 0, flags, task, 60);
        stage_flags = (effect->orientation & 1) ? 16 : 8;
        effect->stage = CreateDefinitionStageTask(gStageSequence, 1,
                stage_flags | 4, 0, task);
        effect->delay = 12;
        ++event->state;
        break;
    }
    case 257: {
        struct SequenceTriplet palettes = gPaletteSequences;
        struct SequenceTriplet accents = gAccentSequences;
        /* The real producer supplies variants0..2; no synthetic clamp. */
        --effect->delay;
        if (effect->delay != 0)
            break;
        if (effect->variant != 2) {
            SetDefinitionBackground(gBackgroundImage, 0, 2, effect->x, effect->y, 0);
            effect->palette = CreateDefinitionPaletteTask(palettes.sequence[effect->variant], task);
        }
        effect->accent_palette = CreateDefinitionAccentTask(accents.sequence[effect->variant], task, 7);
        effect->delay = 3;
        ++event->state;
        break;
    }
    case 258:
        if (effect->delay != 0) {
            --effect->delay;
            if (effect->delay != 0)
                break;
            ResetDefinitionActor(effect->actor);
        }
        effect->positioned = PollPositionedDefinition(effect->positioned);
        if (effect->positioned != 0)
            break;
        effect->palette = PollDefinitionPalette(effect->palette);
        if (effect->palette != 0)
            break;
        effect->accent_palette = PollDefinitionPalette(effect->accent_palette);
        if (effect->accent_palette != 0)
            break;
        ++event->state;
        break;
    case 259:
        effect->motion = PollDefinitionMotion(effect->motion);
        if (effect->motion == 0)
            event->state = 2;
        break;
    }
    return 0;
}

asm(".global gPositionSequence\n.set gPositionSequence,0x083968C0\n"
    ".global gMotionSequences\n.set gMotionSequences,0x08396908\n"
    ".global gStageSequence\n.set gStageSequence,0x08396944\n"
    ".global gBackgroundImage\n.set gBackgroundImage,0x088F4680\n"
    ".global gPaletteSequences\n.set gPaletteSequences,0x08149C88\n"
    ".global gAccentSequences\n.set gAccentSequences,0x08149C94\n"
    ".global ProjectActorWithDefaultTransition\n.thumb_set ProjectActorWithDefaultTransition,0x080DD749\n"
    ".global ApplyDefinitionRecordCurrentValue\n.thumb_set ApplyDefinitionRecordCurrentValue,0x080DE10D\n"
    ".global SelectActorFlag256\n.thumb_set SelectActorFlag256,0x080DE3BD\n"
    ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x080D6099\n"
    ".global CreateDefinitionMotion\n.thumb_set CreateDefinitionMotion,0x080DCFE5\n"
    ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x080DFD8D\n"
    ".global SetDefinitionBackground\n.thumb_set SetDefinitionBackground,0x080D7221\n"
    ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x080D4705\n"
    ".global CreateDefinitionAccentTask\n.thumb_set CreateDefinitionAccentTask,0x080D4725\n"
    ".global ResetDefinitionActor\n.thumb_set ResetDefinitionActor,0x080DF8CD\n"
    ".global PollPositionedDefinition\n.thumb_set PollPositionedDefinition,0x080D6135\n"
    ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x080D4775\n"
    ".global PollDefinitionMotion\n.thumb_set PollDefinitionMotion,0x080DBA5D\n");
