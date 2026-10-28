typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct SceneEntityHandle {
    /* Retail reloads this pointer after the state-bit call and each store. */
    u8 * volatile unit;
};

extern struct SceneEntityHandle *ResolveSceneEntityHandle(u32 entity_id);
extern void SetIndexedUnitState(u8 *unit, u16 index, u8 value);

/* Opcode 0x2d writes one observed unit-state bit. Index zero also clears
 * two halfword fields at offsets +0x18 and +0x1c of the resolved unit. */
u32 SetSceneEntityStateFromCommand(void *scene_context, const u8 *command)
{
    struct SceneEntityHandle *handle;

    (void)scene_context;
    handle = ResolveSceneEntityHandle(command[1]);
    SetIndexedUnitState(handle->unit, command[2], command[3]);
    if (command[2] == 0) {
        *(u16 *)(handle->unit + 0x18) = 0;
        *(u16 *)(handle->unit + 0x1c) = 0;
    }
    return 0x110;
}
