typedef unsigned char u8;
typedef unsigned int u32;

/* The retail handler sets this scene-runtime byte to 12. */
u32 SetSceneRuntimeByteAt0200F390(u32 *scene_context, const u8 *command)
{
    volatile u8 *scene_runtime_byte = (volatile u8 *)0x0200f390;

    (void)scene_context;
    (void)command;
    *scene_runtime_byte = 12;
    return 0x112;
}
