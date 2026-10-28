/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08131048.c
 * Original SHA-256: 314564f2aea24bf24642f60dec2a5ece9e9057799d697e59efe4231025d9bf3c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *first;
    void *second;
    u8 unknown_08[0x28];
    const u8 *command;
} CommandContext;

typedef u8 (*CommandHandler)(CommandContext *context);

extern CommandHandler const data_083A8604[];

/* 08131048..0813107C: 52 bytes. */
u8 func_08131048(CommandContext *context)
{
    if (context->first == 0 || context->second == 0)
        return 0;

    return data_083A8604[*context->command](context);
}
