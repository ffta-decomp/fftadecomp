/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080221E4.c
 * Original SHA-256: 1b443118b8fa290c24a5775163cff5428a8294d7e5799fb2ac389726fbe77313
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct ListNode080221E4 ListNode080221E4;

typedef struct TreeItem080221E4 {
    u8 unknown_00[0x10];
    s8 priority;
    u8 unknown_11[0x17];
    void *active;
    u8 unknown_2C[0x10];
    struct TreeItem080221E4 *left;
    struct TreeItem080221E4 *right;
    struct TreeItem080221E4 *parent;
} TreeItem080221E4;

typedef struct TreeOwner080221E4 {
    u8 unknown_00[0x0C];
    TreeItem080221E4 *root;
} TreeOwner080221E4;

extern TreeItem080221E4 *func_080C7B74(const ListNode080221E4 *node);

/* Complete [0x080221E4, 0x08022236): 82 bytes, 40 instructions. */
u32 func_080221E4(ListNode080221E4 *node, void *payload)
{
    TreeOwner080221E4 *owner = payload;
    TreeItem080221E4 *item = func_080C7B74(node);

    if (item->active != 0) {
        item->left = 0;
        item->right = 0;
        if (owner->root == 0) {
            owner->root = item;
        } else {
            TreeItem080221E4 *current = owner->root;

            for (;;) {
                if (current->priority > item->priority) {
                    if (current->left == 0) {
                        current->left = item;
                        break;
                    }
                    current = current->left;
                } else {
                    if (current->right == 0) {
                        current->right = item;
                        break;
                    }
                    current = current->right;
                }
            }
            item->parent = current;
        }
    }
    return 1;
}
