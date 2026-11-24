struct RangeRequestNode;

/* The caller consumes the unchanged full pointer before inspecting its links. */
struct RangeRequestNode *GetRangeRequestNode(struct RangeRequestNode *node)
    __asm__("CoreLibrary42_00148738");
struct RangeRequestNode *GetRangeRequestNode(struct RangeRequestNode *node)
{
    return node;
}
