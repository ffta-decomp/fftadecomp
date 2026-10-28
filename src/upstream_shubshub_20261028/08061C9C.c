/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08061C9C.c
 * Original SHA-256: e5fa16af9c75f0eed68497fcd3a9823e4a453e90b086da6c264d906d4a7aa172
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 first;
    u32 second;
} Key08061C9C;

typedef struct {
    u8 text[0x14];
    Key08061C9C key;
    u8 status;
    u8 ready;
    u8 unknown_1E[2];
} Request08061C9C;

typedef struct {
    u8 unknown_00[0xCC];
    Request08061C9C request;
} Owner08061C9C;

typedef struct {
    u8 text[0x14];
    u8 status;
    u8 age;
    u8 unknown_16[6];
} Entry08061C9C;

typedef struct {
    u8 unknown_00[0x18];
    Key08061C9C keys[16];
    u8 unknown_98[0x17];
    u8 selected;
    u8 unknown_B0[0x7C8];
    Entry08061C9C entries[16];
} Cache08061C9C;

typedef void (*BufferInitializer08061C9C)(void *destination, u32 bytes);
typedef void (*BufferCopier08061C9C)(void *destination, const void *source,
                                    u32 bytes);

extern Owner08061C9C *data_0200F450;
extern Cache08061C9C g_state_020020D0;
extern BufferInitializer08061C9C g_callbacks_0836D4B8[];
extern BufferCopier08061C9C data_0836D4BC;
extern s32 func_08061BFC(const u8 *first, const u8 *second);
extern void func_08061C30(void);

/* 0x08061C9C..0x08061DD0: 308 bytes, 128 instructions. */
Entry08061C9C *func_08061C9C(void)
{
    Request08061C9C *request = &data_0200F450->request;
    int selected = 0;
    Entry08061C9C *entry = g_state_020020D0.entries;
    Entry08061C9C *oldest;
    int i;
    int minimum_age;

    for (i = 0; i < 16; ++i, ++entry) {
        if (entry->status &&
            request->key.first == g_state_020020D0.keys[i].first &&
            request->key.second == g_state_020020D0.keys[i].second &&
            func_08061BFC(request->text, entry->text) == 0) {
            entry->status = request->status;
            entry->age = 0xFF;
            g_state_020020D0.selected = i;
            func_08061C30();
            return entry;
        }
    }

    entry = g_state_020020D0.entries;
    oldest = 0;
    for (i = 0, minimum_age = 0xFF; i < 16; ++i, ++entry) {
        if (!entry->status) {
            g_state_020020D0.selected = i;
            g_state_020020D0.keys[i] = request->key;
            data_0836D4BC(entry, request->text, 0x14);
            entry->status = request->status;
            entry->age = 0xFF;
            request->ready = 1;
            func_08061C30();
            return entry;
        }
        if (minimum_age > entry->age) {
            minimum_age = entry->age;
            selected = i;
            oldest = entry;
        }
    }

    g_callbacks_0836D4B8[0](oldest, sizeof(*oldest));
    g_state_020020D0.keys[selected] = request->key;
    g_state_020020D0.selected = selected;
    data_0836D4BC(oldest, request->text, 0x14);
    oldest->status = request->status;
    oldest->age = 0xFF;
    request->ready = 1;
    func_08061C30();
    return oldest;
}
