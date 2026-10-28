typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SceneCommandTarget {
    u8 reserved_00_27[0x28];
    u16 flags_28;
} SceneCommandTarget;

extern SceneCommandTarget *ResolveSceneCommandHandle(u32 handle);

/* Opcode 0x37 marks the resolved scene command target with flag 0x100. */
u32 SetSceneCommandTargetFlagFromCommand(u32 *scene_context,
                                         const u8 *command)
{
    SceneCommandTarget *target;

    (void)scene_context;
    target = ResolveSceneCommandHandle(command[1]);
    if (target != 0)
        target->flags_28 |= 0x100;
    return 0x110;
}

/* Retail stores a zero halfword after the function for four-byte alignment. */
__asm__(".hword 0");
