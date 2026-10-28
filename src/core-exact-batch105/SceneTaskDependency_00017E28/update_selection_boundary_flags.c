typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef struct SelectionData {
    u8 unknown[26];
    s16 position;
} SelectionData;
typedef struct SelectionBoundaryRequest {
    void *unknown;
    SelectionData *data;
    u8 unknown8[8];
    u8 flags;
} SelectionBoundaryRequest;
extern u32 GetSelectionDataLength_08017B50(SelectionData *data);
extern s16 GetSelectionDataEnd_08017BE8(SelectionData *data);
__asm__(".global GetSelectionDataLength_08017B50\n.thumb_set GetSelectionDataLength_08017B50, 0x08017b51\n.global GetSelectionDataEnd_08017BE8\n.thumb_set GetSelectionDataEnd_08017BE8, 0x08017be9");
void UpdateSelectionBoundaryFlags(SelectionBoundaryRequest *request) __asm__("SceneTaskDependency_00017E28");
void UpdateSelectionBoundaryFlags(SelectionBoundaryRequest *request)
{
    u32 length;
    SelectionData *data;
    int end;
    if (request->data->position != 0)
        request->flags |= 4;
    else
        request->flags &= 251;
    length = GetSelectionDataLength_08017B50(request->data);
    data = request->data;
    end = data->position + (u16)length - 1;
    if (end == GetSelectionDataEnd_08017BE8(data))
        request->flags &= 247;
    else
        request->flags |= 8;
}
