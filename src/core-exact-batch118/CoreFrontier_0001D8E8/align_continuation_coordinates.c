typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 gContinuationState[];
extern void SetSharedUpdateFlagTwo(void);
__asm__(".global gContinuationState\n.set gContinuationState,0x02008168\n.global SetSharedUpdateFlagTwo\n.thumb_set SetSharedUpdateFlagTwo,0x0801d919");
void AlignContinuationCoordinates(void) __asm__("CoreFrontier_0001D8E8");
void AlignContinuationCoordinates(void)
{
    register u8 *state __asm__("r1") = gContinuationState;
    register u8 *previous __asm__("r3");
    register u32 mask __asm__("r4");
    register u32 mask_value __asm__("r2");
    u32 value;
    __asm__("" : "+r"(state));
    previous = state-552;
    value = *(u16 *)(previous+36)-8;
    /* The first load/subtract precedes the shared native mask definition. */
    __asm__("" : "+r"(value));
    mask=~7u;
    __asm__("" : "+r"(mask));
    mask_value=mask;
    __asm__("" : "+r"(mask_value));
    *(u16 *)(state+10) = value & mask_value;
    *(u16 *)(state+12) = (*(u16 *)(previous+38)-48) & mask_value;
    SetSharedUpdateFlagTwo();
}
