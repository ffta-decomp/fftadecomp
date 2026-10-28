/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D97D4.c
 * Original SHA-256: 851b86544e8ae80d89a2ef3ca230407b715dd513538123acbb0ccea3921dfe1e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
} ByteFields;

typedef struct {
    u8 unknown_00[0x18];
    ByteFields entries[0];
} ObjectState;

extern ObjectState *func_08005BFC(void *object);

void func_080D97D4(void *object, u8 index, u16 first, u16 second,
                  u16 third, u16 fourth)
{
    ObjectState *state = func_08005BFC(object);

    if ((s16)first != -1)
        state->entries[index].first = first;
    if ((s16)second != -1)
        state->entries[index].second = second;
    if ((s16)third != -1)
        state->entries[index].third = third;
    if ((s16)fourth != -1)
        state->entries[index].fourth = fourth;
}
