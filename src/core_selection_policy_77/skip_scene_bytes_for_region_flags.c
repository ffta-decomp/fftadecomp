/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Scene {u16 position;};
struct GameState {u8 unknown00[0x3c2a];u8 selected_region;};
struct RegionDefinition {u8 unknown00[8];u16 flags;u8 unknown0a[2];};
extern struct GameState game_state;
extern const struct RegionDefinition region_definitions[];
typedef char RegionStride[sizeof(struct RegionDefinition)==12?1:-1];
asm(".global game_state\n.set game_state,0x02000000");
asm(".global region_definitions\n.set region_definitions,0x08563a70");


u32 SkipSceneBytesForRegionFlags(struct Scene *scene, const u8 *command)
{
    u32 region = game_state.selected_region;
    u32 record_offset = region * sizeof(struct RegionDefinition);
    const struct RegionDefinition *definition = (const struct RegionDefinition *)((const u8 *)region_definitions + record_offset);
    if (!(definition->flags & 2)) {
        u32 displacement = command[1] | (command[2] << 8);
        scene->position += displacement;
    }
    return 272;
}
