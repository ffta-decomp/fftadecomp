typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MenuLayoutRequest {
    u8 unknown_00[11];
    u8 flags_0b;
    u16 flags_0c;
    u8 unknown_0e[29];
    u8 mode_flags;
    u32 packed_layout;
    u32 payload;
    u8 unknown_34[6];
    u16 flags_3a;
    u8 unknown_3c[1816];
    const u8 *layout_record;
};
extern struct MenuLayoutRequest *volatile ActiveMenuLayout;
extern const u8 *GetIndexedGraphicsLayoutRecord(u8 entry_index);
void SetMenuLayoutRequest(u8, u8, u8, u32)
    __asm__("CoreFrontier_00013108");
void SetMenuLayoutRequest(u8 layout_id, u8 sub_id, u8 alternate, u32 payload)
{
    struct MenuLayoutRequest *initial_request = ActiveMenuLayout;
    struct MenuLayoutRequest *request;
    const u8 *record;
    initial_request->flags_3a &= 0xff7f;
    initial_request->packed_layout = (u32)layout_id << 8 | sub_id;
    initial_request->payload = payload;
    record = GetIndexedGraphicsLayoutRecord(layout_id);
    request = ActiveMenuLayout;
    request->layout_record = record;
    if (alternate != 0) {
        struct MenuLayoutRequest *next_mode;
        struct MenuLayoutRequest *enabled_request;
        request->mode_flags &= 0xfe;
        next_mode = ActiveMenuLayout;
        next_mode->mode_flags |= 2;
        enabled_request = ActiveMenuLayout;
        enabled_request->flags_0c |= 16;
        enabled_request->flags_0b |= 2;
    } else {
        struct MenuLayoutRequest *next_mode;
        struct MenuLayoutRequest *disabled_request;
        request->mode_flags &= 0xfd;
        next_mode = ActiveMenuLayout;
        next_mode->mode_flags |= 1;
        disabled_request = ActiveMenuLayout;
        disabled_request->flags_0c &= 0xffef;
        disabled_request->flags_0b &= 0xfd;
    }
}
__asm__(".global ActiveMenuLayout\n.set ActiveMenuLayout,0x0200918C\n"
        ".global GetIndexedGraphicsLayoutRecord\n.thumb_set GetIndexedGraphicsLayoutRecord,0x080CB969\n");
