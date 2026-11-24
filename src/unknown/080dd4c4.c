#include "engine/tasks/task_tree.h"
struct DefinitionPointerCell { void *object; };
void *ReadOptionalDefinitionObjectCell(const struct DefinitionPointerCell *cell)
{
    void *object = 0;
    if (cell != 0)
        object = cell->object;
    return object;
}
