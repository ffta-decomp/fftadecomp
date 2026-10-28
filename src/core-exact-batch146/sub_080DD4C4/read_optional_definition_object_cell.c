#include "../../../src/task_tree_core.h"
struct DefinitionPointerCell { void *object; };
void *ReadOptionalDefinitionObjectCell(const struct DefinitionPointerCell *cell)
{
    void *object = 0;
    if (cell != 0)
        object = cell->object;
    return object;
}
