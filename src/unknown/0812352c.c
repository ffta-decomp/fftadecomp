typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct SceneCommandOwner;
extern void CreateScenePathRequest(struct SceneCommandOwner *, u8 unit_selector,
                                  u8 path_selector, u8 repetitions, u8 delay, u8 tail);
u32 ApplyScenePackedPathRange(struct SceneCommandOwner *owner, const u8 *command)
{
    u32 packed = command[2];
    register u32 lower_projection __asm__("r4") = 15;
    u8 unit_selector;
    u8 path_selector;
    u32 upper;
    s32 signed_lower;
    u8 repetitions;
    /* Retain the two original destructive definitions and shared shifted value.
       Both initialized read/write constraints emit no instructions. */
    asm("" : "+r"(lower_projection));
    lower_projection &= packed;
    asm("" : "+r"(lower_projection));
    unit_selector = command[1];
    lower_projection <<= 24;
    path_selector = lower_projection >> 24;
    upper = packed >> 4;
    signed_lower = (s32)lower_projection >> 24;
    repetitions = upper - signed_lower + 1;
    CreateScenePathRequest(owner, unit_selector, path_selector, repetitions, command[3], 0);
    return 0x115;
}
asm(".global CreateScenePathRequest\n.thumb_set CreateScenePathRequest,0x08127af9\n");
