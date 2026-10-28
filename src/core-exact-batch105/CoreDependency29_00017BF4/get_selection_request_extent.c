typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct SelectionExtentRequest {
    void *unknown;
    u8 *data;
    u8 unknown8[8];
    u8 flags;
} SelectionExtentRequest;
u16 GetSelectionRequestExtent(SelectionExtentRequest *request) __asm__("CoreDependency29_00017BF4");
u16 GetSelectionRequestExtent(SelectionExtentRequest *request)
{
    u8 *data = request->data;
    u8 extra;
    if (!data)
        return 0;
    if (request->flags & 8)
        extra = data[21] + 1;
    else
        extra = 0;
    return (u16)(((u32)request->data[19] + extra - 3) * 8);
}
