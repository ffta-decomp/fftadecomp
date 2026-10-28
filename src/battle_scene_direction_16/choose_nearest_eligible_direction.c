/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct CoordinateUnit {
    u8 prefix[246];
    u8 x;
    u8 y;
} CoordinateUnit;
typedef struct UnitNode {
    CoordinateUnit *unit;
} UnitNode;
typedef struct CandidateRecord {
    UnitNode *node;
    u8 unknown[804];
} CandidateRecord;
typedef struct CandidateContext {
    CandidateRecord records[13];
    u16 count;
} CandidateContext;
#define OFFSET(T,M) ((u32)&(((T*)0)->M))
typedef char RecordStride[sizeof(CandidateRecord)==808?1:-1];
typedef char ContextCountOffset[OFFSET(CandidateContext,count)==0x2908?1:-1];
typedef char UnitXOffset[OFFSET(CoordinateUnit,x)==246?1:-1];
typedef char UnitYOffset[OFFSET(CoordinateUnit,y)==247?1:-1];
extern u32 NextRandom(void);
extern u32 ExcludedUnitStateA(const CoordinateUnit *);
extern u32 ExcludedUnitStateB(const CoordinateUnit *);
extern u32 DirectionFromDeltas(s8,s8);
__asm__(".global NextRandom\n.thumb_set NextRandom, 0x08002805");
__asm__(".global ExcludedUnitStateA\n.thumb_set ExcludedUnitStateA, 0x080c8281");
__asm__(".global ExcludedUnitStateB\n.thumb_set ExcludedUnitStateB, 0x080cd92d");
__asm__(".global DirectionFromDeltas\n.thumb_set DirectionFromDeltas, 0x0809d6bd");


/* Select a direction toward the first strictly nearest eligible candidate.
 * Unit coordinates are unsigned bytes; the incoming coordinate bytes are signed
 * only at their uses. Predicate calls may replace each record's node or unit. */
s8 ChooseNearestEligibleUnitDirection(CandidateContext *context, UnitNode *excluded, u8 x, u8 y)
{
    u8 direction = (s16)NextRandom() % 4;
    int minimum_distance = 4096;
    int index;
    int delta_x;
    int delta_y;
    int absolute_x;
    int absolute_y;
    CandidateRecord *record;
    CoordinateUnit *unit;
    for (index = 0; index < context->count; index++) {
        record = &context->records[index];
        if (record->node != excluded) {
            if ((u8)ExcludedUnitStateA(record->node->unit) == 0) {
                if ((u8)ExcludedUnitStateB(record->node->unit) == 0) {
                    unit = record->node->unit;
                    delta_x = unit->x - (s8)x;
                    absolute_x = delta_x;
                    if (absolute_x < 0)
                        absolute_x = -absolute_x;
                    delta_y = unit->y - (s8)y;
                    absolute_y = delta_y;
                    if (absolute_y < 0)
                        absolute_y = -absolute_y;
                    if (absolute_x + absolute_y < minimum_distance) {
                        minimum_distance = absolute_x + absolute_y;
                        direction = DirectionFromDeltas(delta_x, delta_y);
                    }
                }
            }
        }
    }
    return direction;
}
