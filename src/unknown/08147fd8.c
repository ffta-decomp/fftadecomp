typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u32 CreateNativeRangeRequest(u32,u32,u32,u32,u32);
__asm__(".global CreateNativeRangeRequest\n.thumb_set CreateNativeRangeRequest,0x08146fb9");
u32 CreateBattleRangeRequest(u32 first_word,u32 span_word,u32 identifier_word,u32 extra_word,u32 selector_word) __asm__("CoreFrontier_00147FD8");
u32 CreateBattleRangeRequest(u32 first_word,u32 span_word,u32 identifier_word,u32 extra_word,u32 selector_word)
{
    register u32 first_lane __asm__("r0");
    register u32 first_value __asm__("r6");
    register u32 span_value __asm__("r1");
    register u32 identifier_value __asm__("r5");
    u32 extra_value;
    register u32 selector_value __asm__("r2");
    register u32 identifier_lane __asm__("r2");
    u16 end;
    u32 flags;
    u32 result;
    /* Native entry captures are sequential. Every RW operand already holds
     * its actual incoming value; no instruction or value is fabricated. */
    first_lane=(u16)first_word;
    __asm__("" : "+r"(first_lane), "+r"(span_word), "+r"(identifier_word), "+r"(extra_word), "+r"(selector_word));
    first_value=first_lane;
    __asm__("" : "+r"(first_value), "+r"(span_word), "+r"(identifier_word), "+r"(extra_word), "+r"(selector_word));
    span_value=(u16)span_word;
    __asm__("" : "+r"(span_value), "+r"(identifier_word), "+r"(extra_word), "+r"(selector_word));
    identifier_value=(u16)identifier_word;
    __asm__("" : "+r"(identifier_value), "+r"(extra_word), "+r"(selector_word));
    extra_value=(u16)extra_word;
    __asm__("" : "+r"(extra_value), "+r"(selector_word));
    selector_value=(u16)selector_word;
    __asm__("" : "+r"(selector_value));
    end=first_value+span_value-1;
    if (end>511) end=511;
    flags=2;
    if (selector_value==0) flags=1;
    identifier_lane=identifier_value<<16;
    __asm__("" : "+r"(identifier_lane));
    if (((signed int)identifier_lane>>16)==-1) flags|=4;
    result=CreateNativeRangeRequest(first_value,end,identifier_lane>>16,flags,extra_value);
    /* Native R7 retains this defined fifth argument across the call. */
    __asm__("" : : "r"(extra_value));
    return result;
}
