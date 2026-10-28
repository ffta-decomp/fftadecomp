/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D615C.c
 * Original SHA-256: 6132e0f03c0f71f608265d6be7163fea1a5b852acf2952668a502e05fcdd7809
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct TaskData080D615C {
    u16 first;
    u16 second;
    u16 third;
};

extern struct TaskData080D615C *func_08005BFC(void *task);

/* Complete [0x080D615C, 0x080D6180): 36 bytes, 17 instructions. */
void func_080D615C(void *task, u16 first, u16 second, u16 third)
{
    struct TaskData080D615C *data = func_08005BFC(task);

    data->first = first;
    data->second = second;
    data->third = third;
}
