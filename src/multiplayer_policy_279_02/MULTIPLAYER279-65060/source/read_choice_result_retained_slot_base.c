#include "../../../../src/task_tree_core.h"
typedef signed short s16;
union ChoiceSlot {
    const void *record;
    u16 inline_value;
};
struct ChoiceOwner { u8 prefix[0x424]; union ChoiceSlot slots[0]; };
struct ChoicePayload {
    struct ChoiceOwner *owner;
    u16 flags;
    u16 one_based_selection;
    u8 mode;
};
typedef void (*CopyChoiceBytes)(void *, const void *, u32);
extern struct ChoicePayload *GetChoicePayload(TaskNode *);
asm(".global GetChoicePayload\n.thumb_set GetChoicePayload,0x08005bfd\n");
#define COPY_CHOICE_BYTES (*(CopyChoiceBytes *)0x0836d4bc)
/* Application menu result codec. The narrow unsigned decrement is preserved
 * before each arm's SIGNED16 index interpretation; no zero-selection guard.
 * Copy arms reload owner after the actual opaque copy callback.
 */
u32 RemainingCore48_00065060(TaskNode *task)
{
    struct ChoicePayload *payload;
    u16 index;
    payload = GetChoicePayload(task);
    index = payload->one_based_selection - 1;
    switch (payload->mode) {
    case 3:
        {
            struct ChoiceOwner *owner = payload->owner;
            const void *source = owner->slots[(s16)index].record;
            u32 offset;
            COPY_CHOICE_BYTES((u8 *)owner + (offset = 0xa3c), source, 16);
            return (u32)((u8 *)payload->owner + offset);
        }
    case 4:
        {
            struct ChoiceOwner *owner = payload->owner;
            const u16 *source = (const u16 *)owner->slots[(s16)index].record;
            return *source;
        }
    case 5:
        {
            struct ChoiceOwner *owner = payload->owner;
            const u8 *source = (const u8 *)owner->slots[(s16)index].record;
            return *source | 0x10000;
        }
    case 6:
        {
            u8 *owner = (u8 *)payload->owner;
            int byte_offset = (s16)index * 4;
            u8 *slots = owner + 0x424;
            /* Both are actual initialized native address operands: keep the
             * slot-field base materialized while signed byte_offset is live.
             * This emits no instruction and fabricates no output value. */
            asm("" : : "r"(slots), "r"(byte_offset));
            return *(u16 *)(slots + byte_offset) | 0x20000;
        }
    case 7:
        {
            struct ChoiceOwner *owner = payload->owner;
            const void *source = owner->slots[(s16)index].record;
            u32 offset;
            COPY_CHOICE_BYTES((u8 *)owner + (offset = 0xa4c), source, 264);
            return (u32)((u8 *)payload->owner + offset);
        }
    default:
        return 0;
    }
}
