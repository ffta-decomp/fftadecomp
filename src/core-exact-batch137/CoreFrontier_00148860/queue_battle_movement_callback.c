#include "../../../src/task_tree_core.h"
typedef signed short s16;
typedef signed int s32;
typedef void (*PositionCallback)(void *, s16, s16, void *);
struct MovementWorkNode {
    void *work;
    s16 requested_ticks;
    u16 accumulated_ticks;
    PositionCallback callback;
    void *context;
    struct MovementWorkNode *left;
    struct MovementWorkNode *right;
    struct MovementWorkNode *parent;
};
struct MovementWorkQueue {
    struct MovementWorkNode nodes[16];
    struct MovementWorkNode *root;
    /* Both bounds are reduced by new requests; their wider roles are tentative. */
    s32 first_limit;
    s32 second_limit;
    s32 count;
};
typedef char MovementWorkNodeMustBe28Bytes[sizeof(struct MovementWorkNode)==28?1:-1];
typedef char MovementWorkQueueMustBe464Bytes[sizeof(struct MovementWorkQueue)==464?1:-1];
extern struct MovementWorkQueue gMovementWorkQueue;
extern u32 QueryBattleObjectStateFour(void *);

void QueueBattleMovementCallback(void *work, s32 ticks, PositionCallback callback, void *context)
{
    if (ticks > 0) {
        struct MovementWorkQueue *queue = &gMovementWorkQueue;
        if (queue->count <= 15 && QueryBattleObjectStateFour(work) != 1) {
            struct MovementWorkNode *node = &queue->nodes[queue->count++];
            if (queue->second_limit > ticks)
                queue->second_limit = ticks;
            if (queue->first_limit > ticks)
                queue->first_limit = ticks;
            node->work = work;
            node->requested_ticks = ticks;
            node->left = 0;
            node->right = 0;
            node->parent = 0;
            node->accumulated_ticks = 0;
            node->callback = callback;
            node->context = context;
            if (queue->root == 0)
                queue->root = node;
            else {
                struct MovementWorkNode *current = queue->root;
                s32 key = (s16)ticks;
                struct MovementWorkNode *next;
                /* Keep the shared advance edge after the right-child test. */
probe_node:
                if (current->requested_ticks >= key) {
                    next = current->left;
                    if (next != 0)
                        goto advance_node;
                    current->left = node;
                    goto attached;
                }
                next = current->right;
                if (next == 0)
                    goto attach_right;
advance_node:
                current = next;
                goto probe_node;
attach_right:
                current->right = node;
attached:
                node->parent = current;
            }
        }
    }
}
asm(".global gMovementWorkQueue\n.set gMovementWorkQueue,0x03005f30\n"
    ".global QueryBattleObjectStateFour\n.thumb_set QueryBattleObjectStateFour,0x08149369\n");
