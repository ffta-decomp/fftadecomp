/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef struct { u8 bytes00[246]; u8 grid_x; u8 grid_y; } UnitCoordinates;
typedef struct { UnitCoordinates *unit; } BattleActor;
typedef struct { void *grid; BattleActor *selected; } GridSelection;
typedef char UnitXOffset[((u32)&((UnitCoordinates *)0)->grid_x == 246) ? 1 : -1];
extern u32 UnitField19IsZero(const void *);
extern u32 ReadScaledEquipment(const void *);
extern u32 DivideUnsigned(u32, u32);
extern u32 TestStatus12(const void *);
extern u32 UnitField27HasBit15(const void *);
/* The caller supplies eight words; the selected grid implementation consumes seven. */
extern void SetGridCell(void *, s16, s16, u8, u16, u8, u8, u32);
__asm__(".global ReadScaledEquipment\n.thumb_set ReadScaledEquipment,0x080ca3ed\n"
        ".global DivideUnsigned\n.thumb_set DivideUnsigned,0x08142ab1\n"
        ".global TestStatus12\n.thumb_set TestStatus12,0x080c8299\n"
        ".global SetGridCell\n.thumb_set SetGridCell,0x081491c1\n");

/* Mark the actor's unit position when the observed equipment/status gates allow it. */
u32 MarkActorGridCell(BattleActor *actor, GridSelection *selection)
{
    BattleActor *selected = selection->selected;
    u32 actor_side;
    u32 selected_side;
    if (selected == actor)
        return 1;
    if ((u8)UnitField19IsZero(actor->unit) != 0)
        return 1;
    if (DivideUnsigned(ReadScaledEquipment(actor->unit), 10) != 0) {
        if ((u8)TestStatus12(selected->unit) != 0)
            return 1;
        actor_side = UnitField27HasBit15(actor->unit);
        selected_side = UnitField27HasBit15(selected->unit);
        if ((u8)actor_side == (u8)selected_side)
            return 1;
    }
    SetGridCell(selection->grid, actor->unit->grid_x, actor->unit->grid_y,
                0, 0, 1, 0, 0);
    return 1;
}
