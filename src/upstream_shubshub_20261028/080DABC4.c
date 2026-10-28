/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DABC4.c
 * Original SHA-256: a0a8c6821420b5063e621329e302ca464bab3b31c7fae438abd721cb0f139862
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *object;
} DrawingState;

extern DrawingState *func_08005BFC(void *object);
extern void *func_0800C614(void *object);
extern void func_080DA3B8(s16 x, s16 y, s16 width, s16 height, void *buffer);
extern void func_080DA598(s16 x, s16 y, s16 width, s16 height, void *buffer);

void func_080DABC4(void *object, u16 x, u16 y, u16 width, u16 height, u8 mode)
{
    void *buffer = func_0800C614(func_08005BFC(object)->object);

    if (mode == 0)
        func_080DA3B8((s16)x, (s16)y, (s16)width, (s16)height, buffer);
    else
        func_080DA598((s16)x, (s16)y, (s16)width, (s16)height, buffer);
}
