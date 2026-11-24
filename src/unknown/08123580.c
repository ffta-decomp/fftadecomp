typedef unsigned char u8;
typedef unsigned int u32;
struct SceneCommandOwner;
extern void CreateSceneCoordinateRequest(struct SceneCommandOwner *, u8 unit_selector,
                                         u8 path_selector, u8 delay, u8 tail);
u32 ApplySceneCoordinatePathOperands(struct SceneCommandOwner *owner, const u8 *command)
{
    u8 unit_selector = command[1];
    u8 path_selector = command[2];
    u32 packed = command[4];
    register u32 delay __asm__("r3") = 15;
    u8 tail;
    /* Preserve the original in-place argument mask without an extra packed copy.
       Initialized read/write allocation constraint; no emitted instruction. */
    asm("" : "+r"(delay));
    delay &= packed;
    /* Bind the initialized result at consumption without changing its byte domain. */
    asm("" : : "r"(delay));
    tail = packed >> 4;
    CreateSceneCoordinateRequest(owner, unit_selector, path_selector, (u8)delay, tail);
    return 0x115;
}
asm(".global CreateSceneCoordinateRequest\n.thumb_set CreateSceneCoordinateRequest,0x08127b41\n");
