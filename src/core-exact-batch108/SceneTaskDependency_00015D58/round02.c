typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ManagedController {
    u8 unknown_00[20]; u16 flags; u8 unknown_16[22];
    u8 shared_data[32]; u8 primary[20]; u8 secondary[20];
};
extern void InitializeSelectionPrimary(void *, void *, void *, u32);
extern void InitializeSelectionSecondary(void *, void *, void *, u32);
void BindManagedSelectionCallbacks(struct ManagedController *controller,
                                  void *primary_callback, void *secondary_callback)
{
    void *data = controller->shared_data;
    u32 flags = 3;
    if (controller->flags & 0x100) flags = 7;
    if ((controller->flags & 0xc0) == 0x80) flags |= 8;
    InitializeSelectionPrimary(controller->primary, data, primary_callback, flags);
    flags = (controller->flags & 2) ? 49 : 0;
    InitializeSelectionSecondary(controller->secondary, data, secondary_callback, flags);
}
asm(".thumb_set InitializeSelectionPrimary, 0x08017c29\n");
asm(".thumb_set InitializeSelectionSecondary, 0x08017db5\n");
