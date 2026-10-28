/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DD4B4.c
 * Original SHA-256: eb0565180d4835f65f0fd8c70846156866b596b7010cec6811be5fae3b4cc317
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Group Group;
typedef struct {
    u32 value;
} Child;

extern Child *func_080A8810(Group *group, s32 index);

/* 080DD4B4..080DD4C4: 16 bytes. */
u32 func_080DD4B4(Group *group, u8 index)
{
    return func_080A8810(group, index)->value;
}
