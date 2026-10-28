/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801B7F8.c
 * Original SHA-256: 0eec98a873d5449ddb0f1e75af8415567fad2afe5bd31dbbe8c71aa907f58bf6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct State0801B7F8 State0801B7F8;

extern void func_0801AF08(State0801B7F8 *state, void *first, void *second,
                          void *buffer, void *secondary_buffer, u8 enabled);

/* 0x0801B7F8 - 28 bytes.
 * Target: 30b582b0059d069c2406240e00950194fff77efb02b030bc01bc0047
 */
void func_0801B7F8(State0801B7F8 *state, void *first, void *second,
                   void *buffer, void *secondary_buffer, u8 enabled)
{
    func_0801AF08(state, first, second, buffer, secondary_buffer, enabled);
}
