/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804082C.c
 * Original SHA-256: fdbd89a21dc89d2381d180424be7aea94e13a9fef96e06cfeeaa2b49a8642a20
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u16 value_04;
    u8 unknown_06[6];
    u16 value_0c;
    u16 value_0e;
    u8 unknown_10[4];
} Choice0804082C;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
    u8 unknown_0a[14];
    Choice0804082C *choices;
} ChoiceOwner0804082C;

typedef struct {
    u8 unknown_00[0x20];
} List0804082C;

typedef struct {
    u8 unknown_00[0x11];
    u8 current;
    u8 unknown_12[2];
} ListOptions0804082C;

typedef struct {
    u32 words[5];
} SavedChoice0804082C;

typedef struct {
    u8 unknown_00[0x38];
    u16 selected;
    u8 command;
    u8 unknown_3b[3];
    u16 action;
    u16 value_40;
    u16 unknown_42;
    u16 value_44;
    u16 value_46;
    ChoiceOwner0804082C *owner;
    u8 unknown_4c[0x2c];
    List0804082C list;
    ListOptions0804082C options;
    SavedChoice0804082C saved;
    u8 unknown_c0[8];
    ChoiceOwner0804082C *selection_owner;
} Channel0804082C;

typedef struct {
    u8 unknown_00[0x4a0];
    SavedChoice0804082C saved;
    u8 result;
    u8 unknown_4b5[0x49f];
    Channel0804082C channels[1];
} State0804082C;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input0804082C;

extern Input0804082C data_03000000;
extern State0804082C *g_state_03002810;

#define CHANNEL_OPTIONS(n) ((ListOptions0804082C *)((n) * sizeof(Channel0804082C) + (u32)g_state_03002810 + 0x9ec))

u16 func_08017B68(List0804082C *list, s32 index);
u16 func_08017B50(List0804082C *list);
void func_08017AF4(List0804082C *list, s32 index, u8 mode);
u8 func_08017A90(List0804082C *list, u16 direction);
u8 func_080356A0(s32 channel, u8 mode);
void func_08085374(void);
void func_08141540(u32 sound);
void func_080406D4(s32 channel, u32 direction, s32 index, u32 change_page);
void func_080407A4(s32 channel);

u32 func_0804082C(s32 channel, u16 mask)
{
    u16 pressed = mask & data_03000000.pressed;
    s32 current;

    if (pressed == 4) {
        s8 selected = func_08017B68(&g_state_03002810->channels[channel].list,
            (s8)CHANNEL_OPTIONS(channel)->current);
        g_state_03002810->channels[channel].selected =
            g_state_03002810->channels[channel].owner->choices[selected].value_0c;
        g_state_03002810->saved = g_state_03002810->channels[channel].saved;
        g_state_03002810->result = func_080356A0(channel, 0);
        g_state_03002810->channels[channel].command = 0;
        return 9;
    }

    if (pressed & 3) {
        ChoiceOwner0804082C *owner = g_state_03002810->channels[channel].selection_owner;
        ListOptions0804082C *options = CHANNEL_OPTIONS(channel);
        u16 selected = func_08017B68(&g_state_03002810->channels[channel].list,
            (s8)options->current);
        g_state_03002810->channels[channel].action = (pressed & 1) ? 1 : 2;
        g_state_03002810->channels[channel].value_40 = owner->choices[selected].value_04;
        g_state_03002810->channels[channel].value_44 = owner->choices[selected].value_0e;
        g_state_03002810->channels[channel].value_46 =
            *(u16 *)((u8 *)&owner->choices[selected] + 0xf);
    }

    if (data_03000000.repeated & 0x80) {
        s8 next;

        g_state_03002810->channels[channel].action = 0x80;
        func_08085374();
        current = CHANNEL_OPTIONS(channel)->current;
        next = (s8)(current + 1);
        if (next < func_08017B50(&g_state_03002810->channels[channel].list)) {
            func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->channels[channel].list, (s8)current, 0xc);
            func_080406D4(channel, 0x80, next, 0);
            func_080407A4(channel);
        } else if (g_state_03002810->channels[channel].owner->flags & 1) {
            s32 wrapped = (s8)current;
            if (wrapped != 0)
                func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->channels[channel].list, wrapped, 0xc);
            func_080406D4(channel, 0x80, 0, 0);
            func_080407A4(channel);
        } else if (func_08017A90(&g_state_03002810->channels[channel].list, 0x80)) {
            func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->channels[channel].list, (s8)current, 0xc);
            func_080406D4(channel, 0x80, next, 1);
            func_080407A4(channel);
            return 4;
        }
    } else if (data_03000000.repeated & 0x40) {
        s8 previous;

        g_state_03002810->channels[channel].action = 0x40;
        func_08085374();
        current = CHANNEL_OPTIONS(channel)->current;
        previous = current - 1;
        if (previous >= 0) {
            func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->channels[channel].list, (s8)current, 0xc);
            func_080406D4(channel, 0x40, previous, 0);
            func_080407A4(channel);
        } else if (g_state_03002810->channels[channel].owner->flags & 1) {
            previous = func_08017B50(&g_state_03002810->channels[channel].list) - 1;
            if (previous != (s8)current)
                func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->channels[channel].list, (s8)current, 0xc);
            func_080406D4(channel, 0x80, previous, 0);
            func_080407A4(channel);
        } else if (func_08017A90(&g_state_03002810->channels[channel].list, 0x40)) {
            func_08141540(0x6d);
            func_08017AF4(&g_state_03002810->channels[channel].list, (s8)current, 0xc);
            func_080406D4(channel, 0x40, previous, 1);
            func_080407A4(channel);
            return 4;
        }
    }
    return 3;
}
