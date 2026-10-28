typedef unsigned int u32;
typedef void (*MemoryClear)(void *, u32);
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");
void ClearFirstWord(void *address) __asm__("SceneActionDependency_0000718C");
void ClearFirstWord(void *address)
{
    (*(MemoryClear *)0x0836d4b8)(address, 4);
}
