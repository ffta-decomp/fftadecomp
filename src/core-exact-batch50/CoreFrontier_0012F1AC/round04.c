typedef unsigned short u16;
typedef unsigned int u32;
/* This coded interval drives the battle continuation flag; captions are unknown. */
u32 IsBattleActionIn312Through316(u16 action) asm("CoreFrontier_0012F1AC");
u32 IsBattleActionIn312Through316(u16 action)
{
    int action_id;
    int boundary;
    action_id = action;
    boundary = 316;
    if (action_id > boundary)
        goto outside_interval;
    boundary = 312;
    if (action_id < boundary)
        goto outside_interval;
    boundary = 1;
    goto finished;
outside_interval:
    boundary = 0;
finished:
    return boundary;
}
