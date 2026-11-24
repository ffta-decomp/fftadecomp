/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808286C.c
 * Original SHA-256: 286eb6d56905b219640e999503e5481d4dd8b67f518cc86278b534f5ad7c91f1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct Menu {
    u8 unknown_00[0x1A];
    u16 position;
    u8 unknown_1C[4];
};

struct Selector {
    u8 unknown_00[0x11];
    s8 selection;
    u8 unknown_12[0x22];
};

struct Entry {
    u8 unknown_00[0x78];
    struct Menu menu;
    struct Selector selector;
};

struct State {
    u8 unknown_00[0x2C88];
    struct Entry entries[1];
};

extern struct State *data_03002818;
extern u16 func_08017B50(struct Menu *menu);
extern u8 func_08017A90(struct Menu *menu, int flag);
extern void func_08017FB0(struct Selector *selector, u8 selection);

static inline s8 selector_selection(struct Selector *selector)
{
    return selector->selection;
}

static inline void advance_menu(struct Menu *menu)
{
    if (func_08017A90(menu, 0x80))
        menu->position++;
}

void func_0808286C(int index, u16 count)
{
    u16 iteration;

    for (iteration = 0; iteration < count; iteration++) {
        struct State **state = &data_03002818;
        s8 next = selector_selection(&(*state)->entries[index].selector) + 1;

        if (next < func_08017B50(&(*state)->entries[index].menu)) {
            func_08017FB0(&(*state)->entries[index].selector, next);
        } else if (func_08017A90(&(*state)->entries[index].menu, 0x80)) {
            advance_menu(&(*state)->entries[index].menu);
        }
    }
}
