/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08097000.c
 * Original SHA-256: b30fdea04e25efd1d84c10175699a6baa301eece76645cb704433214ecb8fa58
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct List08097000 List08097000;
typedef struct ListOwner08097000 ListOwner08097000;

typedef struct {
    void *object;
    u8 unknown_04[0xC];
} Entry08097000;

typedef struct {
    void *allocator;
    void *storage;
    ListOwner08097000 *context;
    void *list_storage;
    List08097000 *first;
    List08097000 *second;
    List08097000 *third;
    void *manager_entry;
    void *manager_storage;
    u8 unknown_24[0x370];
    Entry08097000 entries[2];
} State08097000;

typedef void (*BufferInitializer08097000)(void *destination, u32 size);

extern void *func_08007138(void *allocator, u32 size);
extern void *func_080070C8(void *storage, u32 size);
extern List08097000 *func_080C799C(void *allocator);
extern u32 func_08022080(u32 count);
extern ListOwner08097000 *func_08021A3C(void *allocator, u16 first,
                                     u16 second, u16 third, u16 fourth);
extern u32 func_0814913C(u8 count);
extern void func_0814914C(void *storage, s32 count);
extern void *func_0808F79C(void);
extern void *func_081493C0(void);
extern BufferInitializer08097000 g_callbacks_0836D4B8[];

/* Complete [0x08097000, 0x080970E8): 232 bytes, 93 instructions. */
State08097000 *func_08097000(void *allocator)
{
    State08097000 *state = func_08007138(allocator, sizeof(*state));
    void *heap;
    Entry08097000 *entry;
    s32 remaining;
    u32 manager_size;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->allocator = allocator;
    state->list_storage = func_08007138(allocator, 0x800);
    g_callbacks_0836D4B8[0](state->list_storage, 0x800);
    heap = func_080070C8(state->list_storage, 0x800);
    state->first = func_080C799C(heap);
    state->second = func_080C799C(heap);
    state->third = func_080C799C(heap);

    state->storage = func_08007138(state->allocator,
                                  func_08022080(0x34) + 0x400);
    g_callbacks_0836D4B8[0](state->storage, func_08022080(0x34) + 0x400);
    heap = func_080070C8(state->storage, func_08022080(0x34) + 0x400);
    state->context = func_08021A3C(heap, 0, 0x120, 0x1E0, 0x400);

    manager_size = func_0814913C(1);
    state->manager_storage = func_08007138(state->allocator, manager_size);
    func_0814914C(state->manager_storage, 1);
    entry = state->entries;
    for (remaining = 1; remaining >= 0; entry++, remaining--)
        entry->object = func_0808F79C();
    state->manager_entry = func_081493C0();
    return state;
}
