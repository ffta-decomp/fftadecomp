typedef unsigned int u32;
struct CallbackSlot { u32 argument; void (*callback)(void); };
extern struct CallbackSlot gCallbackSlots[];
__asm__(".global gCallbackSlots\n.set gCallbackSlots,0x03000890");
u32 RegisterCallbackSlot(void (*callback)(void), u32 argument)
{
    u32 slot_index = 0;
    u32 result;
    struct CallbackSlot *slot = gCallbackSlots;
check_slot:
    if (slot->callback != 0)
        goto occupied;
    slot->callback = callback;
    slot->argument = argument;
    result = slot_index;
    goto done;
occupied:
    ++slot;
    ++slot_index;
    if ((int)slot_index <= 3)
        goto check_slot;
    result = 0;
done:
    return result;
}
