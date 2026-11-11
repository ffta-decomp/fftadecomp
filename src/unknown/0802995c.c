#include "ffta/unsigned_types.h"
typedef signed char s8;
typedef signed int s32;

struct NativeRecordPreviewWindow {
    u8 unknown00[16];
    u8 x, y;
    u8 unknown18[98];
    void *pool, *owner, *record, *group;
    u8 pool_storage[4096];
    u8 render_mode, selector, overlay, layer;
    u8 animation_request, phase, span, vertical_offset;
};
typedef char PreviewPoolOffset[(u32)&((struct NativeRecordPreviewWindow *)0)->pool == 116 ? 1 : -1];
typedef char PreviewGroupOffset[(u32)&((struct NativeRecordPreviewWindow *)0)->group == 128 ? 1 : -1];
typedef char PreviewPhaseOffset[(u32)&((struct NativeRecordPreviewWindow *)0)->phase == 0x1089 ? 1 : -1];

extern u32 RefreshPreviewWindowFrame(void *);
extern void *InitializePreviewPool(void *, u32);
extern void *CreatePreviewOwner(void *, u16, u16, u16, u16);
extern void (*const ClearPreviewWord)(void *, u32);
extern void *CreatePreviewGroup(void *);
extern void RemovePreviewRecord(void *, void *);
extern void *CreatePreviewRecord(void *, u32, u32, u32, u32, u32, u32);
extern void UpdatePreviewFlags(void *, u16, u16);
extern void SetPreviewSequenceCursor(void *, u32);
extern void DrawPreviewQuantity(u8, u8, u8, u8);
extern void AdvancePreviewOwner(void *);
extern u16 ReadPreviewSelectorValue(u32);
extern void DrawPreviewRecord(void *, u32, u32, u32, u32, u32, u32, u32, u32, u32);
extern void DrawPreviewSpriteList(const u8 *, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32);
extern void SetPreviewWindowMode(void *, u32);
__asm__(".global RefreshPreviewWindowFrame\n.thumb_set RefreshPreviewWindowFrame,0x08017181\n"
        ".global InitializePreviewPool\n.thumb_set InitializePreviewPool,0x080070c9\n"
        ".global CreatePreviewOwner\n.thumb_set CreatePreviewOwner,0x08021a3d\n"
        ".global ClearPreviewWord\n.set ClearPreviewWord,0x0836d4b8\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
        ".global CreatePreviewGroup\n.thumb_set CreatePreviewGroup,0x08021b1d\n"
        ".global RemovePreviewRecord\n.thumb_set RemovePreviewRecord,0x08021bd5\n"
        ".global CreatePreviewRecord\n.thumb_set CreatePreviewRecord,0x08021619\n"
        ".global UpdatePreviewFlags\n.thumb_set UpdatePreviewFlags,0x08021df9\n"
        ".global SetPreviewSequenceCursor\n.thumb_set SetPreviewSequenceCursor,0x08021e29\n"
        ".global DrawPreviewQuantity\n.thumb_set DrawPreviewQuantity,0x08029d49\n"
        ".global AdvancePreviewOwner\n.thumb_set AdvancePreviewOwner,0x08021e7d\n"
        ".global ReadPreviewSelectorValue\n.thumb_set ReadPreviewSelectorValue,0x08021055\n"
        ".global DrawPreviewRecord\n.thumb_set DrawPreviewRecord,0x08021f19\n"
        ".global DrawPreviewSpriteList\n.thumb_set DrawPreviewSpriteList,0x08001f35\n"
        ".global SetPreviewWindowMode\n.thumb_set SetPreviewWindowMode,0x08017509");

u32 AdvanceNativeRecordPreviewWindow(struct NativeRecordPreviewWindow *)
    __asm__("SceneTaskDependency_0002995C");
u32 AdvanceNativeRecordPreviewWindow(struct NativeRecordPreviewWindow *window)
{
    switch (window->phase) {
    case 0: {
        void *pool;
        void *prior_record;
        void *created_record;
        void *group;
        void **group_address;
        u32 request;
        u8 *request_address;
        u8 vertical;

        if ((u8)RefreshPreviewWindowFrame(window) == 0)
            break;
        pool = InitializePreviewPool(window->pool_storage, 4096);
        window->pool = pool;
        window->owner = CreatePreviewOwner(pool, 704, 725, 0, 0);
        ClearPreviewWord(&window->record, 4);
        group = CreatePreviewGroup(window->owner);
        group_address = &window->group;
        *group_address = group;
        prior_record = window->record;
        if (prior_record != 0)
            RemovePreviewRecord(group, prior_record);
        created_record = CreatePreviewRecord(*group_address, 0, 0, 20,
            window->selector, window->overlay, 0);
        window->record = created_record;
        request_address = &window->animation_request;
        asm("" : "+r"(request_address));
        request = *request_address;
        if (request == 1) {
            UpdatePreviewFlags(*group_address, 0, 2);
            *request_address = 3;
        } else if (request == 0) {
            SetPreviewSequenceCursor(created_record, 1);
            UpdatePreviewFlags(*group_address, 2, 256);
            *request_address = 3;
        } else if (request == 4) {
            UpdatePreviewFlags(*group_address, 2, 1);
        }
        vertical = (u8)(window->vertical_offset - 7);
        DrawPreviewQuantity(window->x, (u8)(vertical + window->y),
            window->span, 13);
        window->phase = 1;
        *(u8 *)0x0200f43cU = 0;
        break;
    }
    case 1: {
        u8 *request_address = &window->animation_request;
        u32 request;
        register s32 vertical_delta __asm__("r1");
        s32 horizontal;
        s32 vertical;
        s32 scaled_row;
        s32 bias;
        s32 row;
        u8 *mode_address;
        u32 mode;
        u32 overlay;

        asm("" : "+r"(request_address));
        request = *request_address;
        if (request == 1) {
            UpdatePreviewFlags(window->group, 0, 2);
            *request_address = 3;
        } else if (request == 0) {
            SetPreviewSequenceCursor(window->record, 1);
            UpdatePreviewFlags(window->group, 2, 256);
            *request_address = 3;
        } else if (request == 4) {
            UpdatePreviewFlags(window->group, 2, 1);
        }
        AdvancePreviewOwner(window->owner);
        vertical_delta = window->vertical_offset;
        __asm__("" : "+r"(vertical_delta));
        vertical_delta -= 7;
        horizontal = window->x * 8 + 24;
        row = window->y;
        vertical_delta = (s8)vertical_delta;
        scaled_row = (row + vertical_delta) * 8;
        bias = vertical_delta * 4;
        bias -= 36;
        vertical = scaled_row - bias;
        mode_address = &window->render_mode;
        if (*mode_address == 2) {
            if (ReadPreviewSelectorValue(window->selector) == 16)
                DrawPreviewSpriteList((const u8 *)0x0839169c, horizontal,
                    vertical, 0, 0, 0, 1, 0, 0, 0, 0);
            else
                DrawPreviewSpriteList((const u8 *)0x083916aa, horizontal,
                    vertical, 0, 0, 0, 1, 0, 0, 0, 0);
        } else {
            DrawPreviewRecord(window->group, horizontal, vertical,
                0, 0, 0, 0, 0, window->layer, 0);
            mode = *mode_address;
            if (mode != 1)
                break;
            overlay = window->overlay;
            if (overlay == 0 || overlay == 12 || overlay == 16)
                break;
            if (ReadPreviewSelectorValue(window->selector) == 16)
                DrawPreviewSpriteList((const u8 *)0x0839169c, horizontal,
                    vertical, 0, 0, 0, mode, 0, 0, 0, 0);
            else
                DrawPreviewSpriteList((const u8 *)0x083916aa, horizontal,
                    vertical, 0, 0, 0, mode, 0, 0, 0, 0);
        }
        break;
    }
    case 2:
        SetPreviewWindowMode(window, 1);
        window->phase = 3;
        break;
    case 3:
        if ((u8)RefreshPreviewWindowFrame(window) != 0)
            window->phase = 4;
        break;
    case 4:
    default:
        break;
    }
    return window->phase;
}
