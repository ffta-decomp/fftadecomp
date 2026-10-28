typedef unsigned int u32;
struct TreeNode;
struct TreeSearch { u32 word; struct TreeNode *found; };
extern void CopyTreeNodeWords(struct TreeNode *node, u32 *word_out, u32 *ordering_out);
__asm__(".global CopyTreeNodeWords\n.thumb_set CopyTreeNodeWords,0x080c7b79");
u32 MatchTreeNodeWord(struct TreeNode *node, struct TreeSearch *search)
{
    u32 word = (u32)-1;
    u32 ordering_value;
    u32 result;
    CopyTreeNodeWords(node, &word, &ordering_value);
    if (search->word != word) {
        result = 1;
    } else {
        search->found = node;
        result = 0;
    }
    return result;
}
