typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SceneEntityRecord SceneEntityRecord;

extern SceneEntityRecord *ResolveSceneEntityHandle(u32 handle);
extern void SetCurrentSceneEntityRecord(SceneEntityRecord *entity);

/*
 * Selects the entity referenced by this command for later scene operations.
 * The helper stores the resolved pointer in the scene runtime's current-entity
 * slot; the dispatcher return value is 0x110.
 */
u32 SetCurrentSceneEntityFromCommand(u32 *scene_context, const u8 *command)
{
    SceneEntityRecord *entity;

    (void)scene_context;
    entity = ResolveSceneEntityHandle(command[1]);
    SetCurrentSceneEntityRecord(entity);
    return 0x110;
}
