typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct __attribute__((packed)) SavedCollectionRecord {
    u32 presence_word;
    u8 remaining_data[12];
};
typedef char SavedCollectionStride[(sizeof(struct SavedCollectionRecord) == 16) ? 1 : -1];
extern struct SavedCollectionRecord gProgressCollectionRecords[20];
__asm__(".global gProgressCollectionRecords\n.set gProgressCollectionRecords,0x02002e78");
