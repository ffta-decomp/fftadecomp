typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

struct ProgressRecord {
    u8 unknown_before_0e[14];
    s16 position;
    s16 pending;
    u8 unknown_before_18[6];
    const u8 *encoded_limit;
    u8 unknown_at_1c;
    u8 active;
};

extern u32 GetListNodeWord(const void *node);
__asm__(".global GetListNodeWord\n.thumb_set GetListNodeWord, 0x080c7b75");

/* Record roles remain tentative. Returning zero stops the real list visitor. */
u32 QueryPendingRecord(const void *node, u32 *found)
    __asm__("CoreClosure31_000A95B0");
u32 QueryPendingRecord(const void *node, u32 *found)
{
    struct ProgressRecord *record = (struct ProgressRecord *)GetListNodeWord(node);
    if (record->active != 0) {
        int low_byte = record->encoded_limit[0];
        int limit = record->encoded_limit[1];
        limit = (limit << 8) | low_byte;
        if (limit > record->position || record->pending != 0) {
            *found = 1;
            return 0;
        }
    }
    return 1;
}
