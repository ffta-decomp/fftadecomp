/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Record {void *unit;};
extern void * GetContentContext(void);
extern int CollectRecords(void *,struct Record **);
extern u8 Check8240(void *);
extern u8 Check8260(void *);
extern u8 Check8298(void *);
extern int ReadUnitValue(void *,int);
extern u8 CheckD92C(void *);
extern u8 CheckD95C(void *);
extern u8 CheckD9A4(void *);
extern u8 CheckD9BC(void *);

asm(".global GetContentContext\n.thumb_set GetContentContext,0x8096d7d\n.global CollectRecords\n.thumb_set CollectRecords,0x8099cdd\n.global Check8240\n.thumb_set Check8240,0x80c8241\n.global Check8260\n.thumb_set Check8260,0x80c8261\n.global Check8298\n.thumb_set Check8298,0x80c8299\n.global ReadUnitValue\n.thumb_set ReadUnitValue,0x80c7ea5\n.global CheckD92C\n.thumb_set CheckD92C,0x80cd92d\n.global CheckD95C\n.thumb_set CheckD95C,0x80cd95d\n.global CheckD9A4\n.thumb_set CheckD9A4,0x80cd9a5\n.global CheckD9BC\n.thumb_set CheckD9BC,0x80cd9bd\n");
unsigned int BranchWhenNoUnexcludedUnitRemains(u16 *position,u8 *command)
{
    struct Record *records[13];
    int count = CollectRecords(GetContentContext(),records);
    int index = 0;
    struct Record *record;
    int value;
    for (; index < count; index++) {
        record = records[index];
        if (Check8240(record->unit)) continue;
        if (Check8260(record->unit)) continue;
        if (Check8298(record->unit)) continue;
        value = ReadUnitValue(record->unit,1);
        if (value == 94) continue;
        if (value == 10) continue;
        if (value == 9) continue;
        if (value == 4) continue;
        if (value == 12) continue;
        if (CheckD92C(record->unit)) continue;
        if (CheckD95C(record->unit)) continue;
        if (CheckD9A4(record->unit)) continue;
        if (!CheckD9BC(record->unit)) return 272;
    }
    *position += command[1] | command[2] << 8;
    return 272;
}
