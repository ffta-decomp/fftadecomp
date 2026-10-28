/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800C6CC.c
 * Original SHA-256: b84debbf83576857793cf9c1b05f7cbb84de9ecfc40008de57eae14225418980
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800C6CC - 64 bytes. Initialize the object slots and their owner. */
typedef struct {
    u8 *objects[4];
    s16 handles[4];
} ObjectSlots0800C6CC;

extern ObjectSlots0800C6CC data_02009148;
extern void *data_02009140;
void func_080105B8(void);

void func_0800C6CC(void *owner)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        data_02009148.objects[i] = 0;
        data_02009148.handles[i] = -1;
    }
    data_02009140 = owner;
    func_080105B8();
}
