/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct Record {void *unit;};
extern u32 ReadUnitField(const void *,u8);

asm(".global ReadUnitField\n.thumb_set ReadUnitField,0x80c7ea5");
int UnitRecordSpecialKindIsThree(struct Record *record)
{
    if (*(u8 *)ReadUnitField(record->unit,68)!=3)
        return 0;
    return 1;
}
