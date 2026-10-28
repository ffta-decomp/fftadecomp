/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08060468.c
 * Original SHA-256: 0427e672c151a0e64ed7f6c7b8cda65bcd3a9b9f9a75ba04908942328e8ac116
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 type;
    u8 flags;
    u16 id;
} MenuRecord;

typedef struct {
    u8 unknown_00[0x1A];
    u8 first_count;
    u8 second_count;
    u8 unknown_1C[4];
    MenuRecord *records[1];
} MenuState;

extern MenuState *data_0200F44C;

/* Complete target: [0x08060468, 0x08060542), 218 bytes, 104 instructions. */
s16 func_08060468(const u8 *mode, s16 selection, u8 *confirmed)
{
    switch (*mode)
    {
    case 5:
        {
            u32 count;
            MenuRecord *selected;
            u32 i;
            u8 occupied;

            if (selection > 1)
                return 2;
            count = data_0200F44C->second_count - 2;
            selected = data_0200F44C->records[count + selection];
            switch (count)
            {
            case 0:
                return -1;
            case 1:
            case 2:
                i = 0;
                occupied = 0;
                for (; i < count; i++)
                {
                    MenuRecord *record = data_0200F44C->records[i];
                    if (record && ((record->id && selected != record) ||
                                   (record->flags & 1)))
                        occupied++;
                }
                if (occupied == count)
                    return -1;
                break;
            }
        }
        break;
    case 6:
        {
            MenuState *state = data_0200F44C;
            MenuRecord *selected = state->records[selection];
            u16 id = selected->id;

            if (id)
            {
                s32 otherIndex = state->first_count - 2;
                MenuRecord *other;

                otherIndex += state->second_count;
                other = state->records[otherIndex];
                if (!other || id != other->id || selected->type != other->type)
                    return -2;
                *confirmed = 1;
                return selection;
            }
        }
        break;
    }
    return selection;
}
