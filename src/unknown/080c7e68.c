typedef unsigned int u32;
struct TreeNode;
struct Collection { struct TreeNode **cursor; u32 count; };
/* Store the node before reloading count; publish the advanced cursor last. */
u32 ListCallbackAppend(struct TreeNode *node, struct Collection *collection)
{
    struct TreeNode **cursor = collection->cursor;
    *cursor++ = node;
    collection->count++;
    collection->cursor = cursor;
    return 1;
}
