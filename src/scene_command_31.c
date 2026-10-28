typedef unsigned char u8;
typedef unsigned int u32;

extern void ApplyScenePackedAction(u32 action_code, u32 middle_low,
                                   u32 middle_high, u32 middle_value,
                                   u32 trailing_low, u32 trailing_value,
                                   u32 trailing_high);

/* Opcode 0x1f unpacks two nibble pairs and forwards all command fields. */
u32 ApplyScenePackedActionFromCommand(u32 *scene_context, const u8 *command)
{
    /* Fixed registers reproduce the retail packed-argument sequence. */
    register const volatile u8 *command_pointer __asm__("r1") = command;
    register u32 action_code __asm__("r0") = command_pointer[1];
    register u32 packed_middle __asm__("r2") = command_pointer[2];
    register u32 nibble_mask __asm__("r5") = 0x0f;
    register u32 middle_low __asm__("r6") = nibble_mask & packed_middle;
    register u32 middle_high __asm__("r2") = packed_middle >> 4;
    register u32 middle_value __asm__("r3") = command_pointer[3];
    register u32 packed_trailing __asm__("r4") = command_pointer[4];
    register u32 trailing_low __asm__("r5") = packed_trailing & nibble_mask;
    register u32 trailing_value __asm__("r1") = command_pointer[5];
    register u32 trailing_high __asm__("r4") = packed_trailing >> 4;

    (void)scene_context;
    ApplyScenePackedAction(action_code, middle_low, middle_high,
                           middle_value, trailing_low, trailing_value,
                           trailing_high);
    return 0x110;
}

/* The retail function ends with a zero alignment halfword. */
__asm__(".short 0");
