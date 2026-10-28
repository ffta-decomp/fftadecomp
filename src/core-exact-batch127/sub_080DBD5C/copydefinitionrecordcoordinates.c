#include "../../../src/task_tree_core.h"

typedef signed short s16;

void CopyDefinitionRecordCoordinates(const u16 *record, u16 *x, u16 *y, u16 *z)
{
    *x = record[4];
    *y = record[5];
    *z = record[6];
}
