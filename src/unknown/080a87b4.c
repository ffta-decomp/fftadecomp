typedef unsigned int u32;
typedef void (*ClearTargetListBytes)(void *, u32);
extern void *AllocateTargetListBytes(u32 bytes);
__asm__(".global AllocateTargetListBytes\n.thumb_set AllocateTargetListBytes,0x08022841\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");

void *CreateBattleTargetList(void) __asm__("CoreRegion30_000A87B4");

/* Preserve the shared allocation/clear extent; no guessed row capacity. */
void *CreateBattleTargetList(void)
{
    void *list = AllocateTargetListBytes(708);
    (*(ClearTargetListBytes *)0x0836d4b8)(list, 708);
    return list;
}
