/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081312EC.c
 * Original SHA-256: e4d8395ff23cda5bb757a69213cbf8c95d81d8315c218feeacfe766edd893fe5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct ActionConfig {
    u8 unknown;
    u8 mode;
};

struct ActionContext {
    void *first;
    void *second;
    u8 unknown[0x28];
    struct ActionConfig *config;
};

extern u32 func_0812DB5C(void *first, void *second, u8 mode);

u8 func_081312EC(const struct ActionContext *context)
{
    if (func_0812DB5C(context->first, context->second,
                      context->config->mode) == 0)
        return 0;
    return 100;
}
