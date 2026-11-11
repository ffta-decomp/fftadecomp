typedef unsigned int u32;
typedef void (*MemoryClear)(void *, u32);
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
void ClearBattleAuxiliaryWorkspace(void)
{
    (*(const MemoryClear *)0x0836d4b8)((void *)0x0200ffc8, 132);
}
