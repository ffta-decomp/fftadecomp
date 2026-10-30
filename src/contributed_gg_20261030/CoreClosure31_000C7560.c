/* Contributed by gg; original source and attribution follow. */
asm(".global f_080C69C8\n.thumb_set f_080C69C8,0x080C69C9\n");
/* CoreClosure31_000C7560
   entry 0x080C7560, 146 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C73D8.c
 * Original SHA-256: 0b662a952a081218afffb0c3601b82f82fb76834750f17e28d68367ffe40d0c6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* ---- inlined ffta.h ---- */
#ifndef FFTA_SHIM_H
#define FFTA_SHIM_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
#endif

typedef struct {
    u8 unknown_00[0x000000AC];
    u8 count;
    u8 unknown_AD;
    u8 flags;
} InputState;

typedef struct {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03[0x11D];
    u16 busy;
    u16 ticks;
} SystemState;

extern InputState data_02015738;
extern SystemState data_030028A0;
extern s32 func_08004D68(void);
extern u8 f_080C69C8(void *context);

static inline u8 input_blocked(void)
{
    if (data_02015738.flags & 0x00000040) {
        if (data_02015738.flags & 0x00000080)
            return func_08004D68() != 1;
        return 0;
    }
    if (((data_02015738.flags & 0x00000020) || data_02015738.count > 13) &&
        (data_030028A0.busy != 0 ||
         (data_030028A0.mode != 3 && data_030028A0.ticks > 16)))
        return 1;
    if (data_02015738.flags & 8)
        return 1;
    return 0;
}

u8 f_target(void *context)
{
    u8 result;

    if (!input_blocked())
        result = f_080C69C8(context);
    else
        result = 2;
    return result;
}
