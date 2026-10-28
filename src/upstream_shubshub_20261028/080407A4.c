/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080407A4.c
 * Original SHA-256: c49cc485f0aea60bd9878887069dbadf8f9d6496aeefbe691cf193494c5f6e1c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete target: [0x080407A4, 0x0804082C), 136 bytes. */
typedef struct {
    u16 unknown_00;
    u16 flags;
    u8 unknown_04[10];
    u8 size_index;
    u8 mode;
    u8 unknown_10[4];
} MenuChoice;

typedef struct {
    u8 unknown_00[0x18];
    MenuChoice *choices;
} ChoiceOwner;

typedef struct {
    u8 unknown_00[0x18];
    u16 count;
    u16 first;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 current;
    u8 unknown_12[2];
} ListOptions;

typedef struct {
    u8 unknown_00[0x78];
    MenuList list;
    ListOptions options;
    u8 unknown_AC[0x1C];
    ChoiceOwner *selection_owner;
} MenuChannel;

typedef struct {
    u8 unknown_00[6];
    u16 width;
    u16 height;
} MenuPanel;

typedef struct {
    u32 unknown_00;
    MenuPanel *panel;
    u8 unknown_08[0x686 - 8];
    u8 mode;
    u8 unknown_687[0x954 - 0x687];
    MenuChannel channels[1];
} MenuState;

extern MenuState *g_state_03002810;
extern u16 func_08017B68(MenuList *state, u32 index);
extern u32 func_08035A20(u8 index);
extern u32 func_08035A44(u8 index);

void func_080407A4(s32 channel)
{
    ChoiceOwner *owner = g_state_03002810->channels[channel].selection_owner;
    ListOptions *options = (ListOptions *)(channel * sizeof(MenuChannel)
        + (u32)g_state_03002810 + 0x9EC);
    u16 selected = func_08017B68(&g_state_03002810->channels[channel].list,
        (s8)options->current);

    if (!(owner->choices[selected].flags & 1)) {
        u8 size = owner->choices[selected].size_index - 1;

        g_state_03002810->panel->width = func_08035A20(size) + 6;
        g_state_03002810->panel->height = func_08035A44(size) + 4;
        g_state_03002810->mode = owner->choices[selected].mode;
    }
}
