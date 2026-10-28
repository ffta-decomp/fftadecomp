typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 RetailCall_0812ea44(void *actor, void *target, u32 action);

u16 ReadTargetReactionAtTemporaryCoordinates(void *actor, void *target, u16 action,
                          s8 new_actor_x, s8 new_actor_y,
                          s8 new_target_x, s8 new_target_y)
{
    u8 *actor_x = (u8 *)actor + 246;
    u8 saved_actor_x = *actor_x;
    u8 *actor_y = (u8 *)actor + 247;
    u8 saved_actor_y = *actor_y;
    u8 *target_x = (u8 *)target + 246;
    u8 saved_target_x = *target_x;
    u8 *target_y = (u8 *)target + 247;
    u8 saved_target_y = *target_y;
    u16 reaction;

    *actor_x = new_actor_x;
    *actor_y = new_actor_y;
    *target_x = new_target_x;
    *target_y = new_target_y;
    reaction = RetailCall_0812ea44(actor, target, action);
    *actor_x = saved_actor_x;
    *actor_y = saved_actor_y;
    *target_x = saved_target_x;
    *target_y = saved_target_y;
    return reaction;
}
