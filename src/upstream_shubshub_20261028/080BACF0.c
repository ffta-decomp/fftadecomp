/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BACF0.c
 * Original SHA-256: 0cc08251e297b975c50e632167886ad0bb688d9d9d362501859e80d06c3dcb78
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x80];
    void *scene;
} Subject;

typedef struct MapEntry MapEntry;

typedef struct {
    Subject *subject;
    MapEntry *entry;
    void *details;
    u8 category;
    u8 first;
    u8 second;
    u8 third;
    u16 identifier;
    u8 unknown_12[0xE];
    u16 current;
    u16 count;
    u16 fields[34];
} FieldContext;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer g_callbacks_0836D4B8[];
extern void func_080C156C(void *scene, Subject *subject, MapEntry *entry,
                         u8 *first, u8 *second, u8 *third);
extern u8 func_080C95A8(u16 index);

static inline void commit_field(FieldContext *context)
{
    context->fields[context->count++] = context->current;
}

/* 0x080BACF0..0x080BAEE8: 504 bytes; initialize the mode-specific field list. */
void func_080BACF0(FieldContext *context, Subject *subject, MapEntry *entry,
                  void *details, u8 mode)
{
    g_callbacks_0836D4B8[0](context, sizeof(*context));
    context->subject = subject;
    context->entry = entry;
    context->details = details;
    func_080C156C(subject->scene, subject, entry, &context->first,
                  &context->second, &context->third);
    context->category = 12;
    context->identifier = 34;
    context->current = 26;
    if (mode == 3) {
        context->category = 13;
        context->identifier = 35;
        if (func_080C95A8(13))
            context->identifier = 0x188;
    }
    if (mode != 1) {
        commit_field(context);
        context->current = 23;
        commit_field(context);
        context->current = 17;
        commit_field(context);
        context->current = 18;
        commit_field(context);
        context->current = 14;
        commit_field(context);
        context->current = 21;
        commit_field(context);
        context->current = 16;
        commit_field(context);
        context->current = 19;
        commit_field(context);
        context->current = 7;
        if (mode == 3) {
            commit_field(context);
            context->current = 10;
        }
        commit_field(context);
        context->current = 25;
        commit_field(context);
        context->current = 5;
    }
    if (mode != 3) {
        commit_field(context);
        context->current = 7;
        commit_field(context);
        context->current = 10;
        commit_field(context);
        context->current = 2;
        commit_field(context);
        context->current = 25;
        commit_field(context);
        context->current = 5;
    }
    commit_field(context);
    context->current = 12;
    commit_field(context);
    context->current = 3;
    commit_field(context);
    context->current = 0;
}
