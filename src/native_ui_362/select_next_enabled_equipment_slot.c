typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* A view of only the observed selection byte and five availability fields. */
struct EquipmentSelectionContext {
    u8 unknown00[0xc1d];
    u8 selected_slot;
    u8 unknownc1e[0x3e];
    u16 slot_available[5];
};
typedef char SlotOffset[(u32)&((struct EquipmentSelectionContext *)0)->selected_slot==0xc1d?1:-1];
typedef char AvailabilityOffset[(u32)&((struct EquipmentSelectionContext *)0)->slot_available==0xc5c?1:-1];
extern struct EquipmentSelectionContext *EquipmentSelectionOwner asm("0x03002818");
extern void RequestSelectionChange(u32) asm("RetailCall_08141540");
asm(".global RetailCall_08141540\n.thumb_set RetailCall_08141540,0x08141541\n");
u32 SelectNextEnabledEquipmentSlot(void) asm("CoreScene34_0007A6CC");
u32 SelectNextEnabledEquipmentSlot(void)
{
    u8 old=EquipmentSelectionOwner->selected_slot;
    do {
        if (EquipmentSelectionOwner->selected_slot<=3)
            EquipmentSelectionOwner->selected_slot++;
        else
            EquipmentSelectionOwner->selected_slot=0;
    } while (!EquipmentSelectionOwner->slot_available[EquipmentSelectionOwner->selected_slot]);
    if (old!=EquipmentSelectionOwner->selected_slot)
        RequestSelectionChange(101);
    return EquipmentSelectionOwner->selected_slot;
}
