/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080870E0.c
 * Original SHA-256: b9de362675ea6cb81e4ec9495413101e464f7b4026d27136028e6f8f0c801834
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 enabled;
    u8 unknown_11[2];
    u8 id;
    u8 unknown_14[8];
} SearchRecord;

typedef struct {
    u8 unknown_0000[0x1270];
    s32 count;
    SearchRecord records[1];
} SearchContext;

extern SearchContext *data_03002818;

s32 func_080870E0(u8 id, u32 include_disabled)
{
    s32 index;

    for (index = 0; index < data_03002818->count; index++) {
        if (include_disabled) {
            if (data_03002818->records[index].id == id)
                return index;
        } else {
            if (data_03002818->records[index].id == id
                && data_03002818->records[index].enabled == 1)
                return index;
        }
    }
    return -1;
}
