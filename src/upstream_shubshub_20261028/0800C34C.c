/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800C34C.c
 * Original SHA-256: 606ca16e5e70248329d88ea33f30e841d5ab05e06a45cd33b2c56cddee58d4a9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 *objects[4];
    s16 handles[4];
} ObjectSlots0800C34C;

extern ObjectSlots0800C34C data_02009148;
extern void *data_02009140;

void func_08000D90(s32 handle);
void func_08007170(void *owner, u8 *object);

static inline void release_object(u8 *object)
{
    s32 j;
    s32 handle;

    for (j = 0; j < 4; j++) {
        if (data_02009148.objects[j] == object) {
            handle = data_02009148.handles[j];
            if (handle != -1) {
                func_08000D90(handle);
                data_02009148.handles[j] = -1;
            }
            func_08007170(data_02009140, object);
            data_02009148.objects[j] = 0;
            return;
        }
    }
}

/* 0x0800C34C - 128 bytes. */
void func_0800C34C(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (data_02009148.objects[i] != 0)
            release_object(data_02009148.objects[i]);
    }
}
