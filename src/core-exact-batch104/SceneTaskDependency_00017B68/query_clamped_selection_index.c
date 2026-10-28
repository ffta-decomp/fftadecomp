typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
u32 SceneTaskDependency_00017B68(u8 *state, u32 input_offset)
{
    u32 result;
    s16 candidate = (u16)(*(u16 *)(state + 26) + (s8)input_offset);
    if (candidate < 0)
        return 0;
    if (candidate <= *(s16 *)(state + 24) - 1)
        result = (u16)candidate;
    else
        result = (u16)(*(u16 *)(state + 24) - 1);
    return result;
}
