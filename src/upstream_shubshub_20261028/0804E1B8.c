/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804E1B8.c
 * Original SHA-256: 1093fb3769099ae74f13b81d5ddb337869db49cf302c325af2613a83631b9fed
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804E1B8..0x0804E1DE: 38 bytes / 15 instructions. */
struct MenuContext0804E1B8 {
    u8 unknown_00[8];
    void *manager;
};

extern struct MenuContext0804E1B8 *data_0201F548;
extern void func_08005A24(void *manager);

s32 func_0804E1B8(void)
{
    if (data_0201F548 == 0 || data_0201F548->manager == 0)
        return -1;
    func_08005A24(data_0201F548->manager);
    return 0;
}
