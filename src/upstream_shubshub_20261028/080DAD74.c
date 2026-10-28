/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DAD74.c
 * Original SHA-256: 0f40a9b67dee48de7fad16720fc6382fc40d9879f56fb063e0efd326cc2b6ea4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DAD74..0x080DAD92: 30 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[4];
    void *object;
} TaskRecord;

extern TaskRecord *func_08005BFC(void *task);
extern void *func_0800C614(void *object);
extern void func_080DA77C(u32 value, u32 mode, void *output);

void func_080DAD74(void *task, u32 value)
{
    void *output = func_0800C614(func_08005BFC(task)->object);
    func_080DA77C(value, 3, output);
}
