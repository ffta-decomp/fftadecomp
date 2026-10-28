typedef unsigned char u8;
typedef unsigned int u32;

/* Only the three list-owner pointer offsets are established here. */
struct ListCountContext {
    u8 unknown_at_00[16];
    const void *list_at_10;
    const void *list_at_14;
    const void *list_at_18;
};

extern u32 CountLinkedNodes(const void *owner);

#if defined(COUNT_LIST_AT_10)
u32 CountContextListAt10(const struct ListCountContext *context)
{
    return CountLinkedNodes(context->list_at_10);
}
#elif defined(COUNT_LIST_AT_14)
u32 CountContextListAt14(const struct ListCountContext *context)
{
    return CountLinkedNodes(context->list_at_14);
}
#elif defined(COUNT_LIST_AT_18)
u32 CountContextListAt18(const struct ListCountContext *context)
{
    return CountLinkedNodes(context->list_at_18);
}
#endif
