/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806514C.c
 * Original SHA-256: f711df23c8b0109a9053e7dfcf3f5634b4f97a985554f2d6008671fa68777f31
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x424];
    void *entries[0];
} PointerContainer;

typedef struct {
    PointerContainer *container;
    u8 unknown_04[2];
    u16 count;
    u8 kind;
} TaskPayload;

void *func_08005BFC(void *task);

void *func_0806514C(void *task)
{
    const TaskPayload *payload = func_08005BFC(task);
    u16 index = payload->count - 1;

    switch (payload->kind) {
    case 7:
        return payload->container->entries[(s16)index];
    default:
        return 0;
    }
}
