typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct NativeTextAttachmentContext {
    u8 unknown00[8];
    u8 active;
    u8 unknown09[3];
    u16 control;
    u8 unknown14[34];
    u32 phase;
    u8 unknown52[6];
    u16 status;
    s16 x,y;
    u8 unknown64[0x754-64];
    const u8 *resolved_reference;
};
extern struct NativeTextAttachmentContext *gNativeTextAttachmentContext;
extern void DrawNativeTextAttachment(const u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
__asm__(".global gNativeTextAttachmentContext\n.set gNativeTextAttachmentContext,0x0200918C\n"
        ".global DrawNativeTextAttachment\n.thumb_set DrawNativeTextAttachment,0x08001F35\n");
void DrawActiveNativeTextAttachment(void) __asm__("SceneRegisteredRoot_00011C60");
void DrawActiveNativeTextAttachment(void)
{
    struct NativeTextAttachmentContext *context = gNativeTextAttachmentContext;
    if (context != 0 && context->active > 1 && (context->status & 0x100)) {
        const u8 *reference = context->resolved_reference;
        if (reference != 0)
            DrawNativeTextAttachment(reference,context->x,context->y,0,
                                     0,1,1u & ~(context->control >> 4),0,
                                     context->phase >> 5,0,0);
    }
}
