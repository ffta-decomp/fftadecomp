typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 EwramSceneState[];
extern const u8 *LookupSceneScriptRecord(u32);
extern u32 UnsignedRemainder(u32,u32);
__asm__(".global EwramSceneState\n.set EwramSceneState,0x02000000\n"
        ".global LookupSceneScriptRecord\n.thumb_set LookupSceneScriptRecord,0x08009a15\n"
        ".global UnsignedRemainder\n.thumb_set UnsignedRemainder,0x08142b29");
u32 RemapSceneTextVariant(u32 incoming) __asm__("Remaining38_00009A90");
u32 RemapSceneTextVariant(u32 incoming)
{
    register u32 code __asm__("r4") = (u16)incoming;
    register u32 original __asm__("r6") = code;
    register u8 *root __asm__("r5");
    register u32 offset __asm__("r1");
    const u8 *record;
    register u32 address __asm__("r0");
    register u32 low_mask __asm__("r0") = 255;
    __asm__("" : "+r"(code), "+r"(original));
    __asm__("" : "+r"(low_mask));
    if ((code & low_mask) > 239) {
        register u32 difference __asm__("r0") = code - 240;
        register u32 return_mask __asm__("r1") = 255;
        __asm__("" : "+r"(difference), "+r"(return_mask));
        return difference & return_mask;
    }
    root = EwramSceneState;
    offset = 0x2192;
    __asm__("" : "+r"(root), "+r"(offset));
    address = (u32)root + offset;
    __asm__("" : "+r"(address));
    record = LookupSceneScriptRecord(*(u16 *)address);
    if (record[2] == 61) {
        register u32 count __asm__("r1");
        register u32 remainder __asm__("r1");
        register u32 byte_offset __asm__("r0");
        offset = 0x3C2A;
        __asm__("" : "+r"(offset));
        address = (u32)root + offset;
        __asm__("" : "+r"(address));
        count = *(u8 *)address;
        __asm__("" : "+r"(count));
        if (count != 0) {
            register u32 decremented __asm__("r0") = count - 1;
            __asm__("" : "+r"(decremented));
            count = (u16)decremented;
        }
        remainder = (u16)UnsignedRemainder(count,10);
        __asm__("" : "+r"(remainder));
        byte_offset = 24 * remainder;
        __asm__("" : "+r"(byte_offset));
        return (u16)(code + byte_offset);
    }
    return original;
}
