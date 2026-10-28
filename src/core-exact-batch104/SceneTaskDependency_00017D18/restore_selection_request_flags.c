typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct SelectionRequest {
    void *unknown;
    u8 *data;
    u16 width, height, reset, unknown14;
    u8 flags, unknown17, phase;
} SelectionRequest;
extern u32 GetRequestExtent_08017BF4(SelectionRequest *request);
__asm__(".global GetRequestExtent_08017BF4\n.thumb_set GetRequestExtent_08017BF4, 0x08017bf5");
void RestoreSelectionRequestFlags(SelectionRequest *request, u8 flags) __asm__("SceneTaskDependency_00017D18");
void RestoreSelectionRequestFlags(SelectionRequest *request, u8 flags)
{
    u32 old_kind = request->flags & 6;
    u8 old_eight = request->flags & 8;
    request->flags = flags;
    if (!(old_kind & flags) && request->data) {
        if ((flags & 1) && (old_eight & 8))
            request->flags = flags | 8;
        if ((old_kind & 4) || (flags & 4)) {
            request->phase = 0;
            request->reset = 0;
        } else {
            request->width = GetRequestExtent_08017BF4(request) + 8;
            request->height = request->data[20] * 8 + 4;
            request->phase = 17;
        }
    }
    if (request->flags & 1) {
        if (old_kind & 4)
            request->flags |= 4;
        if (old_eight)
            request->flags |= 8;
    }
}
