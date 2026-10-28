/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Unit {u8 gap[4];u8 active;u8 gap2[2];u8 job;u8 tail[256];};
extern struct Unit gUnits[];
extern u32 gClearRoutine;
extern u8 gContext[];
extern void ClearTrampoline(void *,int,u32);
extern int ReadProperty(u16,int);
extern void FillUnitIndices(u8,u8 *);
extern u8 CheckUnitMask(struct Unit *,int);
extern u8 Check8310(struct Unit *);
extern u8 Check82D8(struct Unit *);
extern u8 Check82F4(struct Unit *);
extern u8 ReadJobGroup(u8);

asm(".global gUnits\n.set gUnits,0x02000080\n.global gClearRoutine\n.set gClearRoutine,0x0836d4b8\n.global gContext\n.set gContext,0x020020d0\n.global ClearTrampoline\n.thumb_set ClearTrampoline,0x814224d\n.global ReadProperty\n.thumb_set ReadProperty,0x80ce4dd\n.global FillUnitIndices\n.thumb_set FillUnitIndices,0x8071dc9\n.global CheckUnitMask\n.thumb_set CheckUnitMask,0x80c8195\n.global Check8310\n.thumb_set Check8310,0x80c8311\n.global Check82D8\n.thumb_set Check82D8,0x80c82d9\n.global Check82F4\n.thumb_set Check82F4,0x80c82f5\n.global ReadJobGroup\n.thumb_set ReadJobGroup,0x80c93f1\n");
u8 CollectPropertyEligibleUnitPointers(u16 property_id, struct Unit **output, u8 *indices)
{
    int group;
    int count;
    int index;
    struct Unit *unit;
    ClearTrampoline(output,92,gClearRoutine);
    group = ReadProperty(property_id,48);
    FillUnitIndices(gContext[20],indices);
    count = 0;
    index = 0;
    do {
        if (indices[index] != 255) {
            unit = &gUnits[indices[index]];
            if (unit->active && !CheckUnitMask(unit,2) && !CheckUnitMask(unit,8) && !Check8310(unit) && !Check82D8(unit) && !Check82F4(unit)) {
                if (property_id && group && ReadJobGroup(unit->job) != group) goto next;
                output[count] = unit;
                count++;
            }
        }
next:
        index++;
    } while (index <= 23);
    return count;
}
