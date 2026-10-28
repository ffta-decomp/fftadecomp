/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806E4E0.c
 * Original SHA-256: 3381c3c1e0efcd53a43b02632c2d319631ccf95a8ad46e2ef0d6671f1a7ce2f5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2c];
    u8 list[0x30];
    u8 unknown_5c;
    u8 row;
    u8 unknown_5e[2];
    u8 settings[1];
} Object0806E4E0;

extern s16 func_08017B68(void *list, s32 row);
extern void func_08017FBC(void *settings, u32 option);
extern void func_08017E28(void *settings);

/* 0x0806E4E0..0x0806E526: 70 bytes, 32 instructions. */
void func_0806E4E0(Object0806E4E0 *object)
{
    s32 row = object->row;
    s16 count = func_08017B68(object->list, (s8)row);
    s16 i;

    for (i = 0; i < count; i++) {
        func_08017FBC(object->settings, 0x80);
        func_08017E28(object->settings);
    }
}
