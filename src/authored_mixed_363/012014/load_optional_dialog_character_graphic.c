typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct DialogDmaRequest { u8 fields[28]; };
struct DialogCharacterContext {
    u8 unknown00[44];
    u32 source_word, destination_offset;
    u8 unknown34[6];
    u16 options;
    u8 unknown3c[1820];
    struct DialogDmaRequest first, second;
};
#define OFF(t,f) ((u32)&((t *)0)->f)
typedef char CheckFirst[OFF(struct DialogCharacterContext,first)==0x758?1:-1];
typedef char CheckSecond[OFF(struct DialogCharacterContext,second)==0x774?1:-1];
typedef char CheckOptions[OFF(struct DialogCharacterContext,options)==58?1:-1];
#define CURRENT (*(struct DialogCharacterContext **)0x0200918c)
extern u8 ReadUnitRecordProperty09(const void *);
extern s32 UnitField27HasBit15(const void *);
extern u8 ReadUnitRecordProperty10Or11(const void *,u8);
extern u32 LoadIndexedCharacterGraphic(u8 *,u8);
extern void LoadVariantPalette(void *,u8);
extern void QueueDialogDma32(struct DialogDmaRequest *,u32,u32,u16);
extern u8 gDialogGraphicScratch[],gObjectVram[],gDialogPaletteShadow[];
extern void (*const gCopyDialogBytes)(u8 *,const u8 *,s32);
__asm__(".global ReadUnitRecordProperty09\n.thumb_set ReadUnitRecordProperty09,0x080cb78d\n"
        ".global UnitField27HasBit15\n.thumb_set UnitField27HasBit15,0x080c8241\n"
        ".global ReadUnitRecordProperty10Or11\n.thumb_set ReadUnitRecordProperty10Or11,0x080cb7c1\n"
        ".global LoadIndexedCharacterGraphic\n.thumb_set LoadIndexedCharacterGraphic,0x080cb8b5\n"
        ".global LoadVariantPalette\n.thumb_set LoadVariantPalette,0x080cb8d5\n"
        ".global QueueDialogDma32\n.thumb_set QueueDialogDma32,0x08000add\n"
        ".global gDialogGraphicScratch\n.set gDialogGraphicScratch,0x02003cb0\n"
        ".global gObjectVram\n.set gObjectVram,0x06010000\n"
        ".global gDialogPaletteShadow\n.set gDialogPaletteShadow,0x03003b20\n"
        ".global gCopyDialogBytes\n.set gCopyDialogBytes,0x0836d4bc\n"
        ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251");
void LoadOptionalDialogCharacterGraphic(void) __asm__("Source52_00012014");
void LoadOptionalDialogCharacterGraphic(void)
{
    struct DialogCharacterContext *initial=CURRENT;
    struct DialogCharacterContext *first_context,*second_context;
    register struct DialogCharacterContext **dma_root __asm__("r10");
    register struct DialogCharacterContext **first_root __asm__("r1");
    register struct DialogDmaRequest *first_request __asm__("r0");
    register u32 first_destination __asm__("r2");
    u8 graphic,palette_selector;
    register u32 size __asm__("r8");
    u16 count;
    u32 size_shifted;
    u32 half;
    register u8 *second_source __asm__("r1");
    register struct DialogDmaRequest *second_request __asm__("r0");
    register u8 *scratch __asm__("r6");
    if(!(initial->options&128)) {
        u32 packed=initial->source_word;
        graphic=(u8)(packed>>8);
        palette_selector=(u8)packed;
    } else {
        const void *unit=(const void *)initial->source_word;
        graphic=(u8)ReadUnitRecordProperty09(unit);
        palette_selector=ReadUnitRecordProperty10Or11(unit,(u8)!(u8)UnitField27HasBit15(unit));
    }
    scratch=gDialogGraphicScratch;
    __asm__("" : "+r"(scratch));
    size_shifted=LoadIndexedCharacterGraphic(scratch,graphic)<<16;
    size=size_shifted>>16;
    __asm__("" : "+r"(size));
    half=(u16)(size_shifted>>17);
    first_root=(struct DialogCharacterContext **)0x0200918c;
    dma_root=first_root;
    __asm__("" : "+r"(dma_root) : "r"(first_root));
    first_context=*first_root;
    first_request=&first_context->first;
    __asm__("" : "+r"(first_request));
    first_destination=first_context->destination_offset+(u32)gObjectVram;
    __asm__("" : "+r"(first_destination) : "r"(first_request));
    count=(u16)(half>>2);
    QueueDialogDma32(first_request,(u32)scratch,first_destination,count);
    second_context=*dma_root;
    second_request=&second_context->second;
    __asm__("" : "+r"(second_request));
    __asm__("add %0,%1,%2" : "=l"(second_source)
            : "l"(half), "l"(scratch) : "cc");
    half+=(u32)gObjectVram;
    __asm__("" : "+r"(half));
    QueueDialogDma32(second_request,(u32)second_source,
                     second_context->destination_offset+half,count);
    size+=(u32)scratch;
    __asm__("" : "+r"(size));
    LoadVariantPalette((u8 *)size,palette_selector);
    /* The ROM cell selects the existing IWRAM CopyBytes implementation. */
    gCopyDialogBytes(gDialogPaletteShadow,(const u8 *)size,96);
}
