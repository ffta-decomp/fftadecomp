typedef unsigned char u8;
typedef unsigned int u32;

extern void CreateSceneActionFromEntityPair(u32 *scene_context,
                                            u32 first_entity_handle,
                                            u32 second_entity_handle,
                                            u32 repeated_entity_handle);

/* The retail wrapper forwards two command handles and repeats the first. */
u32 CreateSceneActionFromCommandHandles(u32 *scene_context,
                                       const u8 *command)
{
    u32 first_entity_handle = command[1];
    u32 second_entity_handle = command[2];

    CreateSceneActionFromEntityPair(scene_context, first_entity_handle,
                                    second_entity_handle,
                                    first_entity_handle);
    return 0x115;
}
