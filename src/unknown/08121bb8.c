struct TaskGroup;
struct TaskNode;
struct SceneRoot { struct TaskGroup *group; };
extern struct SceneRoot *gSceneRoot;
extern void RemoveTaskSubtree(struct TaskGroup *,struct TaskNode *);
void CoreRegion_00121BB8(struct TaskNode *node)
{
 RemoveTaskSubtree(gSceneRoot->group,node);
}
asm(".global gSceneRoot\n.set gSceneRoot,0x020159CC\n.global RemoveTaskSubtree\n.thumb_set RemoveTaskSubtree,0x080058A5");
