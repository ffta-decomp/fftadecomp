/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08031624.c
 * Original SHA-256: 5bc5a19248ac816319808ec55b85e5a013d694ffb2834eb24e9885f2364ce9c6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target: 52 bytes / 20 instructions, 0x08031624..0x08031658.
 * Wait for HBlank, then write the buffered blend control value. */
typedef unsigned short u16;

struct DisplayStatus {
    u16 status;
};

extern struct DisplayStatus data_04000004;
extern u16 data_030027F0;

void func_08031624(void)
{
    /* plausible: DISPSTAT at 0x04000004 changes as the display enters HBlank. */
    volatile struct DisplayStatus *display = &data_04000004;
    u16 hblank = display->status & 2;
    u16 *buffered_control = &data_030027F0;
    while (hblank == 0)
        hblank = display->status & 2;
    /* plausible: BLDCNT at 0x04000050 is a hardware display control register. */
    *(volatile u16 *)0x04000050 = *buffered_control;
}
