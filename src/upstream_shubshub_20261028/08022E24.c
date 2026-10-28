/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022E24.c
 * Original SHA-256: ad2503542215d8d34e02a2a8aff57834609a8670b03ad1dc43ff9dd611a1fb72
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x5C];
    void *buffer;
} BufferState08022E24;

extern BufferState08022E24 g_state_0200F390;
extern u8 data_03003860[];
extern void (*data_0836D4BC)(void *destination, const void *source, u32 length);
extern void *func_08022840(u32 size);

/* 0x08022E24: 52 bytes; lazily allocate and populate the cached buffer. */
void func_08022E24(void)
{
    if (!g_state_0200F390.buffer) {
        g_state_0200F390.buffer = func_08022840(0x400);
        data_0836D4BC(g_state_0200F390.buffer, data_03003860, 0x400);
    }
}
