/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080997E8.c
 * Original SHA-256: d232f60c7da26e0dcf53e86734be277e92b809fb9e0efb214121a6c69e47636d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *owner;
    void *head;
    void *root;
} Collection;

typedef struct {
    u8 unknown_00[0x10];
    Collection *primary;
    u8 unknown_14[4];
    Collection *secondary;
} SceneCollections;

typedef struct {
    u8 unknown_00[0x24];
    s32 key;
    u8 unknown_28[0x58];
    SceneCollections *collections;
} SceneObject;

void *func_080C7BF4(Collection *collection, void *value);
void *func_080C7A74(Collection *collection, void *value);
void *func_080C7AB4(Collection *collection, void *value, s32 key);

void func_080997E8(SceneObject *object)
{
    if (func_080C7BF4(object->collections->primary, object) == 0) {
        func_080C7A74(object->collections->primary, object);
        func_080C7AB4(object->collections->primary, object, object->key);
    }

    if (func_080C7BF4(object->collections->secondary, object) == 0) {
        func_080C7A74(object->collections->secondary, object);
        func_080C7AB4(object->collections->secondary, object, object->key);
    }
}
