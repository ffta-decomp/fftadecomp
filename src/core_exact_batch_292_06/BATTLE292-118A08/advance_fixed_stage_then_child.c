typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct EffectRequest {
    u16 state, unknown_02;
    void *owner;
};
struct StageThenChild {
    u32 unknown_00;
    void *child, *owner, *stage;
};
union StageCoordinates {
    u32 packed;
    s16 coordinates[2];
};
typedef char PayloadSizeIs16[sizeof(struct StageThenChild) == 16 ? 1 : -1];
typedef char CoordinatesSizeIs4[sizeof(union StageCoordinates) == 4 ? 1 : -1];
extern u16 DefinitionShadow[];
extern const u8 FixedStageDefinition[];
extern void BiosCpuSet(const void *, void *, u32);
extern void *CreateDefinitionEffectTask(void *, const void *, u8, u8,
                                      const s16 *, void *);
extern void *PollDefinitionEffect(void *);
extern void *CreateIndexedChild(u8, void *, void *);
extern void *PollIndexedChild(void *);

u32 AdvanceFixedStageThenChild(void *, struct EffectRequest *, struct StageThenChild *)
    __asm__("RemainingBand43_00118A08");
u32 AdvanceFixedStageThenChild(void *context, struct EffectRequest *request,
                              struct StageThenChild *effect)
{
    u16 state = request->state;
    switch (state) {
    case 0: {
        union StageCoordinates position;
        u16 first_zero, second_zero;
        u16 *shadow;
        effect->owner = request->owner;
        position.packed = 0x00b80068;
        first_zero = state;
        shadow = DefinitionShadow;
        BiosCpuSet(&first_zero, shadow, 0x01000040);
        second_zero = state;
        shadow += 256;
        BiosCpuSet(&second_zero, shadow, 0x01000070);
        effect->stage = CreateDefinitionEffectTask(effect->owner,
            FixedStageDefinition, 3, 6, position.coordinates, context);
        break;
    }
    case 1:
        break;
    case 256:
        effect->stage = PollDefinitionEffect(effect->stage);
        if (effect->stage != 0)
            break;
        effect->child = CreateIndexedChild(1, effect->owner, context);
        /* The constructor can change the live request before this increment. */
        request->state++;
        break;
    case 257:
        effect->child = PollIndexedChild(effect->child);
        if (effect->child != 0)
            break;
        request->state = 2;
        break;
    }
    return 0;
}

/* Absolute aliases issue no instructions and retain the existing implementations. */
__asm__(
    ".global DefinitionShadow\n.set DefinitionShadow,0x03003920\n"
    ".global FixedStageDefinition\n.set FixedStageDefinition,0x083a6110\n"
    ".global BiosCpuSet\n.thumb_set BiosCpuSet,0x0814186d\n"
    ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080e03f9\n"
    ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x080e05dd\n"
    ".global CreateIndexedChild\n.thumb_set CreateIndexedChild,0x080f2e41\n"
    ".global PollIndexedChild\n.thumb_set PollIndexedChild,0x080f1211\n"
);
