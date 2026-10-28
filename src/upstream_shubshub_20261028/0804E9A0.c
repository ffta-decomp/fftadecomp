/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804E9A0.c
 * Original SHA-256: 40246d31f7f0a535c2d273012408a800299f7c577f8b772ee2a6f72b8dc3ebac
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 value;
} TaskData;

extern TaskData *func_08005BFC(void *task);

/* 0804E9A0..0804E9AE: 14 bytes. */
void func_0804E9A0(void *task)
{
    TaskData *data = func_08005BFC(task);

    data->value = 0x80;
}
