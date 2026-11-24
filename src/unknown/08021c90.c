typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct Owner { void *pool; void *groups, *records; u16 lower, upper, alternate_lower, alternate_upper; };
extern s32 FindOwnerRecordRange(struct Owner *, s32 width, s32 lower, s32 upper);
__asm__(".global FindOwnerRecordRange\n.thumb_set FindOwnerRecordRange,0x080213dd");
s32 SelectOwnerRecordRange(struct Owner *owner, u32 alternate, s32 width)
{
    u32 lower, upper;
    if (alternate == 0) {
        lower = owner->lower;
        upper = owner->upper;
    } else {
        lower = owner->alternate_lower;
        upper = owner->alternate_upper;
    }
    return FindOwnerRecordRange(owner, width, lower, upper);
}
