typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ContentUnitDefinitionBank {
    u16 count;
    u16 unknown_02;
    const void *records;
    u8 unknown_08[32];
};
struct ContentUnitRecord {
    u8 unknown_00[4];
    u8 occupied;
    u8 unknown_05[259];
};
struct PreparedUnit {
    u8 unknown_00[246];
    u8 x;
    u8 y;
    u8 unknown_f8;
    u8 initial_x;
    u8 initial_y;
};
struct PreparedUnitNode { struct PreparedUnit *unit; };
typedef char DefinitionBankSize[(sizeof(struct ContentUnitDefinitionBank)==40)?1:-1];
typedef char UnitRecordSize[(sizeof(struct ContentUnitRecord)==264)?1:-1];
extern const struct ContentUnitDefinitionBank ContentUnitDefinitionBanks[];
extern struct ContentUnitRecord ContentUnitPool[12];
extern u32 LoadContentUnitRecords(const struct ContentUnitDefinitionBank *bank, struct ContentUnitRecord *records, int maximum);
extern struct PreparedUnitNode *AppendContentUnit(u32 receiver, struct ContentUnitRecord *record);
__asm__(".global ContentUnitDefinitionBanks\n.set ContentUnitDefinitionBanks, 0x0854cd54\n"
        ".global ContentUnitPool\n.set ContentUnitPool, 0x02002fc4\n"
        ".thumb_set LoadContentUnitRecords, 0x080ca745\n"
        ".thumb_set AppendContentUnit, 0x08092441");
