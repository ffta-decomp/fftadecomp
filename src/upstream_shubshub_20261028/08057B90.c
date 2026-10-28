/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08057B90.c
 * Original SHA-256: e22a00bc219d90b19ae5b0f86e3bd875fcdacf763657ce088c862de4403caab2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern void func_08000D48(u8 channel, const void *source, void *destination, u32 control);

/* Complete target: [0x08057B90, 0x08057BEC), 92 bytes. */
void func_08057B90(u8 channel, u16 *buffer, u8 split, u16 first, u16 second)
{
    u8 row;

    for (row = 0; row < split; row++)
        buffer[row] = first;
    for (row = split; row < 160; row++)
        buffer[row] = second;
    func_08000D48(channel, buffer, (void *)0x04000050, 0x20400001);
}
