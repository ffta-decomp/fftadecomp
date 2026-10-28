typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Decimal(u8 *, u32, u32);
extern void Labeled(u8 *, u32, u32);
extern void Split(u8 *, u32, u32, u32, u32);
extern void QueryCounts(u8 *, u8 *, u16 *, u16 *);
extern void Indicators(u8 *);
extern void TemplateCopy(u32, u32);
extern void *NextRequest(void);
extern void QueueCopy32(void *, const void *, void *, u16);
extern void QueueFill32(void *, u32, void *, u16);
__asm__(".global Decimal\n.thumb_set Decimal, 0x0802BC7D\n.global Labeled\n.thumb_set Labeled, 0x0802BD91\n.global Split\n.thumb_set Split, 0x0802BEB1\n.global QueryCounts\n.thumb_set QueryCounts, 0x0802BA41\n.global Indicators\n.thumb_set Indicators, 0x0802BE41\n.global TemplateCopy\n.thumb_set TemplateCopy, 0x0802C009\n.global NextRequest\n.thumb_set NextRequest, 0x0802BA09\n.global QueueCopy32\n.thumb_set QueueCopy32, 0x08000ADD\n.global QueueFill32\n.thumb_set QueueFill32, 0x08000B69");
void TaskConstructor45_0002C270(u8 *view)
{
    register u32 guard_word __asm__("r1") = *(u16 *)(view + 16);
    register u32 guard_mask __asm__("r0");
    register u32 suppressed __asm__("r6");
    u16 current;
    u16 total;
    /* Preserve the original halfword-read, masked-left-shift and normalization. */
    __asm__("" : : "r"(guard_word));
    guard_mask = 16;
    __asm__("" : : "r"(guard_mask));
    guard_mask = (guard_mask & guard_word) << 16;
    __asm__("" : "+r"(guard_mask));
    suppressed = guard_mask >> 16;
    __asm__("" : "+r"(suppressed));
    if (suppressed != 0)
        return;
    Decimal(view + 1000, *(u16 *)(*(u8 **)(view + 12) + 214), 608);
    QueryCounts(view, *(u8 **)(view + 12), &current, &total);
    Labeled(view + 1128, current, 928);
    Decimal(view + 1192, total, 1216);
    {
    register u8 *mode_base __asm__("r0") = (u8 *)0x020020D0;
    /* Preserve the original base-plus-byte-offset phase and literal identity. */
    __asm__("" : "+r"(mode_base));
    if (mode_base[181] == 0) {
        void *request = NextRequest();
        u8 *context = *(u8 **)0x0200F440;
        QueueCopy32(request, context + 0xBDC, (void *)0x060139C0, 16);
        {
            register u32 tile_offset __asm__("r2") = 1024;
            /* This site's third argument is constructed before its first two. */
            __asm__("" : : "r"(tile_offset));
            Decimal(view + 1064, (*(u8 **)(view + 12))[9], tile_offset);
        }
        QueueFill32(NextRequest(), 0, (void *)0x060139A0, 8);
        QueueFill32(NextRequest(), 0, (void *)0x06013AA0, 24);
        QueueFill32(NextRequest(), 0, (void *)0x06013D40, 8);
    } else {
        TemplateCopy(992, 160);
        TemplateCopy(992, 416);
        Split(view + 1256, *(u16 *)(*(u8 **)(view + 12) + 26), 192, 1024, suppressed);
        {
            register u8 *target __asm__("r0") = view + 1384;
            register u32 value __asm__("r1") = *(u16 *)(*(u8 **)(view + 12) + 30);
            register u32 first_offset __asm__("r2") = 448;
            register u32 compact __asm__("r3") = 1;
            /* Preserve the true fifth argument until its outgoing stack store. */
            __asm__("" : : "r"(target), "r"(value), "r"(first_offset), "r"(compact));
            Split(target, value, first_offset, 1088, compact);
        }
    }
    }
    Indicators(*(u8 **)(view + 12));
}
