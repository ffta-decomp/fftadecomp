/* Contributed by gg; original source and attribution follow. */
/* CoreClosure31_000D7150
   entry 0x080D7150, 88 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D7080.c
 * Original SHA-256: 1eae4e0911493b4c6de7c331dd88aec9b61988af3f2564fced407c758072942f
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

/* 0x080D7080..0x080D70D8: 88 bytes, 44 instructions. */
void f_target(const u8 *source, u16 count, u8 *destination, u8 palette)
{
    u8 high_palette = palette << 4;
    u16 i;

    for (i = 0; i < count; i++) {
        u32 bits = source[i];
        u16 pixel;

        for (pixel = 0; pixel < 2; pixel++) {
            *destination = bits & 15;
            if (*destination) {
                *destination |= high_palette;
            }
            destination++;
            bits >>= 4;
        }
    }
}
