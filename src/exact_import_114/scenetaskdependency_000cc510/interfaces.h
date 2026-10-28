typedef unsigned char u8;
typedef unsigned short u16;
/* Paired byte stores support these tentative packed halfword fields. */
struct CollectionRecord {
    u16 field_00;
    u16 field_02;
    u8 preserved_metadata;
    u8 byte_05;
    u8 byte_06;
    u8 count;
    u16 field_08;
    u16 field_0a;
    u16 field_0c;
    u16 field_0e;
} __attribute__((packed));
struct CollectionSave {
    u8 unknown_prefix[0x2e78];
    struct CollectionRecord records[0];
};
typedef char CollectionRecordSize[(sizeof(struct CollectionRecord)==16)?1:-1];
extern struct CollectionSave gCollectionSave;
__asm__(".global gCollectionSave\n.set gCollectionSave,0x02000000");
