struct ContentUnitRecord;
typedef int (*ContentUnitVisitor)(struct ContentUnitRecord *record,
                                  struct ContentUnitRecord **selected);
extern int SelectUnitWithField27Bit12(struct ContentUnitRecord *record,
                                     struct ContentUnitRecord **selected);
extern void VisitContextUnitRecords(void *context, ContentUnitVisitor visitor,
                                    struct ContentUnitRecord **selected);
/* Existing traversal stops on the unchanged unit-flag predicate callback. */
struct ContentUnitRecord *FindContentEntryWithUnitFlag12(void *context)
{
    struct ContentUnitRecord *selected = 0;
    VisitContextUnitRecords(context, SelectUnitWithField27Bit12, &selected);
    return selected;
}
asm(".global SelectUnitWithField27Bit12\n.thumb_set SelectUnitWithField27Bit12,0x0809AB3D\n"
    ".global VisitContextUnitRecords\n.thumb_set VisitContextUnitRecords,0x08099841\n");
