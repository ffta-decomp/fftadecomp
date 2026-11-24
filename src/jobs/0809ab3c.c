/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
struct Record {void *unit;};
extern int UnitField27HasBit12(const void *);

asm(".global UnitField27HasBit12\n.thumb_set UnitField27HasBit12,0x80c8299");
int ContentUnitSelectCallback(struct Record *record,struct Record **selected)
{
    int result;
    if ((u8)UnitField27HasBit12(record->unit)) {
        *selected=record;
        result=0;
    } else result=1;
    return result;
}
