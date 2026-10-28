/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D9ADC.c
 * Original SHA-256: 4f393304fedb7620faf5ee40b5fb9fad903db14eb3349998a1802f603f456f6c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    void *object;
} TaskData;

extern TaskData *func_08005BFC(void *task);
extern void func_0800DAB8(void *object, s16 start, u8 count, u8 first, u8 second);

/* 080D9ADC..080D9B06: 42 bytes. */
void func_080D9ADC(void *task, u8 first, u8 second)
{
    TaskData *data = func_08005BFC(task);

    func_0800DAB8(data->object, 0, 160, first, second);
}
