typedef unsigned char u8;
typedef signed short s16;
struct TaskGroup;
struct ManagedResultRecord {
    s16 result;
    u8 ready;
    u8 unknown_before_20[29];
    struct TaskGroup *group;
};
extern void RunTaskTree(struct TaskGroup *group);
__asm__(".global RunTaskTree\n.thumb_set RunTaskTree, 0x08005a25");

int ServiceManagedRecordResult(void) __asm__("CoreFrontier_00025464");
int ServiceManagedRecordResult(void)
{
    struct ManagedResultRecord **slot = (struct ManagedResultRecord **)0x0200f438;
    if (*slot == 0 || (*slot)->group == 0)
        return -1;
    RunTaskTree((*slot)->group);
    if ((*slot)->ready != 0) {
        (*slot)->ready = 0;
        /* The byte store may alias globally visible pointer storage. */
        return (*slot)->result;
    }
    return 0;
}
