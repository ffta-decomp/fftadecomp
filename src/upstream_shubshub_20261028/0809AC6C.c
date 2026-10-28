/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809AC6C.c
 * Original SHA-256: 13a9fb7528f3f1c439b75928481b06105cb3c4bc3bfc887a95f6a060977a5165
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct Collection Collection;

typedef struct {
    s32 key;
    void *value;
} CollectionEntry;

typedef struct {
    u8 unknown_00[0x24];
    s32 key;
} SceneObject;

CollectionEntry *func_080C7C14(Collection *collection, SceneObject *object);
void func_080C7C40(CollectionEntry *entry, void *value, s32 key);

s32 func_0809AC6C(SceneObject *object, Collection *collection)
{
    CollectionEntry *entry = func_080C7C14(collection, object);

    func_080C7C40(entry, object, object->key);
    return 1;
}
