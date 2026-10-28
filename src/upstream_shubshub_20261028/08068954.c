/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08068954.c
 * Original SHA-256: de6cc0f4e9ea8e14f4bf714f6510ed94b936e61b0a090c843ca2874e47dcfe02
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08068954..0x08068998: 68 bytes. */
typedef struct {
    u8 unknown_00[0x84];
    u8 control[1];
} MenuOwner;

typedef struct {
    u8 unknown_00[8];
    u8 selection;
    u8 unknown_09[7];
} MenuSettings;

typedef struct {
    u32 unknown_00;
    MenuOwner *owner;
    u8 handle;
    u8 flags;
    u8 unknown_0a[0x0E];
    MenuSettings settings;
    u8 update_state[1];
} MenuContext;

typedef void (*MenuCallback)(MenuContext *context);

extern void func_08017E28(void *control);
extern void func_080686F4(MenuContext *context);
extern void func_08017508(void *state, u8 selection);
extern void func_08066EA0(MenuContext *context);
extern u8 func_080098F4(MenuCallback callback, MenuContext *context);

void func_08068954(MenuContext *context)
{
    MenuSettings *settings = &context->settings;
    void *control = context->owner->control;

    context->flags &= ~5;
    if (control)
        func_08017E28(control);
    func_080686F4(context);
    func_08017508(context->update_state, settings->selection);
    context->handle = func_080098F4(func_08066EA0, context);
}
