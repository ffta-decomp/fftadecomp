typedef unsigned char u8;
struct ControlResourceTagsView {
    u8 unknown[28];
    u8 flags;
    u8 first_tag;
    u8 second_tag;
};
void SetControlBranchResourceTags(struct ControlResourceTagsView *control,
    u8 first_tag, u8 second_tag) __asm__("CoreFrontier_00016E1C");
void SetControlBranchResourceTags(struct ControlResourceTagsView *control,
    u8 first_tag, u8 second_tag)
{
    if (first_tag == 0 && second_tag == 0) {
        control->flags &= 0xfd;
    } else {
        control->flags |= 2;
        control->first_tag = first_tag;
        control->second_tag = second_tag;
    }
}
