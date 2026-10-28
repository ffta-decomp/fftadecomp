/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CA0F8.c
 * Original SHA-256: 8ecaaaaa02670bcc3d9c0d78bd03f1480eee0b6966e8556f7395577f26bea3f0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080CA0F8..0x080CA150: 88 bytes, 39 instructions, including pools. */
typedef struct {
    u32 key;
    u8 unknown_04[0x102];
    u8 table;
} KeyedObject;

extern const u32 g_table_085680DC[];
extern const u32 g_table_085516D0[];

u32 func_080CA0F8(const KeyedObject *object)
{
    u32 i;
    switch (object->table) {
    case 0:
        for (i = 0; i < 725; i++) {
            if (g_table_085680DC[i] == object->key) {
                return i;
            }
        }
        /* An unmatched primary entry also searches the secondary table. */
    case 1:
        for (i = 0; i < 107; i++) {
            if (g_table_085516D0[i] == object->key) {
                return i;
            }
        }
        break;
    }
    return 0;
}
