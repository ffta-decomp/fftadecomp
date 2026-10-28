typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern const void *const gSaveSelectedResourceTable[];
extern u8 gSavePairLiveImage[];
extern u8 *gSavePairContext;
extern void CopyNativeHalfwords(const void*,void*,u32) asm("RetailCall_0814186C");
void CopySaveRestoreSelectedResourcePair(void) asm("Remaining38_00137C4C");
void CopySaveRestoreSelectedResourcePair(void)
{
    register const void *const *table asm("r9");
    u8 *live;
    const volatile u8 *selector;
    u8 **context_cell;
    u32 byte_offset;
    const void *source;
    u32 first_offset;
    u32 count;
    table=gSaveSelectedResourceTable;
    /* Actual non-null ROM table root is kept in R9 across both copies. */
    asm("" : "+r"(table));
    live=gSavePairLiveImage;
    /* Preserve the complete live-image base before the physical byte offset. */
    asm("" : "+r"(live));
    live+=0x2FC2;
    selector=live;
    byte_offset=(u32)*selector;
    byte_offset<<=30;
    byte_offset>>=27;
    source=*(const void *const *)((u32)table+byte_offset);
    context_cell=&gSavePairContext;
    {
        u8 *destination=*context_cell;
        first_offset=0xA1C;
        destination+=first_offset;
        count=256;
        CopyNativeHalfwords(source,destination,count);
    }
    /* The selector and context may both change across the original call. */
    byte_offset=(u32)*selector;
    byte_offset<<=30;
    byte_offset>>=29;
    ++byte_offset;
    byte_offset<<=2;
    source=*(const void *const *)((u32)table+byte_offset);
    {
        u8 *destination=*context_cell;
        destination+=0xC1C;
        CopyNativeHalfwords(source,destination,count);
    }
    *(u16 *)(*context_cell+first_offset)=0;
}
__asm__(".global gSaveSelectedResourceTable\n.set gSaveSelectedResourceTable,0x083a8e44\n.global gSavePairLiveImage\n.set gSavePairLiveImage,0x02000000\n.global gSavePairContext\n.set gSavePairContext,0x030027d8\n.global RetailCall_0814186C\n.thumb_set RetailCall_0814186C,0x0814186d");
