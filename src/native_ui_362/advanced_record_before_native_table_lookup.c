typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeAbilityLabelEntry { u16 text_index; u8 remaining[6]; };
struct NativeCopyRequest;
extern const struct NativeAbilityLabelEntry *const NativeAbilityLabelLists[];
extern const u8 *const NativeAbilityLabelTexts[];
extern u8 *NativeUnitTaskContext;
extern void *AllocateNativeUnitLabel(u32) asm("RetailCall_08022840");
extern void ReleaseNativeUnitLabel(void *) asm("RetailCall_08022854");
extern void CopyNativeUnitLabelHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
extern u32 ReadNativeUnitLabelField(const void *,u8) asm("RetailCall_080c7ea4");
extern u32 RenderNativeUnitLabel(void *,u32,const u8 *,u32,u32) asm("RetailCall_08015110");
extern void ArrangeNativeUnitLabelTiles(u8 *,const u8 *) asm("RetailCall_0802baf8");
extern struct NativeCopyRequest *TakeNativeUnitLabelRequest(void) asm("RetailCall_0802ba08");
extern void QueueNativeUnitLabelCopy(struct NativeCopyRequest *,u32,u32,u16) asm("RetailCall_08000adc");
void UpdateNativeUnitAbilityLabel(u8 *) asm("TaskConstructor45_0002C034");
void UpdateNativeUnitAbilityLabel(u8 *descriptor)
{
    u8 *scratch=AllocateNativeUnitLabel(768);
    u16 zero;
    register u16 *zero_address asm("r1");
    const u8 *text;
    u8 *output;
    zero_address=&zero;
    asm("" : "+r"(zero_address));
    *zero_address=0;
    CopyNativeUnitLabelHalfwords(zero_address,scratch,0x01000180);
    if (*(u16 *)(descriptor+16)&2) {
        const struct NativeAbilityLabelEntry *list;
        list=NativeAbilityLabelLists[ReadNativeUnitLabelField(*(void **)(descriptor+12),3)];
        list += (*(u8 **)(descriptor+12))[58];
        text=NativeAbilityLabelTexts[list->text_index];
    } else {
        text=(const u8 *)ReadNativeUnitLabelField(*(void **)(descriptor+12),0);
    }
    RenderNativeUnitLabel(NativeUnitTaskContext+972,(u32)scratch,text,0,1);
    output=descriptor+40;
    ArrangeNativeUnitLabelTiles(output,scratch);
    ReleaseNativeUnitLabel(scratch);
    QueueNativeUnitLabelCopy(TakeNativeUnitLabelRequest(),(u32)output,0x06014500,192);
}
__asm__(".global NativeAbilityLabelLists\n.set NativeAbilityLabelLists,0x0851ba84\n"
        ".global NativeAbilityLabelTexts\n.set NativeAbilityLabelTexts,0x085567f0\n"
        ".global NativeUnitTaskContext\n.set NativeUnitTaskContext,0x0200f440\n"
        ".global RetailCall_08022840\n.thumb_set RetailCall_08022840,0x08022841\n"
        ".global RetailCall_08022854\n.thumb_set RetailCall_08022854,0x08022855\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_080c7ea4\n.thumb_set RetailCall_080c7ea4,0x080c7ea5\n"
        ".global RetailCall_08015110\n.thumb_set RetailCall_08015110,0x08015111\n"
        ".global RetailCall_0802baf8\n.thumb_set RetailCall_0802baf8,0x0802baf9\n"
        ".global RetailCall_0802ba08\n.thumb_set RetailCall_0802ba08,0x0802ba09\n"
        ".global RetailCall_08000adc\n.thumb_set RetailCall_08000adc,0x08000add\n");
