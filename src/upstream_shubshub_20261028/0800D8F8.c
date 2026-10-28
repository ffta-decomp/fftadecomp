/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800D8F8.c
 * Original SHA-256: cdc65ff300cf8b895249689f7f3f3f49d76332e96b3e0c134cc96e7b9e4abea7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0800D8F8, 0x0800D95C), 100 bytes. */
typedef struct {
    u16 values[160];
} ValueRow;

extern ValueRow *func_0800C614(void *object);
extern void func_0800C64C(void *object);

void func_0800D8F8(void *object, u8 mode, u8 row, u8 index, u16 value)
{
    ValueRow *values = 0;

    switch (mode) {
    case 0:
        values = func_0800C614(object);
        break;
    case 1:
        values = func_0800C614(object) + row;
        break;
    case 2:
        values = func_0800C614(object) + row;
        break;
    }
    values->values[index] = value;
    func_0800C64C(object);
}
