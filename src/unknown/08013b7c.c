typedef unsigned char u8;
typedef unsigned short u16;
struct SelectionControl;
struct SelectionBranchGateView {
    u8 unknown[12];
    union {
        u16 combined;
        struct {
            u8 first;
            u8 second;
        } bytes;
    } resource_tags;
};
extern void SetControlBranchResourceTags_08016E1C(struct SelectionControl *, u8 first, u8 second);
extern void BindControlBranchResource_08016E4C(struct SelectionControl *, u8 *data, u8 first);
__asm__(".global SetControlBranchResourceTags_08016E1C\n.thumb_set SetControlBranchResourceTags_08016E1C,0x08016e1d\n.global BindControlBranchResource_08016E4C\n.thumb_set BindControlBranchResource_08016E4C,0x08016e4d");
void ConfigureSelectionBranchResources(struct SelectionBranchGateView *gate,
    struct SelectionControl *control, u8 *data) __asm__("CoreFrontier_00013B7C");
void ConfigureSelectionBranchResources(struct SelectionBranchGateView *gate,
    struct SelectionControl *control, u8 *data)
{
    if (gate->resource_tags.combined != 0) {
        u8 *branch_data = data;
        /* Keep this real copy across configuration, with the original data
         * pointer retained separately for the second branch's +192 view. */
        __asm__("" : "+r"(branch_data));
        SetControlBranchResourceTags_08016E1C(control,
            gate->resource_tags.bytes.first, gate->resource_tags.bytes.second);
        if (gate->resource_tags.bytes.first != 0)
            BindControlBranchResource_08016E4C(control, branch_data, 1);
        if (gate->resource_tags.bytes.second != 0) {
            branch_data = data + 192;
            __asm__("" : "+r"(branch_data));
            BindControlBranchResource_08016E4C(control, branch_data, 0);
        }
    }
}
