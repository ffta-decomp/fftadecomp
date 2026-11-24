typedef unsigned char u8;
typedef unsigned int u32;
struct SceneProgressContext { u8 *records; };
extern struct SceneProgressContext *gSceneProgress;
__asm__(".global gSceneProgress\n.set gSceneProgress,0x03002810");
/* Byte stores may alias the published root; retain each observed reload. */
u32 InitializeSavedSelectorSlot(u32 slot, u32 selector, u32 enabled)
{
    u8 *first = gSceneProgress->records;
    register u32 offset __asm__("r4") = slot * 12;
    /* Keep the initialized row offset live across all four root reloads. */
    __asm__ volatile ("" : "+r" (offset));
    first += offset;
    first[176] = 0;
    {
        u8 *second = gSceneProgress->records;
        second += offset;
        second[177] = enabled;
    }
    {
        u8 *third = gSceneProgress->records + offset;
        selector += 1;
        third[179] = selector;
    }
    {
        register u8 *last __asm__("r0") = gSceneProgress->records;
        /* Preserve the final loaded base in R0 rather than destroying row offset. */
        __asm__ volatile ("" : "+r" (last));
        last += offset;
        last[178] = 0;
    }
    return 0;
}
