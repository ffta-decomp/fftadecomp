#include "../../task_tree_core.h"

typedef void (*ClearWorkBufferBytes)(void *, u32);
__asm__(".global Free_08007170\n.thumb_set Free_08007170, 0x08007171\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

/* Reload the allocator after the callback, preserving callback-visible effects. */
void ReleaseManagedTaskWorkBuffer(void *buffer) __asm__("CoreConsumer_0008F7CC");
void ReleaseManagedTaskWorkBuffer(void *buffer)
{
    (*(ClearWorkBufferBytes *)0x0836d4b8)(buffer, 364);
    Free_08007170(*(void **)0x0200f458, buffer);
}
