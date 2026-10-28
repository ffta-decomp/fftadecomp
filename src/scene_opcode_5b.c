typedef unsigned char u8;
typedef unsigned int u32;

extern void *GetSceneCommandTaskContext(void);
extern u32 IsSceneCommandTaskComplete(void);
extern void ReleaseSceneCommandTaskContext(void *task_context);
extern void SetSceneCommandTaskContext(void *task_context);

/* Opcode 0x5b waits for completion, then releases and clears the task context. */
u32 WaitForSceneCommandTaskCompletion(u32 *scene_context, const u8 *command)
{
    void *task_context;

    (void)scene_context;
    (void)command;
    task_context = GetSceneCommandTaskContext();
    if ((IsSceneCommandTaskComplete() << 24) == 0)
        goto pending;
    ReleaseSceneCommandTaskContext(task_context);
    SetSceneCommandTaskContext(0);
    return 0x110;

pending:
    return 0x118;
}

/* Retail stores a zero halfword after this function for four-byte alignment. */
__asm__(".hword 0");
