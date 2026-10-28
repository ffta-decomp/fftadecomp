/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneCommandState { u16 position; };
struct SceneDefinition { u8 unknown_00; u8 command_id; u16 event_id; u8 unknown_04[4]; u16 flags; u8 unknown_0a[2]; };
struct SceneProgressState { u8 unknown_00[0x3c2a]; u8 selected_definition; };
typedef char DefinitionSize[sizeof(struct SceneDefinition)==12?1:-1];
typedef char FlagsOffset[(u32)&((struct SceneDefinition *)0)->flags==8?1:-1];
extern const struct SceneDefinition gSceneDefinitions[];
extern struct SceneProgressState gSceneProgress;
__asm__(".global gSceneDefinitions\n.set gSceneDefinitions,0x08563a70");
__asm__(".global gSceneProgress\n.set gSceneProgress,0x02000000");

u32 AddSceneOffsetWhenDefinitionFlag1(struct SceneCommandState *scene,
    const u8 *command);
u32 AddSceneOffsetWhenDefinitionFlag1(struct SceneCommandState *scene,
    const u8 *command)
{
    u32 selected = gSceneProgress.selected_definition;
    u32 byte_offset = selected * sizeof(struct SceneDefinition);
    const struct SceneDefinition *definition = (const struct SceneDefinition *)
        ((const u8 *)gSceneDefinitions + byte_offset);
    if (definition->flags & 1) {
        u32 displacement = command[1] | (command[2] << 8);
        scene->position += displacement;
    }
    return 272;
}
