typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SceneEntityRecord {
    u8 reserved_00_1e[0x1f];
    u8 field_1f;
} SceneEntityRecord;

extern SceneEntityRecord *ResolveSceneEntityHandle(u32 handle);

/* Opcode 0x29 writes its second operand to the resolved record's byte +0x1f. */
u32 SetSceneEntityField1fFromCommand(u32 *scene_context, const u8 *command)
{
    SceneEntityRecord *entity;

    (void)scene_context;
    entity = ResolveSceneEntityHandle(command[1]);
    entity->field_1f = command[2];
    return 0x110;
}
