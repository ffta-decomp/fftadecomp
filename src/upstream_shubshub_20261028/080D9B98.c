/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D9B98.c
 * Original SHA-256: 25198bab7b5faf6a3b386e5ebc5ee502078e61cdbb4495b50756a659afb33864
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D9B98..0x080D9BA8: 16 bytes. */
typedef struct {
    u8 unknown_00[4];
    void *resource;
} ResourceObject;

extern ResourceObject *func_08005BFC(int index);
extern void func_0800C64C(void *resource);

void func_080D9B98(int index)
{
    func_0800C64C(func_08005BFC(index)->resource);
}
