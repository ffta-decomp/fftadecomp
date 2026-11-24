typedef unsigned char u8;
typedef unsigned int u32;

extern void ProcessSceneActionSelector(u32 selector);
extern u32 GetIndexedFlagState(u32 flag_index);

/* The handler dispatches the selector, then reports indexed flag 13. */
u32 ProcessSceneActionSelectorFromCommand(u32 *scene_context,
                                          const u8 *command)
{
    u8 flag_state;
    u32 result;

    (void)scene_context;
    ProcessSceneActionSelector(command[1]);
    flag_state = (u8)GetIndexedFlagState(13);
    result = 0x110;
    if (flag_state == 1)
        result += 9;
    return result;
}
