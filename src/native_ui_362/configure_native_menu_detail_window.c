typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct MenuDetailGeometry {
    u8 unknown_00[8];
    u16 width;
    u16 height;
    u16 unknown_12;
    u16 top;
    u8 flags;
};

extern u8 *gNativeMenuRoot;
extern u8 gNativeSelectionRuntime[];
extern u8 gNativeWindowRuntime[];
extern void *SetCurrentNativeTextContext(void *context);
extern void ConfigureNativeTextRecord(void *context, u16 record,
                                      void *selection_runtime,
                                      void *window_runtime);
extern u32 EnableTextContextFlag512(void);
extern void InstallNativeMenuCallbackPair(void);
extern void RestoreNativeSelectionRequestFlags(void *selection, u32 enabled);

void ConfigureNativeMenuDetailWindow(void *object)
{
    struct MenuDetailGeometry *selection =
        (struct MenuDetailGeometry *)((u8 *)object + 92);
    struct MenuDetailGeometry *window =
        (struct MenuDetailGeometry *)((u32)object + 112);
    u8 *context;

    SetCurrentNativeTextContext(gNativeMenuRoot + 0x5B4);
    context = gNativeMenuRoot;
    ConfigureNativeTextRecord(context + 0x5B4, *(u16 *)(context + 30),
                              gNativeSelectionRuntime, gNativeWindowRuntime);
    switch (*(u8 *)object) {
    case 1:
    case 5:
        EnableTextContextFlag512();
        break;
    case 6:
        InstallNativeMenuCallbackPair();
        break;
    }
    gNativeMenuRoot[29] = selection->flags;
    if (selection->height + selection->top <= 64)
        RestoreNativeSelectionRequestFlags(selection, 0);
    else
        RestoreNativeSelectionRequestFlags(selection, 1);

    if (window != 0) {
        if (window->width <= 224 && window->height <= 64)
            window->flags &= 0xFB;
        window->flags |= 0x40;
    }
}

asm(".set gNativeMenuRoot, 0x0200F44C\n"
    ".set gNativeSelectionRuntime, 0x030008B0\n"
    ".set gNativeWindowRuntime, 0x03000990\n"
    ".thumb_set SetCurrentNativeTextContext, 0x08013391\n"
    ".thumb_set ConfigureNativeTextRecord, 0x08019A8D\n"
    ".thumb_set EnableTextContextFlag512, 0x08013435\n"
    ".thumb_set InstallNativeMenuCallbackPair, 0x080615B1\n"
    ".thumb_set RestoreNativeSelectionRequestFlags, 0x08017D19\n");
