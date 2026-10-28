typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void SetSceneRuntimeModeField(u32 value, u32 byte_mask);
extern void DispatchSceneCommandPayload(u32 mode, u32 packed_payload);

/* Opcode 0x4c configures a mode field, dispatches its packed payload, and clears the selection. */
u32 ConfigureAndApplySceneCommandFromBytes(u16 *scene_context,
                                           const u8 *command)
{
    u32 packed_payload = (u32)command[1] | ((u32)command[2] << 8);
    u32 mode = command[3];

    if (mode == 0xff) {
        SetSceneRuntimeModeField(0x6400, 2);
        DispatchSceneCommandPayload(1, packed_payload);
    } else {
        switch (mode) {
        case 2:
            mode = 1;
            SetSceneRuntimeModeField(0x6400, 2);
            break;
        case 4:
            mode = 2;
            SetSceneRuntimeModeField(0x640000, 4);
            break;
        }
        DispatchSceneCommandPayload(mode, packed_payload);
    }

    scene_context[2] = 0;
    return 0x114;
}
