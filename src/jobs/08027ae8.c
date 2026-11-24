/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct TaskRecordView { u8 *unit; };
extern struct TaskRecordView *RetailCall_08096d88(void);
extern void *RetailCall_08096d7c(void);
extern void *RetailCall_08099544(void *);
extern u32 RetailCall_080c8240(const u8 *);
extern u32 RetailCall_080c8260(const u8 *);
extern u32 RetailCall_080ced5c(u32);
asm(".global RetailCall_08096d88\n.thumb_set RetailCall_08096d88,0x08096d89\n.global RetailCall_08096d7c\n.thumb_set RetailCall_08096d7c,0x08096d7d\n.global RetailCall_08099544\n.thumb_set RetailCall_08099544,0x08099545\n.global RetailCall_080c8240\n.thumb_set RetailCall_080c8240,0x080c8241\n.global RetailCall_080c8260\n.thumb_set RetailCall_080c8260,0x080c8261\n.global RetailCall_080ced5c\n.thumb_set RetailCall_080ced5c,0x080ced5d");

u32 ActorPassesRecordStatusGate(void)
{
    struct TaskRecordView *record=RetailCall_08096d88();
    if (RetailCall_08099544(RetailCall_08096d7c()) != 0 &&
        !(u8)RetailCall_080c8240(record->unit) &&
        !(u8)RetailCall_080c8260(record->unit) &&
        !(u8)RetailCall_080ced5c(1))
        return 1;
    return 0;
}
