/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D997C.c
 * Original SHA-256: 6eaa21789a9aa76474db016f029c5e00156038a0a03fc281f4522474d166a70e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D997C..0x080D99BE: 66 bytes. */
typedef struct {
    u8 unknown_00[4];
    void *resource;
    u8 type;
} ResourceObject;

extern ResourceObject *func_08005BFC(int index);
extern u8 *func_0800C614(void *resource);

u8 *func_080D997C(int index, u8 subindex)
{
    u8 *result = 0;
    ResourceObject *object = func_08005BFC(index);

    switch (object->type) {
    case 0:
        result = func_0800C614(object->resource);
        break;
    case 1:
        result = func_0800C614(object->resource) + subindex * 0x140;
        break;
    case 2:
        result = func_0800C614(object->resource) + subindex * 0x140;
        break;
    }
    return result;
}
