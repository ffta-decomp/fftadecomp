/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
extern u8 BattleDependency_001339A8(int record_index, int state_index, u8 mask);
extern void SetIndexedUnitState(u8 *unit, u16 index, u8 value);

/* Original direct-call target; declaration only, no instructions. */
asm(".global BattleDependency_001339A8\n.thumb_set BattleDependency_001339A8, 0x081339a9");
void ClearUnitStatesFromDetailMask(int record_index, u8 *unit)
{
    int state_index;
    for (state_index = 0; state_index <= 43; state_index++) {
        if (BattleDependency_001339A8(record_index, state_index, 1))
            SetIndexedUnitState(unit, state_index, 0);
    }
}
