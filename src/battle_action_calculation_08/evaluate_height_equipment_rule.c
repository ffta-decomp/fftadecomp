/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitHeightView { u8 prefix[248]; u8 height; };
extern u8 UnitPredicate_0012C960(const void *unit);
extern u32 ReadUnitField(const void *unit, u8 selector);
extern u8 ItemPredicate_0012D07C(const void *unit, u16 item_id, u32 value);

asm(".global UnitPredicate_0012C960\n.thumb_set UnitPredicate_0012C960,0x0812c961\n.global ItemPredicate_0012D07C\n.thumb_set ItemPredicate_0012D07C,0x0812d07d");
u32 EvaluateHeightEquipmentRule(const struct UnitHeightView *actor, const struct UnitHeightView *target, u32 value)
{
    /* The checked scalar is reused for the subsequent equipment property. */
    int checked_value = actor->height - target->height;
    int equipment_slot;
    if (checked_value < 0)
        checked_value = -checked_value;
    if (UnitPredicate_0012C960(target) || checked_value != 2)
        return 0;
    for (equipment_slot = 0; equipment_slot <= 4; equipment_slot++) {
        checked_value = ReadUnitField(target, equipment_slot + 29);
        if (checked_value && !ItemPredicate_0012D07C(target, checked_value, value))
            return 0;
    }
    return 100;
}
