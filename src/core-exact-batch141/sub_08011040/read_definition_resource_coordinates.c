#include "../../../src/task_tree_core.h"

typedef signed short s16;
/* Observed prefix of the established 64-byte definition-position object. */
struct DefinitionPositionPrefix {
    u8 unknown_00[29];
    u8 mode;
    s16 x;
    s16 y;
    s16 z;
};

u32 ReadDefinitionResourceCoordinates(const struct DefinitionPositionPrefix *object,
                                       u16 *x,u16 *y,u16 *z)
{
    *x = object->x;
    *y = object->y;
    *z = object->z;
    return object->mode;
}
