/* Original authored command30 state masks and load order. */
typedef unsigned char u8;
typedef unsigned int u32;
struct SceneEntityRecord { u8 preceding[48]; u32 state_flags; };
typedef char entity_flags_offset_check[((u32)&(((struct SceneEntityRecord*)0)->state_flags)==48)?1:-1];
extern struct SceneEntityRecord *ResolveSceneEntityHandle(u32);
extern void ApplySceneEntityStateMasks(struct SceneEntityRecord *,u32,u32);
u32 UpdateSceneEntityStateFromCommand(u32 *scene_context,const u8 *command)
{
    struct SceneEntityRecord *entity;
    u32 clear_mask;
    u32 set_mask;
    u32 value;
    u32 mode;
    (void)scene_context;
    entity = ResolveSceneEntityHandle(command[1]);
    clear_mask = 0;
    set_mask = 0;
    value = command[3];
    mode = command[2];
    switch (mode) {
    case 0:
        if (value != 0)
            clear_mask = 4;
        else
            set_mask = 4;
        entity->state_flags = (entity->state_flags & ~clear_mask) | set_mask;
        break;
    case 1:
        if (value == 0) {
            clear_mask = 0x1000;
            set_mask = 0x4000;
        } else {
            clear_mask = 0x5000;
            if (value != 1) {
                clear_mask = 0x4000;
                set_mask = 0x1000;
            }
        }
        ApplySceneEntityStateMasks(entity,clear_mask,set_mask);
        break;
    }
    return 0x110;
}
