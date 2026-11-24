typedef unsigned short u16;
typedef unsigned int u32;
struct SavedOptionsContext;
extern void InitializeSavedOptionsWorkingCopy(struct SavedOptionsContext *,
    const void *, const void *, u16, u32);
__asm__(".global InitializeSavedOptionsWorkingCopy\n.thumb_set InitializeSavedOptionsWorkingCopy,0x08008819");

/* The original constructor receives these fixed resources and zero linked value. */
void InitializeDefaultSavedOptionsContext(struct SavedOptionsContext *context)
{
    InitializeSavedOptionsWorkingCopy(context, (const void *)0x030008b0,
                                     (const void *)0x03000990, 224, 0);
}
