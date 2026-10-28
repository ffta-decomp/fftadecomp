#include "../../../src/task_tree_core.h"
typedef signed short s16;
typedef signed int s32;
struct BattleMovementView {
    void *object;
    u8 mode;
    u8 unknown_05[7];
    u16 cell_x;
    u16 unknown_0e;
    u16 cell_y;
    u16 unknown_12;
    u16 previous_x;
    u16 unknown_16;
    u16 previous_y;
    u8 unknown_1a[14];
};
typedef char BattleMovementViewMustBe40Bytes[sizeof(struct BattleMovementView)==40?1:-1];
extern u8 ReadDefinitionReadiness(void);
extern u8 ReadMapCellPrimaryByte(u8, u8);
extern void ProjectBattlePoint(s16, s16, s16, u16 *, u16 *, u16 *);
extern void ReadCurrentCoordinates(u16 *, u16 *);
extern void SetCurrentCoordinates(s32, s16);
extern void SnapBattleMovementView(struct BattleMovementView *);
extern void DrawBattleMovementView(struct BattleMovementView *);
extern s32 DivideSigned(s32, s32);

void ProcessBattleMovementView(struct BattleMovementView *record)
{
    s16 projected_x;
    s16 projected_y;
    s16 projected_depth;
    s16 current_x;
    s16 current_y;
    u32 mode = record->mode;
    if (mode == 0)
        return;
    if (mode == 3)
        return;
    if (mode == 4) {
        DrawBattleMovementView(record);
        return;
    }
    if (mode == 2 || record->previous_x == 0xffff || record->previous_y == 0xffff) {
        SnapBattleMovementView(record);
        return;
    }
    if (ReadDefinitionReadiness() == 0) {
        u16 target_x;
        u16 target_y;
        s32 delta_x;
        s32 delta_y;
        projected_x = (record->cell_x << 5) + 16;
        projected_depth = (record->cell_y << 5) + 16;
        projected_y = ReadMapCellPrimaryByte((u8)record->cell_x, (u8)record->cell_y) << 4;
        ProjectBattlePoint(projected_x, projected_y, projected_depth,
                          (u16 *)&projected_x, (u16 *)&projected_y, (u16 *)&projected_depth);
        ReadCurrentCoordinates((u16 *)&current_x, (u16 *)&current_y);
        target_x = (u16)current_x;
        target_y = (u16)current_y;
        if (projected_x < current_x + 48)
            target_x = (u16)projected_x - 48;
        else if (projected_x > current_x + 192)
            target_x = (u16)projected_x - 192;
        if (projected_y < current_y + 56)
            target_y = (u16)projected_y - 56;
        else if (projected_y > current_y + 104)
            target_y = (u16)projected_y - 104;
        delta_x = (s16)target_x - current_x;
        delta_y = (s16)target_y - current_y;
        if (delta_x != 0 || delta_y != 0) {
            s32 step_x = delta_x / 8;
            s32 step_y = delta_y / 8;
            if (delta_x != 0 && step_x == 0) {
                s32 magnitude = delta_x;
                if (magnitude < 0)
                    magnitude = -magnitude;
                step_x = DivideSigned(delta_x, magnitude);
            }
            if (delta_y != 0 && step_y == 0) {
                s32 magnitude = delta_y;
                if (magnitude < 0)
                    magnitude = -magnitude;
                step_y = DivideSigned(delta_y, magnitude);
            }
            target_x = (u16)current_x + step_x;
            target_y = (u16)current_y + step_y;
        }
        if ((s16)target_x != current_x || (s16)target_y != current_y)
            SetCurrentCoordinates((s16)target_x, (s16)target_y);
    }
    DrawBattleMovementView(record);
}
asm(".global ReadDefinitionReadiness\n.thumb_set ReadDefinitionReadiness,0x0801bdb1\n"
    ".global ReadMapCellPrimaryByte\n.thumb_set ReadMapCellPrimaryByte,0x0801cc19\n"
    ".global ProjectBattlePoint\n.thumb_set ProjectBattlePoint,0x0801c919\n"
    ".global ReadCurrentCoordinates\n.thumb_set ReadCurrentCoordinates,0x0801e6f1\n"
    ".global SetCurrentCoordinates\n.thumb_set SetCurrentCoordinates,0x0801e5e1\n"
    ".global SnapBattleMovementView\n.thumb_set SnapBattleMovementView,0x08024a25\n"
    ".global DrawBattleMovementView\n.thumb_set DrawBattleMovementView,0x08025239\n"
    ".global DivideSigned\n.thumb_set DivideSigned,0x081426b9\n");
