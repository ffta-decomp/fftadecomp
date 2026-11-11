typedef unsigned int u32;
typedef unsigned short u16;
struct CoordinateAdvanceRecord { u32 words[2]; u16 step; u16 offset_x; u16 offset_y; u16 limit; };
extern u32 AdvanceCoordinateRecord(struct CoordinateAdvanceRecord *record);
__asm__(".global AdvanceCoordinateRecord\n.thumb_set AdvanceCoordinateRecord,0x0809fdc1");
u32 ConfigureAndAdvanceGlobalCoordinates(const u32 *pair, u32 step, u32 limit, u32 offset_x, u32 offset_y) __asm__("BattleStateDependency_000A83A4");
u32 ConfigureAndAdvanceGlobalCoordinates(const u32 *pair, u32 step, u32 limit, u32 offset_x, u32 offset_y)
{
    struct CoordinateAdvanceRecord *record = (struct CoordinateAdvanceRecord *)0x0200f898;
    if (pair != 0) {
        u32 second = pair[1];
        u32 first = pair[0];
        record->words[0] = first;
        record->words[1] = second;
    }
    /* The original keeps record in r2 for the call and uses r1 for field stores.
     * This defined-value alias constraint emits no instructions itself. */
    {
    register struct CoordinateAdvanceRecord *fields __asm__("r1") = record;
    __asm__("" : "+r"(fields));
    fields->offset_x = offset_x;
    fields->offset_y = offset_y;
    if (step != 0)
        fields->step = step;
    if (limit != 0)
        fields->limit = limit;
    }
    return AdvanceCoordinateRecord(record);
}
