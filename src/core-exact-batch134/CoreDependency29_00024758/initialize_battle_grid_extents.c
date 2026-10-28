#include "../../../src/task_tree_core.h"

typedef signed short s16;
typedef void (*MemoryRoutine)(void *, u32);
struct BattleGridExtentState {
    u8 unknown_00[4];
    u8 state;
    u8 unknown_05[3];
    u8 mode;
    u8 scale;
    u8 enabled;
    u8 unknown_0b[9];
    u16 pending;
    u16 selection;
    u16 target;
    u8 unknown_1a[2];
    u8 minimum_x;
    u8 minimum_y;
    u8 maximum_x;
    u8 maximum_y;
    s16 screen_left;
    s16 screen_top;
    s16 screen_right;
    s16 screen_bottom;
};
typedef char BattleGridExtentStateMustBe40Bytes[sizeof(struct BattleGridExtentState)==40?1:-1];
extern MemoryRoutine const gClearBytesRoutine;
extern void CallMemoryRoutine(void *, u32, MemoryRoutine);
extern void ReadBattleGridBounds(u8 *, u8 *, u8 *, u8 *);
extern void ReadBattleScreenBounds(u16 *);

void InitializeBattleGridExtents(struct BattleGridExtentState *record)
{
    u16 screen_bounds[6];
    u8 horizontal_extent;
    u8 vertical_extent;
    u8 minimum_x;
    u8 minimum_y;
    CallMemoryRoutine(record, 40, gClearBytesRoutine);
    record->state = 0;
    record->mode = 2;
    record->scale = 8;
    record->enabled = 1;
    record->selection = 0xffff;
    record->target = 0xffff;
    record->pending = 0xffff;
    ReadBattleGridBounds(&horizontal_extent, &vertical_extent, &minimum_x, &minimum_y);
    record->minimum_x = minimum_x;
    record->minimum_y = minimum_y;
    record->maximum_x = minimum_x + horizontal_extent;
    record->maximum_y = minimum_y + vertical_extent;
    ReadBattleScreenBounds(screen_bounds);
    record->screen_left = screen_bounds[0] - 104;
    record->screen_top = screen_bounds[1] - 80;
    record->screen_right = screen_bounds[2] - 136;
    record->screen_bottom = screen_bounds[3] - 96;
}
asm(".global gClearBytesRoutine\n.set gClearBytesRoutine,0x0836d4b8\n"
    ".global CallMemoryRoutine\n.thumb_set CallMemoryRoutine,0x0814224d\n"
    ".global ReadBattleGridBounds\n.thumb_set ReadBattleGridBounds,0x0801cd4d\n"
    ".global ReadBattleScreenBounds\n.thumb_set ReadBattleScreenBounds,0x0801cae1\n");
