/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08097478.c
 * Original SHA-256: c6ea9643f391ea5e20045c582085939060402561ff08d0942a787aa1255e5127
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x44];
    void *primary;
    u8 unknown_48[4];
    void *children[2];
} Group08097478;

extern u32 func_08021C3C(void *object);
extern u16 func_08021DE0(const void *object);
extern void func_08021DE4(void *object, u16 clear_flags, u16 set_flags);

/* 0x08097478..0x08097504: 140 bytes, 64 instructions. */
s32 func_08097478(Group08097478 *group, u32 identifier)
{
    s32 ready = 1;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (group->children[i]) {
            if (func_08021C3C(group->children[i]) == identifier) {
                func_08021DE4(group->children[i], 0, 0x100);
            } else if (!(func_08021DE0(group->children[i]) & 0x100)) {
                ready = 0;
            }
        }
    }
    if (group->primary) {
        if (func_08021C3C(group->primary) == identifier) {
            func_08021DE4(group->primary, 0, 0x100);
        } else if (!(func_08021DE0(group->primary) & 0x100)) {
            ready = 0;
        }
    }
    return ready;
}
