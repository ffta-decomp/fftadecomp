typedef unsigned char u8;
typedef unsigned int u32;

extern void ApplySceneCommandOperands(u32 *scene_context,
                                      u32 command_selector,
                                      u32 command_subtype,
                                      u32 action_kind,
                                      u32 selector_flags,
                                      u32 command_value);

/* Opcode 0x41 splits command byte 2 into low subtype and high flags. */
u32 ApplySceneCommandFromPackedOperands(u32 *scene_context,
                                        const u8 *command)
{
    u32 selector = command[1];
    /* Keep the shared packed byte in r4 across both mask operations. */
    register u32 packed_subtype __asm__("r4") = command[2];

    ApplySceneCommandOperands(scene_context, selector, packed_subtype & 0x0f,
                              1, (packed_subtype & 0x70) >> 4, command[3]);
    return 0x115;
}
