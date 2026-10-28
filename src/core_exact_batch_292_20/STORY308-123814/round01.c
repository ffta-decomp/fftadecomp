typedef unsigned char u8;
typedef unsigned int u32;

extern void UpdateSceneEntityActions(u32 selector);
extern void FilterSceneEntitiesForTransition(u32 selector);

/* Opcode 0x4f chooses an existing live-entity transition policy.
 * Read the mode before the per-arm selector, as in the original command. */
u32 Scene51_00123814(void *scene_context, const u8 *command)
{
    if (command[2] != 0)
        UpdateSceneEntityActions(command[1]);
    else
        FilterSceneEntitiesForTransition(command[1]);
    return 0x110;
}

__asm__(".global UpdateSceneEntityActions\n"
        ".thumb_set UpdateSceneEntityActions,0x081247b5\n"
        ".global FilterSceneEntitiesForTransition\n"
        ".thumb_set FilterSceneEntitiesForTransition,0x08124851\n");
