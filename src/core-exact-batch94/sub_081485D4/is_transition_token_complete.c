typedef unsigned short u16;
typedef unsigned int u32;
u32 IsTransitionTokenComplete(const u16 *token)
{
    u32 complete = 0;
    if (*token == 0)
        complete = 1;
    return complete;
}
