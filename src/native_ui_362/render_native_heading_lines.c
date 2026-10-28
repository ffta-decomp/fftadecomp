typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 NativeHeadingScratch[];
extern const u8 NativeHeadingPrefix[];
extern const u8 NativeHeadingMiddle[];
extern const u8 NativeHeadingSeparator[];
extern const u8 *NativeHeadingNames[];
extern const u8 *NativeHeadingTextBank[];
extern u8 *NativeHeadingRoot;
extern u8 NativeHeadingSurface[];
extern void FormatNativeHeadingParts(u8*,const u8*,const u8*,const u8*,const u8*,const u8*) asm("RetailCall_08038d80");
extern u32 MeasureNativeHeadingTiles(const u8*) asm("RetailCall_080161bc");
extern u32 ResolveNativeHeadingPosition(u32,u32,u32,u32) asm("RetailCall_0808b92c");
extern u32 RenderNativeHeadingTokens(void*,u32,const u8*,u32,u32) asm("RetailCall_08015110");
#define HEADING_POINTER(base,offset) (*(u8 **)((base)+(offset)))
#define HEADING_HALFWORD(base,offset) (*(u16 *)((base)+(offset)))
void RenderNativeHeadingLines(void) asm("CoreRegion_0004A2E4");
void RenderNativeHeadingLines(void)
{
    u8 *formatted=NativeHeadingScratch;
    const u8 *prefix=NativeHeadingPrefix;
    register const u8 **names asm("r8")=NativeHeadingNames;
    register const u8 **bank asm("r9");
    u8 *initial_owner;
    const u8 *initial_name;
    asm("" : "+r"(names));
    initial_owner=NativeHeadingRoot;
    initial_name=names[HEADING_HALFWORD(HEADING_POINTER(initial_owner,4),32)];
    FormatNativeHeadingParts(formatted,prefix,initial_name,NativeHeadingMiddle,NativeHeadingSeparator,
        ({
            register const u8 **initial_bank asm("r5")=NativeHeadingTextBank;
            bank=initial_bank;
            /* The actual sixth argument produces and reads this address. */
            asm("" : "+r"(bank) : "r"(initial_bank));
            initial_bank[26];
        }));
    if((u16)MeasureNativeHeadingTiles(formatted)<=25) {
        register u32 position asm("r1")=ResolveNativeHeadingPosition(4,(u32)NativeHeadingSurface,0,0);
        asm("" : "+r"(position));
        RenderNativeHeadingTokens(NativeHeadingRoot+3148,position,formatted,0,1);
    } else {
        u8 *surface=NativeHeadingSurface;
        u8 *name_owner;
        register u32 position asm("r1")=ResolveNativeHeadingPosition(4,(u32)surface,0,0);
        asm("" : "+r"(position));
        name_owner=NativeHeadingRoot;
        RenderNativeHeadingTokens(name_owner+3148,position,
            names[HEADING_HALFWORD(HEADING_POINTER(name_owner,4),32)],0,1);
        position=ResolveNativeHeadingPosition(4,(u32)surface,0,2);
        asm("" : "+r"(position));
        RenderNativeHeadingTokens(NativeHeadingRoot+3148,position,
            ({
                register const u8 **last_bank asm("r3")=bank;
                asm("" : "+r"(last_bank));
                last_bank[26];
            }),0,1);
    }
}
__asm__(".global NativeHeadingScratch\n.set NativeHeadingScratch,0x02003cb0\n"
        ".global NativeHeadingPrefix\n.set NativeHeadingPrefix,0x08391800\n"
        ".global NativeHeadingMiddle\n.set NativeHeadingMiddle,0x08391803\n"
        ".global NativeHeadingSeparator\n.set NativeHeadingSeparator,0x083917fa\n"
        ".global NativeHeadingNames\n.set NativeHeadingNames,0x0855a64c\n"
        ".global NativeHeadingTextBank\n.set NativeHeadingTextBank,0x085668b0\n"
        ".global NativeHeadingRoot\n.set NativeHeadingRoot,0x03002810\n"
        ".global NativeHeadingSurface\n.set NativeHeadingSurface,0x06009960\n"
        ".global RetailCall_08038d80\n.thumb_set RetailCall_08038d80,0x08038d81\n"
        ".global RetailCall_080161bc\n.thumb_set RetailCall_080161bc,0x080161bd\n"
        ".global RetailCall_0808b92c\n.thumb_set RetailCall_0808b92c,0x0808b92d\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n");
