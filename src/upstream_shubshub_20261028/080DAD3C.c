/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DAD3C.c
 * Original SHA-256: 47134b4b67ac81d9c1575c3f6bf708c8f5c7620303dc70e3fc24482293ccce97
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DAD3C..0x080DAD74: 56 bytes. */
typedef struct {
    u32 unknown_00;
    void *object;
} Payload080DAD3C;

extern void *func_08005BFC(void *task);
extern void *func_0800C614(const void *object);
extern void func_080DA1C4(s16 x, s16 y, u16 value, void *data);

void func_080DAD3C(void *task, u16 x, u16 y, u16 value)
{
    Payload080DAD3C *payload = func_08005BFC(task);
    void *data = func_0800C614(payload->object);

    func_080DA1C4((s16)x, (s16)y, value, data);
}
