/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011644.c
 * Original SHA-256: e1b1b70f67beb9755a26a64b4f85fa44b673833319fa4810b4c6b4f4da67dbba
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08011644..0x08011690: 76 bytes / 29 instructions. */
struct Entry08011644;

struct Snapshot08011644 {
    struct Entry08011644 **source;
    struct Entry08011644 *value;
};

extern struct Entry08011644 *data_02009178;
extern struct Entry08011644 *data_0200917C;
extern struct Entry08011644 *data_02009174;
extern struct Entry08011644 *data_02009180;

void func_08011644(struct Snapshot08011644 *snapshot, u8 selector)
{
    struct Entry08011644 **source;

    switch (selector) {
    case 0:
        source = &data_02009178;
        break;
    case 1:
        source = &data_0200917C;
        break;
    case 2:
        source = &data_02009174;
        break;
    case 3:
        source = &data_02009180;
        break;
    default:
        return;
    }
    snapshot->source = source;
    snapshot->value = *source;
}
