/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct UnitRecord { u8 bytes[264]; };
extern struct UnitRecord gUnitPoolB[];
extern const u8 gUnitSelectionState[];
extern void ReadUnitIndices(u8 selector, u8 *indices);
extern u32 ReadUnitField(const void *unit, u8 selector);

asm(".global gUnitSelectionState\n.set gUnitSelectionState,0x020020d0\n.global ReadUnitIndices\n.thumb_set ReadUnitIndices,0x08071dc9");
int CollectPolicyEligibleUnitPointers(struct UnitRecord **output)
{
    u8 indices[24];
    int count;
    int index;
    struct UnitRecord **cursor;
    ReadUnitIndices(gUnitSelectionState[20], indices);
    count = 0;
    index = 0;
    cursor = output;
    for (; index <= 23; index++) {
        if (indices[index] != 255) {
            struct UnitRecord *unit = &gUnitPoolB[indices[index]];
            u8 kind = ReadUnitField(unit, 1);
            if (!unit || (kind != 2 && kind != 8 && kind != 94 && kind != 10 && kind != 4 && kind != 9 && kind != 12)) {
                if (output)
                    *cursor = unit;
                cursor++;
                count++;
            }
        }
    }
    return count;
}
