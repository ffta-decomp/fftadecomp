typedef unsigned int u32;
struct RangeRequestNode {
    unsigned char unknown_prefix[36];
    struct RangeRequestNode *previous;
    struct RangeRequestNode *next;
};
struct RangeRequestPool {
    void *allocator;
    struct RangeRequestNode *head;
};
extern struct RangeRequestPool gRangeRequestPool;
extern u32 IsRangeRequestComplete(struct RangeRequestNode *request);
extern struct RangeRequestNode *GetRangeRequestNode(struct RangeRequestNode *request);
extern void FreeRangeRequest(void *allocator, struct RangeRequestNode *node);
__asm__(".set gRangeRequestPool,0x03003c60\n"
        ".thumb_set IsRangeRequestComplete,0x081485d5\n"
        ".thumb_set GetRangeRequestNode,0x08148739\n"
        ".thumb_set FreeRangeRequest,0x08007171");
struct RangeRequestNode *ReleaseCompletedRangeRequest(struct RangeRequestNode *request)
    __asm__("CoreFrontier_001484CC");
struct RangeRequestNode *ReleaseCompletedRangeRequest(struct RangeRequestNode *request)
{
    if (request && IsRangeRequestComplete(request)) {
        struct RangeRequestNode *node = GetRangeRequestNode(request);
        if (node) {
            struct RangeRequestNode *previous = node->previous;
            struct RangeRequestNode *next = node->next;
            if (previous) {
                previous->next = next;
                next->previous = previous;
            } else {
                gRangeRequestPool.head = next;
                next->previous = previous;
            }
            FreeRangeRequest(gRangeRequestPool.allocator, node);
        }
        return 0;
    }
    return request;
}
