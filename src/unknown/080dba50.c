extern void RemoveCurrentGroupTaskSubtree(void *node);
__asm__(".global RemoveCurrentGroupTaskSubtree\n.thumb_set RemoveCurrentGroupTaskSubtree,0x08005b59");
void RemoveSceneTaskBranch(void *node)
{
    RemoveCurrentGroupTaskSubtree(node);
}
