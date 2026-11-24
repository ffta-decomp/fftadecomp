struct TaskNode;
/* Real task callbacks receive the payload immediately after the 24-byte node. */
void *GetTaskPayload(struct TaskNode *node)
    __asm__("SceneActionDependency_00005BFC");
void *GetTaskPayload(struct TaskNode *node)
{
    return (unsigned char *)node + 24;
}
