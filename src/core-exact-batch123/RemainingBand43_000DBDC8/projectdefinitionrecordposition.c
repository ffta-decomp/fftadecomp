#include "../../../src/task_tree_core.h"

typedef signed char s8;
typedef signed short s16;

extern void ProjectDefinitionCoordinates(s16,s16,s16,s16 *,s16 *);
void ProjectDefinitionRecordPosition(const void *record, s16 *screen_x, s16 *screen_y)
{
    s16 x = ((const s16 *)record)[4];
    s16 y = ((const s16 *)record)[5];
    s16 z = ((const s16 *)record)[6];
    ProjectDefinitionCoordinates(x, y, z, screen_x, screen_y);
}

asm(".global ProjectDefinitionCoordinates\n.thumb_set ProjectDefinitionCoordinates,0x801c985\n");
