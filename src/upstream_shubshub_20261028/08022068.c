/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022068.c
 * Original SHA-256: 68da8f4985cae94a3200bfdaa36804568f35198cc10c7d1ca24e32bb53417703
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08022068..0x08022080: 24 bytes. */
typedef struct ListContext08022068 ListContext08022068;
typedef struct ListNode08022068 ListNode08022068;
typedef u32 (*ListCallback08022068)(ListNode08022068 *node, void *payload);

extern u32 func_080221BC(ListNode08022068 *node, void *payload);
extern void func_080C7CC0(ListContext08022068 *list,
                         ListCallback08022068 callback, void *payload);

void func_08022068(u8 *object)
{
    func_080C7CC0(*(ListContext08022068 **)(object + 8),
                  func_080221BC, object + 0x14);
}
