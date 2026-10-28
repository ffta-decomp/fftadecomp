/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809AC30.c
 * Original SHA-256: 11ba38bd11f243384dceaf48027a27bd1b77b2225dd10d8ae6d85901c8472399
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *entity;
    u8 unknown_04[0x28];
    u16 flags;
    u8 unknown_2e[0x0e];
    void *handle;
} EntityOwner;

typedef struct {
    EntityOwner *owner;
} OwnerContext;

extern u8 func_080C8240(void *entity);
extern void func_081492A8(void *handle);

/* 0x0809AC30..0x0809AC6C: 60 bytes. */
s32 func_0809AC30(EntityOwner *owner, const OwnerContext *context)
{
    if (context->owner != owner) {
        if ((owner->flags & 1)
            || func_080C8240(owner->entity)
                != func_080C8240(context->owner->entity))
            func_081492A8(owner->handle);
    }
    return 1;
}
