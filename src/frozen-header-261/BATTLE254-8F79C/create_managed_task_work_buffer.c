#include "../../task_tree_core.h"

typedef void (*ClearWorkBufferBytes)(void *, u32);
__asm__(".global Allocate_08007138\n.thumb_set Allocate_08007138, 0x08007139\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

/* The byte extent is observed; the buffer's wider data model remains unknown. */
void *CreateManagedTaskWorkBuffer(void) __asm__("CoreConsumer_0008F79C");
void *CreateManagedTaskWorkBuffer(void)
{
    void *buffer = Allocate_08007138(*(void **)0x0200f458, 364);
    (*(ClearWorkBufferBytes *)0x0836d4b8)(buffer, 364);
    return buffer;
}
