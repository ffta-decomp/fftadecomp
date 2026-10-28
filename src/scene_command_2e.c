typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SceneEntityRecord {
    u8 reserved_00_07[8];
    u16 field_08;
    u16 field_0a;
    u16 field_0c;
} SceneEntityRecord;

extern SceneEntityRecord *ResolveSceneEntityHandle(u32 handle);

/* Opcode 0x2e adds three command halfwords to fields on the resolved entity. */
u32 AddSceneEntityFieldsFromCommand(u32 *scene_context, const u8 *command)
{
    SceneEntityRecord *entity;
    u16 increment;

    (void)scene_context;
    entity = ResolveSceneEntityHandle(command[1]);

    increment = (u16)(command[2] | ((u16)command[3] << 8));
    entity->field_08 = (u16)(entity->field_08 + increment);
    increment = (u16)(command[4] | ((u16)command[5] << 8));
    entity->field_0c = (u16)(entity->field_0c + increment);
    increment = (u16)(command[6] | ((u16)command[7] << 8));
    entity->field_0a = (u16)(entity->field_0a + increment);
    return 0x110;
}

/* Retail stores a zero halfword after the function for four-byte alignment. */
__asm__(".hword 0");
