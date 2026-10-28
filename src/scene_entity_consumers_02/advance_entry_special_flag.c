/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EntryData { u8 prefix; u8 selector; u8 gap[4]; u16 id; };
struct EntryContext { struct EntryData *data; u8 rest[100]; u8 first[20]; u8 second[20]; };
extern u16 PrepareEntry(struct EntryContext *context);
extern void ApplyEntrySelector(u8 *first, u8 selector);
extern void RefreshEntry(u8 *second);
extern void SetGameFlag(u32 id, u8 value);

asm(".global PrepareEntry\n.thumb_set PrepareEntry,0x08011861\n.global ApplyEntrySelector\n.thumb_set ApplyEntrySelector,0x08017d19\n.global RefreshEntry\n.thumb_set RefreshEntry,0x08017e29");
static inline void EnableEntry(u8 *entry)
{
    if (entry) {
        entry[16] &= 191;
        RefreshEntry(entry);
    }
}
u32 AdvanceSceneEntryAndSpecialFlag(struct EntryContext *context)
{
    u8 *first = context->first;
    u8 *second = context->second;
    if (!PrepareEntry(context))
        return 0;
    ApplyEntrySelector(first, context->data->selector);
    EnableEntry(second);
    if (context->data->id == 0x479)
        SetGameFlag(0x581, 1);
    return 1;
}
