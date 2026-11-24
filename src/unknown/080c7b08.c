typedef unsigned int u32;

/* The observed list node stores its lookup word at +0 and next at +8. */
struct LinkedNode {
    u32 word;
    u32 unknown_at_04;
    struct LinkedNode *next;
};
/* The owner stores a separate word and the first node pointer. */
struct ListOwner {
    u32 word;
    struct LinkedNode *head;
};

#if defined(LIST_COUNT)
u32 CountLinkedNodes(const struct ListOwner *owner)
{
    const struct LinkedNode *node = owner->head;
    u32 count = 0;
    while (node != 0) {
        node = node->next;
        count++;
    }
    return count;
}
#elif defined(LIST_GET_WORD0)
u32 GetListOwnerWord0(const struct ListOwner *owner)
{
    return owner->word;
}
#elif defined(LIST_COPY_OWNER_WORDS)
void CopyListOwnerWords(const struct ListOwner *owner,
                        struct LinkedNode **head_out, u32 *word_out)
{
    *head_out = owner->head;
    *word_out = owner->word;
}
#elif defined(LIST_COPY_NODES)
u32 CopyListNodes(const struct ListOwner *owner, struct LinkedNode **out)
{
    const struct LinkedNode *node = owner->head;
    while (node != 0) {
        *out++ = (struct LinkedNode *)node;
        node = node->next;
    }
    return 0;
}
#elif defined(LIST_FIND_WORD)
struct LinkedNode *FindListNodeByWord(const struct ListOwner *owner, u32 word)
{
    struct LinkedNode *node = owner->head;
    while (node != 0) {
        if (word == node->word)
            return node;
        node = node->next;
    }
    return 0;
}
#elif defined(LIST_SET_WORDS)
void SetListWords(struct ListOwner *owner, struct LinkedNode *head, u32 word)
{
    owner->head = head;
    owner->word = word;
}
#endif
