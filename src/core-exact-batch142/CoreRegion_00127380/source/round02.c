typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed short s16;
struct SceneActorCoordinates { u8 unaccessed_00[8]; u16 x; u16 y; u16 z; };
struct SceneModeState {
    u32 unaccessed_00; struct SceneActorCoordinates *actor;
    u8 unaccessed_08[7]; u8 mode; u8 unaccessed_16[2];
    u16 target_x; u16 target_y; u16 target_z;
};
struct ScenePackedPoint { s32 x:16; s32 y:16; s32 z:16; s32 unassigned_06:16; };
typedef char PointSize[sizeof(struct ScenePackedPoint)==8?1:-1];
typedef char ModeOffset[(u32)&(((struct SceneModeState *)0)->mode)==15?1:-1];
typedef char TargetOffset[(u32)&(((struct SceneModeState *)0)->target_x)==18?1:-1];
u32 SelectSceneUnitModeByDistance(struct SceneModeState *state)
{
    struct ScenePackedPoint source;
    struct ScenePackedPoint destination;
    s16 *source_components;
    s16 *destination_components;
    s32 distance_x, distance_z, distance;
    u32 in_second_band;
    source.x = state->actor->x;
    source.y = state->actor->y;
    source.z = state->actor->z;
    destination.x = (u16)(state->target_x * 32 + 16);
    destination.z = (u16)(state->target_z * 32 + 16);
    destination.y = (u16)(state->target_y * 32 + 16);
    /* Native takes both complete object addresses and reads signed halves. */
    source_components = (s16 *)&source;
    destination_components = (s16 *)&destination;
    distance_x = source_components[0] - destination_components[0];
    if (distance_x < 0) distance_x = -distance_x;
    distance_z = source_components[2] - destination_components[2];
    if (distance_z < 0) distance_z = -distance_z;
    distance = distance_x;
    if (distance < distance_z) distance = distance_z;
    if (distance <= 7) goto outer_band;
    if (distance <= 15) goto middle_band;
    in_second_band = 0;
    if (distance <= 23) in_second_band = 1;
    if (in_second_band == 0) goto outer_band;
middle_band:
    if (state->mode == 1) return 2;
    if (state->mode == 3) return 0;
    return state->mode;
outer_band:
    if (state->mode == 0) return 1;
    if (state->mode == 2) return 3;
    return state->mode;
}
