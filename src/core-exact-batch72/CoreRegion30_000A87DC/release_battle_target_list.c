typedef unsigned int u32;
typedef void (*ClearTargetListBytes)(void *, u32);
extern void ReleaseTargetListBytes(void *list);
__asm__(".global ReleaseTargetListBytes\n.thumb_set ReleaseTargetListBytes,0x08022855\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");

void ReleaseBattleTargetList(void *list)
    __asm__("CoreRegion30_000A87DC");

/* The continuation clears its list slot only after this clear/free pair. */
void ReleaseBattleTargetList(void *list)
{
    (*(ClearTargetListBytes *)0x0836d4b8)(list, 708);
    ReleaseTargetListBytes(list);
}
