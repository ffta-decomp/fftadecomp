/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct UnitCandidateView { u8 *unit; u8 unknown04[88]; s16 value; };
struct UnitCategoryView { u8 unknown00[260]; u8 category; };
extern s32 RetailCall_08099cdc(u32,struct UnitCandidateView **);
extern u32 RetailCall_080cdca4(const u8 *);
extern u32 RetailCall_080ce410(const u8 *);
extern u32 RetailCall_0812e4a8(const u8 *);
asm(".global RetailCall_08099cdc\n.thumb_set RetailCall_08099cdc,0x08099cdd\n.global RetailCall_080cdca4\n.thumb_set RetailCall_080cdca4,0x080cdca5\n.global RetailCall_080ce410\n.thumb_set RetailCall_080ce410,0x080ce411\n.global RetailCall_0812e4a8\n.thumb_set RetailCall_0812e4a8,0x0812e4a9");

struct UnitCandidateView *FindLowestEligibleUnitRecord(u32 selector,const struct UnitCategoryView *target)
{
    struct UnitCandidateView *records[13];
    s32 count=RetailCall_08099cdc(selector,records);
    struct UnitCandidateView *best=0;
    s32 best_value=1024;
    s32 index;
    for(index=0;index<count;index++) {
        const u8 *category=&target->category;
        {
            if (records[index]->value < best_value &&
                (u8)RetailCall_080cdca4(records[index]->unit) &&
                *category == (u8)RetailCall_080ce410(records[index]->unit) &&
                (u8)RetailCall_0812e4a8(records[index]->unit)) {
                best_value=records[index]->value;
                best=records[index];
            }
        }
    }
    return best;
}
