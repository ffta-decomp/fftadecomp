typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct { u8 opaque0[4]; void *record; u8 opaque8[12]; u16 x, y, mode; u16 opaque26; } Event;
extern void GetRecordGrid(void *, s16 *, s16 *) asm("RetailCall_080d8b5c");
extern u32 GetGridHeight(u32, u32) asm("RetailCall_0801cc18");
extern void GridToWorld(int, u32, int, s16 *, s16 *, s16 *) asm("RetailCall_0801ca78");
extern void WorldToScreen(int, int, int, s16 *, s16 *) asm("RetailCall_0801c984");
extern void *CreateCallback(void *, u32, Event *, void *) asm("RetailCall_08005b6c");
extern u8 SequenceCallback[] asm("0x080eed89");
void *RemainingBand43_000EEE50(void *record, u8 mode, void *parent)
{
    Event event;
    s16 grid_x, grid_z;
    s16 world_x, world_y, world_z;
    s16 screen_x, screen_y;
    u32 height;
    GetRecordGrid(record, &grid_x, &grid_z);
    height = (u8)GetGridHeight((u8)grid_x, (u8)grid_z);
    GridToWorld(grid_x, height, grid_z, &world_x, &world_y, &world_z);
    WorldToScreen(world_x, world_y, world_z, &screen_x, &screen_y);
    event.x = screen_x;
    event.y = screen_y;
    event.mode = mode;
    event.record = record;
    return CreateCallback(SequenceCallback, 28, &event, parent);
}
asm(".global RetailCall_080d8b5c\n.thumb_set RetailCall_080d8b5c,0x080d8b5d\n"
    ".global RetailCall_0801cc18\n.thumb_set RetailCall_0801cc18,0x0801cc19\n"
    ".global RetailCall_0801ca78\n.thumb_set RetailCall_0801ca78,0x0801ca79\n"
    ".global RetailCall_0801c984\n.thumb_set RetailCall_0801c984,0x0801c985\n"
    ".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n");
