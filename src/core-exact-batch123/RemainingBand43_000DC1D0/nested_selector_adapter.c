typedef unsigned char u8;
typedef unsigned int u32;

extern void *GetRecordNestedPointer(void *record);
extern u32 ExistingNestedSelectorQuery(u32 selector, void *nested_pointer);

__asm__(".global GetRecordNestedPointer\n.thumb_set GetRecordNestedPointer,0x080DD47D\n"
        ".global ExistingNestedSelectorQuery\n.thumb_set ExistingNestedSelectorQuery,0x080DB945");

u32 RemainingBand43_000DC1D0(void *record)
{
    void *nested_pointer = GetRecordNestedPointer(record);
    return (u8)ExistingNestedSelectorQuery(6, nested_pointer);
}
