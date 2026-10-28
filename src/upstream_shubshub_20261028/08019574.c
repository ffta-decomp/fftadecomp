/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08019574.c
 * Original SHA-256: 807ae0968449791892ffc63c93bf4c96389dfa24b75c0cd25a36d0ee0182245b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 identifier : 10;
    u16 unknown_0A : 6;
    u8 unknown_02[10];
    u16 options[2];
} Unit;

typedef struct {
    const Unit *unit;
} MenuState;

extern MenuState g_state_020020D0;
extern const char *const g_table_085567F0[];
extern const char *const g_table_08526680[];
extern u32 func_080CE4DC(u16 identifier, u32 selector);
extern u8 func_080C9540(u16 index);
extern const char *func_080CB4E0(u32 identifier);
extern void func_08018C24(void *display, const char *text);

/* 08019574..080195F2: 126 bytes, 49 instructions. */
u32 func_08019574(void *display, u8 action)
{
    const Unit *unit = g_state_020020D0.unit;
    u32 index;
    u32 selector;
    const char *text;

    if (action == 0x84) {
        index = 0;
        selector = 0x3F;
    } else {
        index = 1;
        selector = 0x40;
    }

    if (func_080CE4DC(unit->identifier, selector)) {
        text = g_table_085567F0[38];
    } else {
        u8 identifier = unit->options[index];

        if (!identifier || !func_080C9540(0x207))
            text = g_table_08526680[0];
        else
            text = func_080CB4E0(identifier);
    }
    func_08018C24(display, text);
    return 0;
}
