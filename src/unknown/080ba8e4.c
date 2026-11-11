#include "ffta/types.h"
struct BattleTransitionNode {
    u8 *unit;
    u8 unknown04[4];
    s16 x, y, z;
    u8 unknown0e[17];
    s8 direction;
    u8 unknown20[16];
    u32 flags;
    u8 unknown34[32];
    void *object;
};
struct BattleActorTransition {
    u32 content, unknown04;
    struct BattleTransitionNode *node;
    u16 unknown0c, counter;
    s16 original_y;
    u16 unknown12;
    void *effect;
    u8 flags, unknown19[3];
    u16 selector, depth;
    u16 continuation[1];
};
struct BattleTransitionShadow {
    u8 unknown00[74];
    volatile u8 enable, mask, level, fade;
};
typedef void (*SetTransitionObjectFields)(void *, u32, u32, u32, u32, u32);
extern struct BattleTransitionShadow TransitionShadow;
extern SetTransitionObjectFields TransitionObjectFields;
extern void StartTransitionCoordinates(s32, s32, s32);
extern u32 PollTransitionCoordinates(void);
extern void ApplyTransitionNodeOperation(struct BattleTransitionNode *, u32, s32, u32);
extern void PlayTransitionSound(u32);
extern void SetTransitionNodeDuration(struct BattleTransitionNode *, u32, u32);
extern void *CreateTransitionEffect(u32);
extern u8 PollTransitionEffect(void *);
extern void DestroyTransitionEffect(void *);
extern s32 DivideTransitionSigned(s32, s32);

u32 AdvanceBattleActorTransition(struct BattleActorTransition *state)
{
    switch (state->selector) {
    case 0:
        StartTransitionCoordinates(state->node->x, state->node->y, state->node->z);
        state->selector = 1;
        __asm__ __volatile__("" : : "m"(state->selector));
        break;
    case 1:
        if (PollTransitionCoordinates() != 0)
            break;
        goto pop_continuation;
    case 2:
        /* agbcc volatile-byte stores already emit the original read-before-store. */
        TransitionShadow.enable = 64;
        TransitionShadow.mask = 63;
        TransitionShadow.level = 0;
        TransitionShadow.fade = 16;
        state->counter = 0;
        ApplyTransitionNodeOperation(state->node, 3, 0, 0);
        {
            struct BattleTransitionNode *node = state->node;
            node->flags &= ~5;
            state->original_y = node->y;
            node->y += 80;
        }
        TransitionObjectFields(state->node->object, 1, 0, 0, 0, 0);
        PlayTransitionSound(200);
        state->selector = 3;
        __asm__ __volatile__("" : : "m"(state->selector));
        break;
    case 3:
        {
            s32 shadow_complete = 0;
            struct BattleTransitionNode *node;
            s32 difference, step;
            register s32 rounded __asm__("r2");
            state->counter++;
            if ((s16)state->counter > 1) {
                state->counter = 0;
                if (TransitionShadow.level <= 15) {
                    u32 level = TransitionShadow.level + 1;
                    TransitionShadow.level = level;
                } else if (TransitionShadow.fade != 0) {
                    u32 fade = TransitionShadow.fade - 1;
                    TransitionShadow.fade = fade;
                } else {
                    TransitionObjectFields(state->node->object, 0, 0, 0, 0, 0);
                    TransitionShadow.enable = 0;
                    shadow_complete = 1;
                }
            }
            {
                register s32 target_y __asm__("r2") = state->original_y;
                register struct BattleTransitionNode *working_node __asm__("r1");
                __asm__("" : "+r"(target_y));
                working_node = state->node;
                difference = target_y - working_node->y;
                rounded = difference;
                __asm__("" : "+r"(rounded));
                __asm__("" : "+r"(working_node) : "r"(difference), "r"(rounded));
                node = working_node;
            }
            if (difference < 0)
                rounded = difference + 7;
            step = rounded >> 3;
            if (step == 0 && difference != 0) {
                s32 magnitude = difference;
                if (magnitude < 0)
                    magnitude = -magnitude;
                step = DivideTransitionSigned(difference, magnitude);
            }
            node->y += step;
            {
                s32 magnitude = step;
                if (magnitude < 0)
                    magnitude = -magnitude;
                if (magnitude <= 0 && (state->flags & 1) == 0) {
                    ApplyTransitionNodeOperation(state->node, 4, 0, 0);
                    state->flags |= 1;
                }
            }
            if (step == 0 && shadow_complete != 0) {
                state->selector = 4;
        __asm__ __volatile__("" : : "m"(state->selector));
                state->counter = 0;
            }
        }
        break;
    case 4:
        state->counter++;
        if ((s16)state->counter > 7) {
            struct BattleTransitionNode *node;
            state->counter = 0;
            state->node->direction++;
            node = state->node;
            if (node->direction > 3) {
                node->direction = 0;
                {
                    register struct BattleTransitionNode *call_node __asm__("r0") = state->node;
                    __asm__("" : : "r"(call_node));
                    ApplyTransitionNodeOperation(call_node, 8, call_node->direction, 0);
                }
                state->selector = 5;
        __asm__ __volatile__("" : : "m"(state->selector));
            } else {
                ApplyTransitionNodeOperation(node, 9, node->direction, 0);
            }
        }
        break;
    case 5:
        state->counter++;
        if ((s16)state->counter > 3) {
            PlayTransitionSound(135);
            SetTransitionNodeDuration(state->node, 60, 0);
            state->selector = 8;
        __asm__ __volatile__("" : : "m"(state->selector));
            state->continuation[state->depth++] = 8;
            state->selector = 9;
        __asm__ __volatile__("" : : "m"(state->selector));
            state->continuation[state->depth++] = 9;
            state->selector = 6;
        __asm__ __volatile__("" : : "m"(state->selector));
        }
        break;
    case 6:
        state->effect = CreateTransitionEffect(state->content);
        state->selector = 7;
        __asm__ __volatile__("" : : "m"(state->selector));
        break;
    case 7:
        if (PollTransitionEffect(state->effect) != 0)
            break;
        DestroyTransitionEffect(state->effect);
        goto pop_continuation;
    case 8:
        goto complete;
    case 9:
        ApplyTransitionNodeOperation(state->node, 0, state->node->direction, 0);
        {
            struct BattleTransitionNode *node = state->node;
            register u8 *unit __asm__("r0") = node->unit;
            register u32 direction __asm__("r1") = (u8)node->direction;
            __asm__("" : "+r"(direction) : "r"(unit));
            unit[248] = (u8)direction;
        }
    pop_continuation:
        state->selector = state->continuation[--state->depth];
        __asm__ __volatile__("" : : "m"(state->selector));
        break;
    }
    goto pending;
complete:
    return 0;
pending:
    return 1;
}
asm(".set TransitionShadow,0x03000940\n"
    ".set TransitionObjectFields,0x08394034\n"
    ".thumb_set StartTransitionCoordinates,0x08096f3d\n"
    ".thumb_set PollTransitionCoordinates,0x08096f7d\n"
    ".thumb_set ApplyTransitionNodeOperation,0x0809836d\n"
    ".thumb_set PlayTransitionSound,0x08141521\n"
    ".thumb_set SetTransitionNodeDuration,0x0809a299\n"
    ".thumb_set CreateTransitionEffect,0x08091ac9\n"
    ".thumb_set PollTransitionEffect,0x08091bb1\n"
    ".thumb_set DestroyTransitionEffect,0x08092231\n"
    ".thumb_set DivideTransitionSigned,0x081426b9\n"
    ".thumb_set _call_via_r4,0x08142255\n");
