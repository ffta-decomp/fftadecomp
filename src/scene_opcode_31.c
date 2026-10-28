typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct SceneEntityRecord {
    u8 reserved_00_1e[0x1f];
    s8 field_1f;
} SceneEntityRecord;

extern SceneEntityRecord *ResolveSceneEntityHandle(u32 handle);
extern void ClearSceneEntityAttachments(SceneEntityRecord *entity);
extern void UpdateSceneEntityAction(SceneEntityRecord *entity,
                                    u32 scaled_parameter,
                                    s32 entity_field_1f, u32 flags);
extern void RefreshSceneEntityPresentation(SceneEntityRecord *entity,
                                           u32 command_option);
extern void ApplySceneEntityStateMasks(SceneEntityRecord *entity,
                                       u32 clear_mask, u32 set_mask);

/* Opcode 0x31 replaces an entity action, refreshes it, and sets a state bit. */
u32 ReplaceSceneEntityActionFromCommand(u32 *scene_context,
                                        const u8 *command)
{
    SceneEntityRecord *entity;
    u16 parameter;

    (void)scene_context;
    entity = ResolveSceneEntityHandle(command[1]);
    parameter = (u16)(command[2] | ((u16)command[3] << 8));

    ClearSceneEntityAttachments(entity);
    parameter = (u16)(parameter << 2);
    UpdateSceneEntityAction(entity, parameter, entity->field_1f, 0);
    RefreshSceneEntityPresentation(entity, command[4]);
    ApplySceneEntityStateMasks(entity, 0, 0x100);
    return 0x110;
}

/* Retail stores a zero halfword after the function for four-byte alignment. */
__asm__(".hword 0");
