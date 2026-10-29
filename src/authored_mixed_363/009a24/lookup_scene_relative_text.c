typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern const u32 SceneRelativeBook[];
extern u8 EwramSceneState[];
extern u8 *LookupSceneScriptRecord(u32);
extern u32 UnsignedRemainder(u32, u32);
__asm__(".global EwramSceneState\n.set EwramSceneState,0x02000000\n.global SceneRelativeBook\n.set SceneRelativeBook,0x089c1484\n"
        ".global LookupSceneScriptRecord\n.thumb_set LookupSceneScriptRecord,0x08009a15\n"
        ".global UnsignedRemainder\n.thumb_set UnsignedRemainder,0x08142ab1");
static inline u16 CurrentSceneRecordId(void)
{
    register u32 root __asm__("r0") = (u32)EwramSceneState;
    register u32 offset __asm__("r1") = 0x2192;
    __asm__("" : "+r"(root), "+r"(offset));
    return *(u16 *)(root + offset);
}
static inline u32 CurrentScenePageCounter(void)
{
    register u32 root __asm__("r0") = (u32)EwramSceneState;
    register u32 offset __asm__("r1") = 0x3C2A;
    __asm__("" : "+r"(root), "+r"(offset));
    return *(u8 *)(root + offset);
}
const u8 *LookupSceneRelativeText(u32 incoming) __asm__("Remaining38_00009A24");
const u8 *LookupSceneRelativeText(u32 incoming)
{
    register u32 selector __asm__("r5") = (u16)incoming;
    const u8 *record;
    u32 page;
    register u32 page_byte_offset __asm__("r0");
    register const u32 *book __asm__("r6");
    const u8 *text;
    __asm__("" : "+r"(selector));
    if (selector > 239)
        record = LookupSceneScriptRecord(170);
    else
        record = LookupSceneScriptRecord(CurrentSceneRecordId());
    page = record[2];
    page_byte_offset = page << 2;
    __asm__("" : "+r"(page_byte_offset));
    book = SceneRelativeBook;
    __asm__("" : "+r"(book));
    text = (const u8 *)(*(const u32 *)(page_byte_offset + (u32)book) + (u32)book);
    if (selector <= 239 && page == 61) {
        u32 counter = CurrentScenePageCounter();
        u32 child;
        register u32 child_address __asm__("r0");
        if (counter != 0)
            counter = (u8)(counter - 1);
        child = (u8)UnsignedRemainder(counter, 10);
        child_address = child * 4;
        __asm__(".Lw4_09a24_child_add_begin:\n\tadd %0,%1,%0\n.Lw4_09a24_child_add_end:"
                : "+l"(child_address) : "l"((u32)text) : "cc");
        text = (const u8 *)(*(const u32 *)child_address + (u32)book);
    }
    return text;
}
