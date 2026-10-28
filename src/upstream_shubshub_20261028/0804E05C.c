/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804E05C.c
 * Original SHA-256: 04531e83910f682ff7402a91c4068faaec59ce025c41a81c0770b8b94cadbbaa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 finished;
    u8 unknown_01[7];
    void *manager;
    void *allocation;
    u8 unknown_10[0x550];
    u8 value_560;
    u8 mode;
    u8 unknown_562[0xA06];
} MenuContext0804E05C;

typedef void (*ClearBuffer0804E05C)(void *destination, u32 size);

extern MenuContext0804E05C *data_0201F548;
extern ClearBuffer0804E05C const g_callbacks_0836D4B8[];
extern void *func_0804CA58(u32 size);
extern void func_0804CA6C(void *allocation);
extern void *func_08005C14(void *storage, u32 size);
extern void func_08005A24(void *manager);
extern void func_08005B18(void *manager);
extern void func_08005C34(void *manager);

/* Complete [0x0804E05C, 0x0804E128): 204 bytes, 78 instructions. */
void func_0804E05C(void *context, u8 *state)
{
    switch (*state) {
    case 0:
        {
            u8 *storage = func_0804CA58(0x4000);

            data_0201F548 = (MenuContext0804E05C *)storage;
            g_callbacks_0836D4B8[0](storage, sizeof(*data_0201F548));
            data_0201F548->allocation = storage;
            storage += sizeof(*data_0201F548);
            data_0201F548->manager = func_08005C14(storage,
                0x4000 - sizeof(*data_0201F548));
            data_0201F548->value_560 = 0;
            data_0201F548->mode = 0x11;
            *state = 2;
        }
        break;
    case 1:
        if (data_0201F548 != 0) {
            void *allocation = data_0201F548->allocation;

            func_08005A24(data_0201F548->manager);
            func_08005B18(data_0201F548->manager);
            func_08005C34(data_0201F548->manager);
            func_0804CA6C(allocation);
            data_0201F548 = 0;
            *state = 3;
        }
        break;
    case 2:
        if (data_0201F548->finished != 0)
            *state = 1;
        break;
    }
}
