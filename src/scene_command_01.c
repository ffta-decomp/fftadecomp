typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern const u8 gSceneCommandDefinitionTable[];
extern u32 CreateSceneContextEntry(u32 *scene_context, u32 value, u32 kind);

/* Opcode 0x01 adds a definition-table base to its command operand. */
u32 CreateSceneEntryFromCommand(u32 *scene_context, const u8 *command)
{
    /* Fixed registers keep the recovered operations in retail instruction order. */
    register const u8 *table_base __asm__("r3") = gSceneCommandDefinitionTable;
    register u32 definition_index __asm__("r2") = command[0];
    u32 definition_offset = definition_index * 6;
    register const u8 *definition __asm__("r1") =
        (const u8 *)(definition_offset + (u32)table_base);
    register u16 base_value __asm__("r1") =
        (u16)(definition[0] | ((u16)definition[1] << 8));
    register u16 command_value __asm__("r3") =
        (u16)(command[1] | ((u16)command[2] << 8));
    register u16 value __asm__("r1") = (u16)(base_value + command_value);

    CreateSceneContextEntry(scene_context, value, 0x80);
    return 0x110;
}
