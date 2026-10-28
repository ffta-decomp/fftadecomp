/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080221BC.c
 * Original SHA-256: 3e7930c892510876dbfefa371e79f734b58996a2f2a9ffcb627e3df4d9fa392f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x080221BC, 0x080221E4), 40 bytes. */
typedef struct ListNode ListNode;

typedef struct {
    u32 flags;
    u8 unknown_04[0x28];
    u32 value_2C;
} Object080221BC;

extern Object080221BC *func_080C7B74(const ListNode *node);

u32 func_080221BC(ListNode *node, void *payload)
{
    Object080221BC *object = func_080C7B74(node);

    if (object->value_2C != 0)
    {
        object->flags &= ~0x30000;
        object->flags &= ~0x80000;
    }
    return 1;
}
