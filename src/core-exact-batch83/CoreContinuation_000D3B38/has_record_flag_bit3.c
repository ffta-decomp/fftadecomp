typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct RecordFlags {
    u8 unknown_before_04[4];
    u16 flags;
};
extern struct RecordFlags *GetRecordIdentity(void *record);
__asm__(".global GetRecordIdentity\n.thumb_set GetRecordIdentity, 0x080a880d");

u32 HasRecordFlagBitThree(void *record) __asm__("CoreContinuation_000D3B38");
u32 HasRecordFlagBitThree(void *record)
{
    struct RecordFlags *fields = GetRecordIdentity(record);
    if ((fields->flags & 8) != 0)
        return 1;
    return 0;
}
