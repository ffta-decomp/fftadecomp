/* Contributed by gg; original source and attribution follow. */
asm(".global data_083AD5F8\n.set data_083AD5F8,0x083AD5F8\n");
/* CoreRegion_000312F0
   entry 0x080312F0, 44 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0803131C.c
 * Original SHA-256: b9d24007a8d1fe098df74b91297288d4cb2d9d867445e9c3fcf0fe76dc3ac2ef
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

extern u8 data_02003CB0[];
extern const u8 data_083AD5F8[];
extern u8 data_06008A40[];
extern void func_0800543C(void *, const void *);
extern void func_0814186C(const void *, void *, u32);

/* 0x0803131C..0x08031348: 44 bytes, 13 instructions. */
void f_target(void)
{
    u8 *buffer = data_02003CB0;

    func_0800543C(buffer, data_083AD5F8);
    func_0814186C(buffer, data_06008A40, 0x630);
}
