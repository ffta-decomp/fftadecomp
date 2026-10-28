typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ScenePathCommand {
    u16 phase;
    u8 reserved_02[2];
    u8 *owner;
    u32 repetitions;
    u32 tail;
    u8 reserved_10[4];
    u8 unit_selector;
    u8 reserved_15;
    u8 path_selector;
    u8 reserved_17;
    u16 delay;
};
struct SceneRepeatBytes { s8 repetitions; u8 tail; } __attribute__((packed));
union SceneRepeatFlags {
    u16 pair;
    struct SceneRepeatBytes bytes;
} __attribute__((packed));
struct ScenePathState {
    u8 *owner;
    void *unit;
    u8 *path;
    u8 count;
    u8 delay;
    union SceneRepeatFlags repeat;
};
typedef char StateSize[sizeof(struct ScenePathState)==16?1:-1];
typedef char StateRepeatOffset[(u32)&(((struct ScenePathState *)0)->repeat)==14?1:-1];
typedef char CommandSelectorOffset[(u32)&(((struct ScenePathCommand *)0)->unit_selector)==20?1:-1];
typedef char CommandPathOffset[(u32)&(((struct ScenePathCommand *)0)->path_selector)==22?1:-1];
typedef char CommandDelayOffset[(u32)&(((struct ScenePathCommand *)0)->delay)==24?1:-1];
extern u32 ResolveSceneCommandActor(u32 selector);
extern void *GetContentConsumerContext(void);
extern void *FindPrimaryBattleActor(void *context, void *unit);
extern u8 *GetScenePathBuffer(u32 selector);
extern void *AllocateSceneTaskBytes(u32 size);
extern void ReleaseSceneTaskAllocation(void *payload);
extern void *GetSceneBattleWorkBuffer(void);
extern void SubmitSceneWorkPaths(void *work, void *unit, u8 *path, u32 count);
extern void WriteSceneWorkOwnedHalfwords(void *work, u32 key, u16 first, u16 second, u16 third, u16 fourth);
extern void WriteSceneWorkOwnedByte(void *work, u32 key, u8 value);
extern u32 ContainsSceneWorkKey(const void *work, u32 key);
extern void FillScenePathWords(u8 *destination, u8 path_selector, u8 repetitions, u8 tail);
extern void (*const gIWRAMClear)(void *destination, u32 size);

u32 ProcessScenePathCommand(void *unused_context, struct ScenePathCommand *command, struct ScenePathState *state)
{
    switch (command->phase) {
    case 1:
        if (state->repeat.bytes.repetitions > 1 || state->repeat.bytes.tail != 0) {
            ReleaseSceneTaskAllocation(state->path);
            state->path = 0;
        }
        break;
    case 0:
        {
            void *unit;
            state->owner = command->owner;
            unit = (void *)ResolveSceneCommandActor(command->unit_selector);
            state->unit = FindPrimaryBattleActor(GetContentConsumerContext(), unit);
            state->repeat.bytes.repetitions = command->repetitions;
            state->repeat.bytes.tail = command->tail;
            if (state->repeat.pair == 1) {
                u8 *path = GetScenePathBuffer(command->path_selector);
                state->path = path;
                state->count = *(u32 *)(path + 128);
            } else {
                u32 path_selector = command->path_selector;
                s32 repetitions = state->repeat.bytes.repetitions;
                u8 *path = GetScenePathBuffer(path_selector);
                u8 sum = 0;
                register s32 guard_limit __asm__("r0") = repetitions;
                /* Native retains a guard copy separate from the stable repetition value.
                   Initialized read-only allocation constraint; emits no instruction. */
                asm("" : : "r"(guard_limit));
                if (sum < guard_limit) {
                    s32 remaining = guard_limit;
                    do {
                        sum = sum + *(u32 *)(path + 128);
                        remaining--;
                        path += 132;
                    } while (remaining != 0);
                }
                {
                    s32 adjustment = repetitions - 1;
                    s32 signed_sum = (s8)sum;
                    state->count = signed_sum - adjustment;
                }
                state->path = AllocateSceneTaskBytes((u32)state->count * 4);
                gIWRAMClear(state->path, (u32)state->count * 4);
                FillScenePathWords(state->path, command->path_selector,
                                   (u8)state->repeat.bytes.repetitions, state->repeat.bytes.tail);
            }
            state->delay = command->delay;
        }
        break;
    case 0x100:
        {
            void *work = GetSceneBattleWorkBuffer();
            SubmitSceneWorkPaths(work, state->unit, state->path, state->count);
            WriteSceneWorkOwnedHalfwords(work, (u32)state->unit, state->delay, 3, 4, state->delay);
            if (state->delay == 1)
                WriteSceneWorkOwnedByte(work, (u32)state->unit, 2);
            else
                WriteSceneWorkOwnedByte(work, (u32)state->unit, 0);
            command->phase = 0x101;
        }
        /* The setup arm immediately performs the polling arm. */
    case 0x101:
        if ((u8)ContainsSceneWorkKey(GetSceneBattleWorkBuffer(), (u32)state->unit) != 0)
            break;
        /* An absent key follows the same completion stores as phase0x103. */
    case 0x103:
        state->owner[6] = 1;
        command->phase = 3;
        break;
    }
    return 0;
}
asm(".global ResolveSceneCommandActor\n.thumb_set ResolveSceneCommandActor,0x08125579\n"
    ".global GetContentConsumerContext\n.thumb_set GetContentConsumerContext,0x08096d7d\n"
    ".global FindPrimaryBattleActor\n.thumb_set FindPrimaryBattleActor,0x08099561\n"
    ".global GetScenePathBuffer\n.thumb_set GetScenePathBuffer,0x08121c59\n"
    ".global AllocateSceneTaskBytes\n.thumb_set AllocateSceneTaskBytes,0x08121b65\n"
    ".global ReleaseSceneTaskAllocation\n.thumb_set ReleaseSceneTaskAllocation,0x08121b79\n"
    ".global GetSceneBattleWorkBuffer\n.thumb_set GetSceneBattleWorkBuffer,0x08121be9\n"
    ".global SubmitSceneWorkPaths\n.thumb_set SubmitSceneWorkPaths,0x0809d129\n"
    ".global WriteSceneWorkOwnedHalfwords\n.thumb_set WriteSceneWorkOwnedHalfwords,0x0809d98d\n"
    ".global WriteSceneWorkOwnedByte\n.thumb_set WriteSceneWorkOwnedByte,0x0809d9d9\n"
    ".global ContainsSceneWorkKey\n.thumb_set ContainsSceneWorkKey,0x0809d96d\n"
    ".global FillScenePathWords\n.thumb_set FillScenePathWords,0x08126ed9\n"
    ".global gIWRAMClear\n.set gIWRAMClear,0x0836d4b8\n"
    ".global _call_via_r0\n.thumb_set _call_via_r0,0x08142245\n"
    ".global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
    ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n"
    ".global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n"
    ".global _call_via_r5\n.thumb_set _call_via_r5,0x08142259\n"
    ".global _call_via_r6\n.thumb_set _call_via_r6,0x0814225d\n");
