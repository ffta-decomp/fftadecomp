/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
extern u8 BattleDependency_001339CC(int record_index, int state_index, u8 mask);
extern void SetIndexedUnitState(u8 *unit, u16 index, u8 value);

/* Verified original direct target; declaration only. */
asm(".global BattleDependency_001339CC\n.thumb_set BattleDependency_001339CC, 0x081339cd");
void ClearUnitStatesFromAlternateMask(u8 *unit, int record_index)
{
    int state_index;
    for (state_index = 0; state_index <= 43; state_index++) {
        if (BattleDependency_001339CC(record_index, state_index, 1))
            SetIndexedUnitState(unit, state_index, 0);
    }
}
