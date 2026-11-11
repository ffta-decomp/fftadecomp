typedef unsigned char u8;
typedef unsigned int u32;

extern void ProcessSceneActionRecordSelection(u32 command_selector,
                                              u32 command_subtype,
                                              u32 command_flags,
                                              u32 command_argument,
                                              u32 command_mode);

/* Opcode 0x20 unpacks its selector, subtype, flags, argument, and mode. */
u32 ProcessSceneActionRecordFromCommand(u32 *scene_context,
                                        const u8 *command)
{
    u32 command_selector;
    register u32 packed_subtype_and_flags __asm__("r2");
    register u32 nibble_mask __asm__("r4");
    u32 command_subtype;
    u32 command_flags;
    u32 command_argument;
    u32 command_mode;

    (void)scene_context;
    /* Retail loads the selector before the packed subtype byte. Keeping the
     * packed byte and mask in r2/r4 preserves that load and mask order. */
    command_selector = command[1];
    packed_subtype_and_flags = command[2];
    nibble_mask = 0x0f;
    command_subtype = nibble_mask;
    command_subtype &= packed_subtype_and_flags;
    command_flags = packed_subtype_and_flags >> 4;
    command_argument = command[3];
    command_mode = command[4];
    /* Reuse the mask as the fifth argument's low-nibble value. */
    nibble_mask &= command_mode;
    ProcessSceneActionRecordSelection(command_selector, command_subtype,
                                      command_flags, command_argument,
                                      nibble_mask);
    return 0x110;
}
