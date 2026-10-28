#include "../../../src/task_tree_core.h"
typedef signed short s16;
union MovementCoordinateWord {
    u32 raw;
    struct { u16 value; u16 unknown_upper; } parts;
};
struct MovementPosition {
    union MovementCoordinateWord x;
    union MovementCoordinateWord y;
};
struct BattleMovementSnapshot {
    void *object;
    u8 mode;
    u8 unknown_05[7];
    struct MovementPosition position;
    struct MovementPosition previous;
    u8 unknown_1c[12];
};
typedef char BattleMovementSnapshotMustBe40Bytes[sizeof(struct BattleMovementSnapshot)==40?1:-1];
extern u8 ReadDefinitionReadiness(void);
extern u8 ReadMapCellPrimaryByte(u8, u8);
extern void ProjectBattlePoint(s16, s16, s16, u16 *, u16 *, u16 *);
extern void GetRelativeBattleCoordinates(s16, s16, u16 *, u16 *);
extern u32 StartBattleCameraMovement(s16, s16);
extern void DrawBattleMovementView(struct BattleMovementSnapshot *);

void SnapshotBattleMovementCoordinates(struct BattleMovementSnapshot *record)
{
    s16 projected_x;
    s16 projected_y;
    s16 projected_depth;
    if (ReadDefinitionReadiness() == 0) {
        projected_x = (record->position.x.parts.value << 5) + 16;
        projected_depth = (record->position.y.parts.value << 5) + 16;
        projected_y = ReadMapCellPrimaryByte((u8)record->position.x.parts.value,
                                           (u8)record->position.y.parts.value) << 4;
        ProjectBattlePoint(projected_x, projected_y, projected_depth,
                          (u16 *)&projected_x, (u16 *)&projected_y, (u16 *)&projected_depth);
        GetRelativeBattleCoordinates(projected_x, projected_y,
                                     (u16 *)&projected_x, (u16 *)&projected_y);
        StartBattleCameraMovement((s16)((u16)projected_x - 120),
                                 (s16)((u16)projected_y - 96));
        /* Both complete coordinate words, including upper halves, are snapshotted. */
        record->previous = record->position;
        if (record->mode == 4)
            DrawBattleMovementView(record);
    }
}
asm(".global ReadDefinitionReadiness\n.thumb_set ReadDefinitionReadiness,0x0801bdb1\n"
    ".global ReadMapCellPrimaryByte\n.thumb_set ReadMapCellPrimaryByte,0x0801cc19\n"
    ".global ProjectBattlePoint\n.thumb_set ProjectBattlePoint,0x0801c919\n"
    ".global GetRelativeBattleCoordinates\n.thumb_set GetRelativeBattleCoordinates,0x0801c961\n"
    ".global StartBattleCameraMovement\n.thumb_set StartBattleCameraMovement,0x0801b939\n"
    ".global DrawBattleMovementView\n.thumb_set DrawBattleMovementView,0x08025239\n");
