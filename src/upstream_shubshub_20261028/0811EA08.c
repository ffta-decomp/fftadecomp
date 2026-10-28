/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0811EA08.c
 * Original SHA-256: b951e5cb216f9dbf1f605cccfca64074a78a2b8489c9a7c8740bac6bb98de509
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0811EA08, 0x0811EA66), 94 bytes, 44 instructions.
 * These are offset views; complete object extents remain unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *context;
    u8 unknown_08[12];
    s16 selector;
} Descriptor0811EA08;

typedef struct {
    void *child;
} Payload0811EA08;

extern void *func_080D3508(u16 resource, u32 mode, void *context);
extern void func_080D35D8(void);
extern void *func_080D3888(void *task);

u32 func_0811EA08(void *task, Descriptor0811EA08 *descriptor,
                  Payload0811EA08 *payload)
{
    switch (descriptor->phase) {
    case 0:
        if (descriptor->selector == 0x19a)
            payload->child = func_080D3508(0x165, 0, descriptor->context);
        else
            payload->child = func_080D3508(0x164, 0, descriptor->context);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        payload->child = func_080D3888(payload->child);
        if (payload->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
