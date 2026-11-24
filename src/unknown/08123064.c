typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SceneEntityRecord {
    u8 *object_data;
} SceneEntityRecord;

extern SceneEntityRecord *ResolveSceneEntityHandle(u32 handle);
extern void ApplySceneEntityState(SceneEntityRecord *entity, u32 state_kind,
                                  u32 state_value);

/* Opcode 0x28 reapplies state kind 1 using the entity byte at object data +0xf8. */
u32 ReapplySceneEntityStateFromCommand(u32 *scene_context,
                                       const u8 *command)
{
    SceneEntityRecord *entity;
    u8 current_state;

    (void)scene_context;
    entity = ResolveSceneEntityHandle(command[1]);
    current_state = entity->object_data[0xf8];
    ApplySceneEntityState(entity, 1, current_state);
    return 0x110;
}
