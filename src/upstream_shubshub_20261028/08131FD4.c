/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08131FD4.c
 * Original SHA-256: 293ea401ccbf353bf60b5568013d746d791f4d2e9a1d497d998a07276b1f6861
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x105];
    u8 value_105;
    u8 unknown_106;
    u8 value_107;
} NestedRecord;

typedef struct {
    u8 unknown_00[8];
    NestedRecord *nested;
    u8 unknown_0C[2];
    u16 value_0E;
    u8 unknown_10[0x16];
    u16 flags;
} RecordContext;

s32 func_080C7EA4(const void *object, u32 selector);
void func_080CAF78(void *object, u16 value, u8 slot);
u8 func_080CB54C(void *object, u8 enabled);
void func_080CA2E8(void *object);

void func_08131FD4(RecordContext *object)
{
    s32 slot;

    if ((object->flags & 0x10) == 0) {
        for (slot = 0; slot < 5; slot++) {
            u16 value = func_080C7EA4(object->nested, (u8)(slot + 0x1D));

            if (value == 0) {
                NestedRecord *nested;

                func_080CAF78(object->nested, object->value_0E, slot);
                func_080CB54C(object->nested, 1);
                nested = object->nested;
                if (object->value_0E == nested->value_105)
                    nested->value_105 = nested->value_107;
                break;
            }
        }
        func_080CA2E8(object->nested);
    }
}
