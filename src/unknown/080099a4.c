typedef unsigned int u32;
struct CallbackSlot { u32 argument; void (*callback)(void); };
extern struct CallbackSlot gCallbackSlots[];
__asm__(".global gCallbackSlots\n.set gCallbackSlots,0x03000890");
u32 IsCallbackSlotEmpty(u32 slot_index)
{
    u32 empty = 0;
    if (gCallbackSlots[slot_index].callback == 0)
        empty = 1;
    return empty;
}
