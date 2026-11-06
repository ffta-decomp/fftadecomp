/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08088FEC.c
 * Original SHA-256: e8a57e7b0689d04bbf1ecd70793b0a80db82e17d1a88c4d30cbcab458a0e98b3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 x;
    u8 y;
    u8 field_03;
    u8 field_04;
    u8 field_05;
    u8 field_06;
    u8 field_07;
} NavigationEntry08088FEC;

typedef struct {
    u32 active : 1;
    u32 enabled : 1;
    u32 visible : 1;
    u32 palette : 4;
    u32 unknown_07 : 1;
    u32 mode : 2;
    u32 variant : 1;
    u32 style : 2;
    u32 pending : 1;
    u32 reserved : 4;
    u32 unknown_12 : 14;
    NavigationEntry08088FEC entries[32];
    u8 count;
    u8 option;
    u8 selection;
    u8 unknown_107;
    u16 timer;
    u16 delay;
    u8 counter;
    u8 graphic;
    u8 state;
    u8 unknown_10F;
    u8 width;
    u8 height;
} DisplayObject08088FEC;

typedef struct {
    u32 unknown_00;
    u8 *surface;
} RenderState08088FEC;

extern RenderState08088FEC data_03000E30;
extern void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);
extern void func_08141540(u16 sound);

/* Complete target: [0x08088FEC, 0x080891BC), 464 bytes.
 * 70b5041c09040a0c617821204042084060700b4821180878ff2817d02078c007
 * 002813d107484068097888235b00e2181278054d63191b78c3f7b0fbc0e00000
 * 0d010000300e0003110100008021101c084000282ed0144826183078c0002018
 * c57a281c0840002804d020784007002800dba5e06d20b8f06dfa307883225200
 * a11808707f2028403070e90061184a7988235b00e01802708879044d62191070
 * c8790349621878e005010000110100000701000040201040002811d0074aa618
 * 3078c0002018857a281c084000284bd020784007002847db72e0000005010000
 * 1020104000282dd0134826183078c0002018457a281c0840002803d020788007
 * 00285dda6d20b8f025fa307883225200a11808707f2028403070e90061184a79
 * 88235b00e01802708879044d62191070c8790349621830e00501000011010000
 * 070100002020104000282bd0144aa6183078c0002018057a281c0840002803d0
 * 2078800700282bda6d20b8f0f3f9307883235b00e11808707f2028403070e900
 * 61184a7988256d006019027088790b33e2181070c879093d62191070012010e0
 * 05010000084960180578e8002018427988235b00e1180a708079044d62191070
 * 002070bc02bc08470501000011010000
 */
u32 func_08088FEC(DisplayObject08088FEC *object, u16 input)
{
    u8 next;

    object->pending = 0;
    if (object->graphic != 0xFF && !object->active) {
        func_0804C788(data_03000E30.surface, object->graphic,
                     object->width, object->height);
        return 0;
    }
    if (input & 0x80) {
        u8 *option = &object->option;
        next = object->entries[*option].field_07;
        if ((next & 0x80) && !object->visible)
            return 0;
        func_08141540(0x6D);
        object->selection = *option;
        *option = next & 0x7F;
        object->width = object->entries[next].x;
        object->height = object->entries[next].y;
        object->unknown_107 = object->entries[next].field_03;
        return 1;
    } else if (input & 0x40) {
        u8 *option = &object->option;
        next = object->entries[*option].field_06;
        if (!(next & 0x80) || object->visible) {
            func_08141540(0x6D);
            object->selection = *option;
            *option = next & 0x7F;
            object->width = object->entries[next].x;
            object->height = object->entries[next].y;
            object->unknown_107 = object->entries[next].field_03;
            return 1;
        }
        return 0;
    } else if (input & 0x10) {
        u8 *option = &object->option;
        next = object->entries[*option].field_05;
        if ((next & 0x80) && !object->enabled)
            return 0;
        func_08141540(0x6D);
        object->selection = *option;
        *option = next & 0x7F;
        object->width = object->entries[next].x;
        object->height = object->entries[next].y;
        object->unknown_107 = object->entries[next].field_03;
        return 1;
    } else if (input & 0x20) {
        u8 *option = &object->option;
        next = object->entries[*option].field_04;
        if ((next & 0x80) && !object->enabled)
            return 0;
        func_08141540(0x6D);
        object->selection = *option;
        *option = next & 0x7F;
        object->width = object->entries[next].x;
        object->height = object->entries[next].y;
        object->unknown_107 = object->entries[next].field_03;
        return 1;
    }
    {
        u8 *entry;

        next = object->option;
        entry = (u8 *)object + next * 8;

        object->width = entry[5];
        object->height = entry[6];
    }
    return 0;
}
