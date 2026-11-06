typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Task;
struct DefinitionEvent {
    u16 state, unknown02;
    void *record;
    u32 unknown08[3];
    u16 definition, parameter;
    u32 unknown24;
};
struct DefinitionTargets {
    u8 target_count, target_index, delay, variant;
    u8 parameter, unknown05[3];
    struct Task *children[2];
    struct Task *auxiliary, *startup;
    void *record;
};
typedef char TargetsSize28[sizeof(struct DefinitionTargets)==28?1:-1];
typedef char EventSize28[sizeof(struct DefinitionEvent)==28?1:-1];
typedef char RecordOffset24[(u32)&((struct DefinitionTargets*)0)->record==24?1:-1];
typedef u32 (*DefinitionCallback)(struct Task*, struct DefinitionEvent*, void*);
/* R2 is the real initialized fullword0/5; retail callee E0402..404
 * consumes LOW8 itself. Canonical helper implementation remains unchanged. */
extern struct Task *CreateDefinitionStartupRawCount(void *, const void *, u32, u8,
                                             const s16 *, struct Task *);
extern void ClearDefinitionDisplay(void);
extern struct Task *PollDefinitionStartup(struct Task *);
extern u32 GetDefinitionTargetCount(void *, u16);
extern struct Task *CreateDefinitionAuxiliary(const void *, struct Task *);
/* This caller consumes the callee-zero-extended full R0 without a caller cast. */
extern u32 GetDefinitionDisplayMask(u8);
extern u32 PollDefinitionTaskArray(struct Task **, u16);
extern void *GetDefinitionTargetRecord(void *, u8);
extern struct Task *CreateDefinitionChild(DefinitionCallback, u16,
                                          struct DefinitionEvent *, struct Task *);
extern u32 AdvanceDefinitionEffect(struct Task *, struct DefinitionEvent *, void *);
extern struct Task *PollDefinitionAuxiliary(struct Task *);
extern const u8 gDefinitionStartupSequence[], gDefinitionAuxiliarySequence[];
extern u16 gDefinitionDisplayShadow;

u32 AdvanceDefinitionTargetSequence(struct Task *task, struct DefinitionEvent *event,
                                    struct DefinitionTargets *targets)
{
    struct DefinitionEvent child;
    u16 state = event->state;
    switch (state) {
    case 0: {
        register u32 count __asm__("r4");
        u32 mode;
        targets->parameter = event->parameter;
        targets->record = event->record;
        targets->variant = state;
        if ((s16)event->definition == 101)
            targets->variant = 1;
        else if ((s16)event->definition == 265)
            targets->variant = 2;
        count = 5;
        if (targets->parameter != 0)
            count = 0;
        /* Actual unmodified 0-or-5 count is live here before mode selection. */
        __asm__("" : : "r"(count));
        mode = 1;
        if (targets->variant == 2)
            mode = 7;
        targets->startup = CreateDefinitionStartupRawCount(targets->record,
                    gDefinitionStartupSequence, count, mode, 0, task);
        break;
    }
    case 1:
        ClearDefinitionDisplay();
        break;
    case 256: {
        u32 count, mask;
        targets->startup = PollDefinitionStartup(targets->startup);
        if (targets->startup != 0)
            break;
        count = GetDefinitionTargetCount(targets->record, 0);
        targets->target_count = count;
        if (targets->variant == 2)
            targets->target_count = count - 1;
        if (targets->target_count == 0) {
            event->state = 2;
            break;
        }
        targets->auxiliary = CreateDefinitionAuxiliary(gDefinitionAuxiliarySequence, task);
        mask = GetDefinitionDisplayMask(2);
        {
            u32 combined_shadow = gDefinitionDisplayShadow | mask;
            register u32 index_zero __asm__("r3") = 0;
            /* Native E4126..412A defines this real zero after computing the
             * combined shadow, rather than keeping an earlier NULL alive. */
            __asm__("" : "+r"(index_zero) : "r"(combined_shadow));
            gDefinitionDisplayShadow = combined_shadow;
            targets->delay = 1;
            targets->target_index = index_zero;
        }
        ++event->state;
        break;
    }
    case 257: {
        struct Task **children = targets->children;
        u32 slot, occupied;
        PollDefinitionTaskArray(children, 2);
        --targets->delay;
        if (targets->delay != 0)
            break;
        /* The native slot choice precedes all child-construction helpers. */
        occupied = (u32)targets->children[0];
        slot = ((0u - occupied) | occupied) >> 31;
        child.definition = targets->target_index;
        child.parameter = targets->variant;
        child.record = GetDefinitionTargetRecord(targets->record, targets->target_index);
        /* The real creator overwrites child.state; other unused bytes stay unspecified. */
        {
            struct Task *created = CreateDefinitionChild(AdvanceDefinitionEffect, 48, &child, task);
            u32 byte_offset = slot * sizeof(*children);
            struct Task **destination = (struct Task **)((u8 *)children + byte_offset);
            *destination = created;
        }
        targets->delay = 54;
        ++targets->target_index;
        if (targets->target_index == targets->target_count)
            ++event->state;
        break;
    }
    case 258: {
        u32 mask;
        targets->auxiliary = PollDefinitionAuxiliary(targets->auxiliary);
        if (targets->auxiliary != 0)
            break;
        if ((u8)PollDefinitionTaskArray(targets->children, 2) == 0)
            break;
        mask = GetDefinitionDisplayMask(2);
        gDefinitionDisplayShadow &= ~mask;
        event->state = 2;
        break;
    }
    }
    return 0;
}

asm(".global CreateDefinitionStartupRawCount\n.thumb_set CreateDefinitionStartupRawCount,0x080E03F9\n"
    ".global ClearDefinitionDisplay\n.thumb_set ClearDefinitionDisplay,0x080D38B5\n"
    ".global PollDefinitionStartup\n.thumb_set PollDefinitionStartup,0x080E05DD\n"
    ".global GetDefinitionTargetCount\n.thumb_set GetDefinitionTargetCount,0x080D8859\n"
    ".global CreateDefinitionAuxiliary\n.thumb_set CreateDefinitionAuxiliary,0x080D3E9D\n"
    ".global GetDefinitionDisplayMask\n.thumb_set GetDefinitionDisplayMask,0x080035A9\n"
    ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x080E0571\n"
    ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x080DD4A5\n"
    ".global CreateDefinitionChild\n.thumb_set CreateDefinitionChild,0x08005B6D\n"
    ".global AdvanceDefinitionEffect\n.thumb_set AdvanceDefinitionEffect,0x080E3E85\n"
    ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x080D3F09\n"
    ".global gDefinitionStartupSequence\n.set gDefinitionStartupSequence,0x08396884\n"
    ".global gDefinitionAuxiliarySequence\n.set gDefinitionAuxiliarySequence,0x0894D690\n"
    ".global gDefinitionDisplayShadow\n.set gDefinitionDisplayShadow,0x03000940\n");
