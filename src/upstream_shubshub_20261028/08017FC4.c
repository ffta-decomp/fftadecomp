/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08017FC4.c
 * Original SHA-256: 09af6104700139fb65e008e386431927242ad0fc8fad6d878533bd235f2e0da1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08017FC4..0x08017FE2: 30 bytes. */
typedef struct {
    u8 unknown_00[0x16];
    u8 value;
} State08017FC4;

typedef struct {
    u32 unknown_00;
    State08017FC4 *state;
    u16 unknown_08;
    u16 value;
} Record08017FC4;

extern u8 func_08017B48(const State08017FC4 *state);

u16 func_08017FC4(const Record08017FC4 *record)
{
    return func_08017B48(record->state) * 8 + 8 + record->value;
}
