typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ControlResourceRouteView {
    u8 unknown_00[20];
    u16 format_flags;
    u8 unknown_22[7];
    u8 first_tag;
    u8 second_tag;
};
extern u8 BuildControlResourceTiles_08018524(u8 *data, u16 base_tile, u8 resource_tag);
__asm__(".global BuildControlResourceTiles_08018524\n.thumb_set BuildControlResourceTiles_08018524,0x08018525");
void BindControlBranchResource(struct ControlResourceRouteView *control,
    u8 *data, u8 first) __asm__("CoreFrontier_00016E4C");
void BindControlBranchResource(struct ControlResourceRouteView *control,
    u8 *data, u8 first)
{
    u32 resource_tag;
    u32 base_tile;
    register u8 *data_argument __asm__("r0");
    if (first != 0) {
        resource_tag = control->first_tag & 127;
        base_tile = 62;
    } else {
        resource_tag = control->second_tag & 127;
        base_tile = 68;
    }
    if (control->format_flags & 0x0800)
        base_tile = 74;
    data_argument = data;
    /* The native call prepares the actual R0 pointer before R1's tile base. */
    __asm__("" : "+r"(data_argument));
    BuildControlResourceTiles_08018524(data_argument, base_tile, resource_tag);
}
