/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801075C.c
 * Original SHA-256: e207de1b764ad49d35a189ab71d482fb465d58c8116961859c3ca89dba91a36f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct FrameTable0801075C {
    u8 unknown_00[8];
    const u8 *data;
    u16 current;
    u8 unknown_0e[6];
    u16 format;
};

static inline u16 read_le16_0801075C(const u8 *data)
{
    u32 low = data[0];

    return (data[1] << 8) | low;
}

/* 0x0801075C..0x080107D4: 120 bytes. */
u16 func_0801075C(const struct FrameTable0801075C *table, u16 index, u16 format)
{
    u16 count = index;

    if ((s16)index == -1)
        count = table->current;
    if (format == 0)
        format = table->format;
    if (format & 0x4000) {
        s32 selected = (s16)count;
        const u8 *data = table->data;

        data += ((const u16 *)data)[selected];
        count = read_le16_0801075C(data);
    } else {
        s32 selected = (s16)count;
        const u8 *data = table->data;
        s32 last;

        data += ((const u32 *)data)[selected];
        count = read_le16_0801075C(data);
        last = count - 1;
        data += last * 4;
        if (read_le16_0801075C(data + 4) == 999)
            count = last;
    }
    return count;
}
