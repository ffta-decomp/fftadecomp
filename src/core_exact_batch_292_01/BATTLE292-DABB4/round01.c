#include "../../task_tree_core.h"

extern void *GetTaskPayload(TaskNode *node) __asm__("SceneHelper_08005BFC");
extern u32 ReadDefinitionObjectDataWord(const void *object);
__asm__(
    ".global ReadDefinitionObjectDataWord\n"
    ".thumb_set ReadDefinitionObjectDataWord,0x0800c615\n"
);

u32 RemainingBand43_000DABB4(TaskNode *node)
{
    const u32 *payload = (const u32 *)GetTaskPayload(node);
    return ReadDefinitionObjectDataWord((const void *)payload[1]);
}
