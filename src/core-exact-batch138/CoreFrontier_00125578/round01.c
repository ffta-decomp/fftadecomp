typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct UnitRecordView { u8 prefix[40]; u16 flags; u8 remaining[222]; };
typedef char UnitStride[sizeof(struct UnitRecordView)==264?1:-1];
typedef char FlagsOffset[(u32)&(((struct UnitRecordView *)0)->flags)==40?1:-1];
extern struct UnitRecordView gUnitRecords[];
extern u8 *FindUnitPoolRecordById(u32 id);
extern u32 ResolveSceneUnitByEncodedId(u32 id);
u32 ResolveSceneCommandActor(u32 selector_argument)
{
    u32 selector = (u8)selector_argument;
    u32 result;
    struct UnitRecordView *record;
    s32 ordinal;
    if (selector != 255)
        goto explicit_selector;
    record = gUnitRecords;
    ordinal = 0;
    do {
        if ((record->flags & 0x400) != 0)
            goto found_record;
        ordinal++;
        record++;
    } while (ordinal <= 23);
    result = 0;
    goto done;
explicit_selector:
    if ((s32)(selector << 24) < 0)
        goto encoded_selector;
    result = (u32)FindUnitPoolRecordById(selector);
    goto done;
found_record:
    result = (u32)record;
    goto done;
encoded_selector:
    result = ResolveSceneUnitByEncodedId(selector);
done:
    return result;
}
asm(".global gUnitRecords\n.set gUnitRecords,0x02000080\n"
    ".global FindUnitPoolRecordById\n.thumb_set FindUnitPoolRecordById,0x080c83cd\n"
    ".global ResolveSceneUnitByEncodedId\n.thumb_set ResolveSceneUnitByEncodedId,0x08121cb5\n");
