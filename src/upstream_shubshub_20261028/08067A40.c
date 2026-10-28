/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08067A40.c
 * Original SHA-256: 3b5812e4473edce91c2a7dfd5b7d34ba7d302df77de431bf33e5c676c456c60d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08067A40, 0x08067B80): 320 bytes, 144 instructions. */
typedef struct {
    u8 unknown_00[0x11];
    u8 current;
} Selector;

typedef struct {
    u8 unknown_00[4];
    u16 flags;
    u8 unknown_06[2];
    u8 kind;
    u8 unknown_09;
    u8 count;
    u8 unknown_0b[5];
    void (*callback)(void);
    u8 unknown_14[0x5c];
    Selector selector;
} SelectionState;

extern u8 data_03000000[];
extern u8 func_08067994(SelectionState *, u16);
extern s8 func_08067D6C(SelectionState *, u16);
extern void func_08067E9C(SelectionState *, u8);
extern void func_08141540(s32);
extern void func_080023D0(void *);
extern void func_08017FB0(Selector *, u8);
extern void func_08067E48(SelectionState *, u8, s32);
extern void func_08066C28(SelectionState *);

s32 func_08067A40(SelectionState *state, u16 input, u16 buttons, u16 modifiers)
{
    Selector *selector = &state->selector;
    s8 current = 0;
    s32 changed = 0;

    if ((state->flags & 4) && func_08067994(state, input))
        return 1;

    if (buttons & 0x80) {
        if ((modifiers & 0x200) && state->kind != 1 && state->kind != 2)
            return func_08067D6C(state, 0x80);
        current = selector->current;
        if (state->count > 1) {
            func_08067E9C(state, current);
            func_08141540(0x6d);
        }
        func_080023D0(data_03000000);
        ++current;
        if (current >= state->count)
            current = 0;
        func_08017FB0(selector, current);
        changed = 1;
    } else if (buttons & 0x40) {
        if ((modifiers & 0x200) && state->kind != 1 && state->kind != 2)
            return func_08067D6C(state, 0x40);
        current = selector->current;
        if (state->count > 1) {
            func_08067E9C(state, current);
            func_08141540(0x6d);
        }
        func_080023D0(data_03000000);
        --current;
        if (current < 0)
            current = state->count - 1;
        changed = 1;
    }
    if (changed) {
        func_08017FB0(selector, current);
        func_08067E48(state, current, 0);
        if (state->callback)
            func_08066C28(state);
    }
    return 0;
}
