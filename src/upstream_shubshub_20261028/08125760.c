/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08125760.c
 * Original SHA-256: 73c54966f0a9b96958f711c787f17033f15ff0c68cf0fd8ab62187aa450d1344
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x08125760, 0x081257D0), 112 bytes including literal. */
typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2a[0x108 - 0x2a];
} SceneRecord08125760;

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} SceneObject08125760;

extern SceneRecord08125760 g_state_02000080[24];
extern SceneRecord08125760 *func_08121CB4(u8);
extern SceneRecord08125760 *func_080C83CC(u8);
extern void *func_08096D7C(void);
extern SceneObject08125760 *func_08099560(void *, SceneRecord08125760 *);

static inline SceneRecord08125760 *resolve_record(u8 selector)
{
    SceneRecord08125760 *record;
    s32 index;

    if (selector == 255) {
        record = g_state_02000080;
        for (index = 0; index < 24; index++, record++) {
            if (record->flags & 0x400)
                return record;
        }
        return 0;
    } else if ((s8)selector < 0) {
        return func_08121CB4(selector);
    } else {
        return func_080C83CC(selector);
    }
}

void func_08125760(u8 selector, u16 clear_mask, u16 set_mask)
{
    SceneRecord08125760 *record = resolve_record(selector);
    SceneObject08125760 *object;

    object = func_08099560(func_08096D7C(), record);
    object->flags = (object->flags & ~clear_mask) | set_mask;
}
