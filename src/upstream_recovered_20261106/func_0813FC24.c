/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0813FC24.c
 * Original SHA-256: 774fd29b7ee84e3c2a93c0ca288b1ed6a1d2dc324cb1242888fa505e85b9cfcd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* Complete target [0x0813FC24, 0x0813FC8C): 104 bytes, 34 instructions. */
typedef struct {
    u8 unknown_0000[0x8000];
    u32 packed_size;
    u8 unknown_8004[0xBD4];
    u8 colors[0x1E0];
} Graphics0813FC24;

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0C;
    u8 unknown_0D;
    u8 *tiles;
    u16 *destination;
} Display0813FC24;

typedef void (*BufferCopier0813FC24)(void *, const void *, u32);
extern Graphics0813FC24 *data_0200F3B0;
extern Display0813FC24 data_030008B0;
extern u8 data_06008000[];
extern const u16 data_08999EEC[];
extern const u8 data_089985C0[];
extern BufferCopier0813FC24 const data_0836D4BC[];
extern void func_08141868(const void *, void *, u32);
extern void func_0813FB0C(const u16 *, u16 *, u16, u8, u16);

void func_0813FC24(void)
{
    func_08141868(data_0200F3B0, data_06008000,
                  (data_0200F3B0->packed_size & 0xFFFFFF) >> 3);
    func_0813FB0C(data_08999EEC, data_030008B0.destination, 600, 30, 0);
    data_0836D4BC[0](data_0200F3B0->colors, data_089985C0, 480);
}
