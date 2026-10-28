/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081471E0.c
 * Original SHA-256: ab807aca41e9dfa17a2d24b53dd01f593df8509ecd513ff4734b1b0eaf9bba38
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 enabled;
    u16 phase;
    u16 duration;
    u16 unknown_06;
    void *data;
    void *context;
    u8 unknown_10[8];
} EffectPayload;

typedef struct EffectNode EffectNode;
struct EffectNode {
    u16 type;
    u16 flags;
    u16 handler;
    u16 group;
    u16 identifier;
    u16 unknown_0A;
    EffectPayload payload;
    EffectNode *previous;
    EffectNode *next;
};

typedef struct {
    void *allocator;
    EffectNode *head;
} EffectManager;

extern EffectManager data_03003C60;
extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);
extern void func_08146DC8(u16 group, u16 identifier, u32 mask);
extern void *func_08007138(void *allocator, u32 size);
extern void *func_0814873C(EffectNode *node);

/* 0x081471E0: 168 bytes; append and initialize an effect with a payload. */
void *func_081471E0(u16 group, u16 identifier, u16 duration, u16 flags,
                   void *context, void *data)
{
    EffectNode *node;
    void *handle;

    func_08146DC8(group, identifier, 0x1F);
    node = func_08007138(data_03003C60.allocator, sizeof(*node));
    g_callbacks_0836D4B8[0](node, sizeof(*node));
    if (data_03003C60.head == 0) {
        data_03003C60.head = node;
        node->previous = 0;
        node->next = 0;
    } else {
        EffectNode *last = data_03003C60.head;

        while (last->next)
            last = last->next;
        last->next = node;
        node->previous = last;
        node->next = 0;
    }

    if (node) {
        EffectPayload *payload = &node->payload;

        payload->phase = 0;
        payload->duration = duration;
        payload->context = context;
        payload->data = data;
        node->payload.enabled = 1;
        node->group = group;
        node->identifier = identifier;
        node->flags = flags;
        node->handler = 0x10;
        node->type = 1;
        handle = func_0814873C(node);
    } else {
        handle = 0;
    }
    return handle;
}
