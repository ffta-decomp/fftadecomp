typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 NativeCounterScratch[];
extern const u8 NativeCounterFrame[];
extern const u8 NativeCounterVariants[];
extern u8 NativeCounterState[];
extern void *NativeCounterFontOwner;
extern s32 SignedRemainder(s32,s32) asm("RetailCall_08142950");
extern void CopyCounterFrame(const void *,void *,u32,u32) asm("RetailCall_08005318");
extern void CpuSet(const void *,void *,u32) asm("RetailCall_0814186c");
extern void EncodeCounter(u32,u16) asm("RetailCall_08035cac");
extern u32 RenderNativeStream(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
extern void NotifyCounterMode(u32,u32) asm("RetailCall_0808a604");
void UpdateNativeCounterGlyphTiles(u32) asm("CoreRegion_00035D00");
void UpdateNativeCounterGlyphTiles(u32 mode_in)
{
    register u32 mode asm("r9") = mode_in;
    register u8 *scratch asm("r6") = NativeCounterScratch;
    u8 *glyph_tiles = scratch + 256;
    register const u8 *frame asm("r8") = NativeCounterFrame;
    register const u8 *variants asm("r5") = NativeCounterVariants;
    register u8 *state asm("r4") = NativeCounterState;
    s32 variant;
    register u32 variant_address asm("r0");
    u32 zero;
    register void *frame_vram asm("r1");
    register u32 halfword_count asm("r2");
    asm("" : "+r"(mode), "+r"(scratch), "+r"(glyph_tiles), "+r"(frame), "+r"(variants));
    asm("" : "+r"(state));
    variant = SignedRemainder((s32)state[0x2FBA]-1,6);
    variant_address = (u32)variant + (u32)variants;
    asm("" : "+r"(variant_address));
    CopyCounterFrame(frame,scratch,*(const u8 *)variant_address >> 1,12);
    frame_vram = (void *)0x06010BC0;
    halfword_count = 128;
    asm("" : "+r"(frame_vram), "+r"(halfword_count));
    halfword_count <<= 1;
    CpuSet(scratch,frame_vram,halfword_count);
    state += 0x2FBB;
    EncodeCounter((u32)scratch,*state);
    RenderNativeStream((void *)((u32)NativeCounterFontOwner+0xC4C),(u32)glyph_tiles,scratch,0,1);
    if (*state <= 9) {
        zero = 0;
        CpuSet(&zero,glyph_tiles,0x05000010);
        glyph_tiles = scratch + 260;
    }
    CpuSet(glyph_tiles,(void *)0x06010DC0,16);
    CpuSet(glyph_tiles+32,(void *)0x06010E00,16);
    CpuSet(glyph_tiles+64,(void *)0x06010DE0,16);
    CpuSet(glyph_tiles+96,(void *)0x06010E20,16);
    if (mode == 1) NotifyCounterMode(3,2);
}
__asm__(".global RetailCall_08142950\n.thumb_set RetailCall_08142950,0x08142951\n"
        ".global RetailCall_08005318\n.thumb_set RetailCall_08005318,0x08005319\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_08035cac\n.thumb_set RetailCall_08035cac,0x08035cad\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n"
        ".global RetailCall_0808a604\n.thumb_set RetailCall_0808a604,0x0808a605\n"
        ".global NativeCounterScratch\n.set NativeCounterScratch,0x02003CB0\n"
        ".global NativeCounterFrame\n.set NativeCounterFrame,0x083ACD68\n"
        ".global NativeCounterVariants\n.set NativeCounterVariants,0x0839195A\n"
        ".global NativeCounterState\n.set NativeCounterState,0x02000000\n"
        ".global NativeCounterFontOwner\n.set NativeCounterFontOwner,0x03002810\n");
