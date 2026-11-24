typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct SceneEntity {
    u8 *unit;
    u32 reserved_04;
    s16 position_x;
    s16 position_height;
    s16 position_y;
} SceneEntity;

extern SceneEntity *ResolveSceneEntity(u32 selector) __asm__("0x081255c8");
extern void UpdateSceneEntityPosition(SceneEntity *entity, s32 x, s32 y)
    __asm__("0x08099e68");

/* Command 47 uses 255 independently to retain each fixed-point axis. */
u32 SetSceneEntityCoordinatesFromCommand(void *context, const u8 *command)
{
    SceneEntity *entity;
    u8 x, y;
    u8 copied_coordinate;
    (void)context;
    entity = ResolveSceneEntity(command[1]);
    x = command[2];
    if (x == 255)
        x = (u8)(entity->position_x >> 5);
    y = command[3];
    if (y == 255)
        y = (u8)(entity->position_y >> 5);
    /* Byte stores may alias the entity's unit pointer: keep each reload. */
    entity->unit[246] = x;
    entity->unit[247] = y;
    UpdateSceneEntityPosition(entity, (s8)entity->unit[246],
                              (s8)entity->unit[247]);
    copied_coordinate = entity->unit[246];
    entity->unit[249] = copied_coordinate;
    copied_coordinate = entity->unit[247];
    entity->unit[250] = copied_coordinate;
    return 272;
}
