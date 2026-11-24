typedef signed char s8;
struct BattleUnit;
struct BattleActorRecord { struct BattleUnit *unit; };
/* Outgoing words retain the native signed-byte extension. The existing callee
 * consumes only their low bytes and returns a full signed terrain value. */
extern int ReadUnitCellPolicyFromSignedCoordinates(struct BattleUnit *unit,
                                                  int x, int y);
int ReadContentUnitCoordinateValue(struct BattleActorRecord *actor, int x, int y)
{
    struct BattleUnit *unit = actor->unit;
    int signed_x = (s8)x;
    int signed_y = (s8)y;
    return ReadUnitCellPolicyFromSignedCoordinates(unit, signed_x, signed_y);
}
asm(".global ReadUnitCellPolicyFromSignedCoordinates\n.thumb_set ReadUnitCellPolicyFromSignedCoordinates,0x08131BE1\n");
