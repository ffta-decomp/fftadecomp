typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SceneCommandTarget {
    u8 reserved_00_27[0x28];
    u16 flags_28;
} SceneCommandTarget;

extern SceneCommandTarget *ResolveSceneCommandHandle(u32 handle);

/* Opcode 0x66 conditionally adds a command halfword to the scene context. */
u32 AddSceneContextValueWhenTargetFlagSet(u16 *scene_value,
                                          const u8 *command)
{
    SceneCommandTarget *target;

    target = ResolveSceneCommandHandle(command[1]);
    if (target != 0 && ((target->flags_28 >> command[2]) & 1) != 0) {
        u16 increment;

        increment = (u16)(command[3] | ((u16)command[4] << 8));
        *scene_value = (u16)(*scene_value + increment);
    }

    return 0x110;
}

/* Retail stores a zero halfword after this function for four-byte alignment. */
__asm__(".hword 0");
