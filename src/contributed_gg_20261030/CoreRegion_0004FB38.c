/* Contributed by gg; original source and attribution follow. */
/* CoreRegion_0004FB38
   entry 0x0804FB38, 76 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08067528.c
 * Original SHA-256: a9a005612fe1f8120c114fd518d795d6ab2c4c2b7e1eb702c729500da04d2cfa
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

/* 0x08067528..0x08067574: 76 bytes. */
typedef struct {
    u8 unknown_00[0x424];
    u8 *entries[1];
} MenuData;

typedef struct {
    MenuData *data;
} MenuContext;

typedef struct {
    u8 unknown_00[2];
    u8 group;
    u8 unknown_03[13];
} EntryInfo;

extern const EntryInfo g_table_08521214[];
extern u8 func_080CB99C(u32 id);

u32 f_target(MenuContext *context, u32 index)
{
    u8 *entry = context->data->entries[index];
    const EntryInfo *info;
    u16 id;

    if (!entry)
        return 0;
    info = &g_table_08521214[*entry];
    if (info->group)
        id = 0x18A + info->group;
    else
        id = 0;
    return func_080CB99C(id) + 13;
}
