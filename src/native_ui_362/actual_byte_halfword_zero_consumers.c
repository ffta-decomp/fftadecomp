typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct NativeLayerWorkspace {u8 unknown00[16];u8 *buffer;} NativeLayerWorkspace;
typedef void (*NativeDescriptorCopyFunction)(u8 *,const u8 *,s32);
extern NativeDescriptorCopyFunction NativeDescriptorCopy;
extern u8 NativeMenuAssetScratch[];
extern const u8 NativeMenuAssetBank[];
extern const u8 NativeMenuDescriptorTemplate[];
extern NativeLayerWorkspace NativeMenuLayer;
extern u32 DecodeNativeMenuAsset(void *,const void *) asm("RetailCall_0800543c");
extern void CopyNativeMenuHalfwords(const void *,void *,u32) asm("RetailCall_0814186c");
extern u16 NormalizeNativeMenuDescriptor(void *) asm("RetailCall_08013b50");
extern void *AllocateNativeMenuBlock(u32) asm("RetailCall_08005b28");
extern void InitializeNativeMenuWindow(void *,u8,u8,u8,u8,u16,u16,u16,u8) asm("RetailCall_08017490");
extern void BindNativeMenuWindowBuffers(void *,void *) asm("RetailCall_08016bd8");
extern void ClearNativeMenuWindowText(void *,u16) asm("RetailCall_08013a88");
void InitializeNativeDescriptorMenu(u8 *) asm("RemainingCore48_00066C98");
void InitializeNativeDescriptorMenu(u8 *context)
{
    u8 *descriptor=context+24;
    u8 *window=context+40;
    u8 *asset=NativeMenuAssetScratch;
    register u32 zero_byte asm("r1");
    register u32 zero_halfword asm("r0");
    DecodeNativeMenuAsset(asset,NativeMenuAssetBank);
    CopyNativeMenuHalfwords(asset+6272,NativeMenuLayer.buffer+17920,496);
    asset += 5888;
    CopyNativeMenuHalfwords(asset,NativeMenuLayer.buffer+18912,32);
    NativeDescriptorCopy(descriptor,NativeMenuDescriptorTemplate,16);
    NormalizeNativeMenuDescriptor(descriptor);
    *(void **)(context+188)=AllocateNativeMenuBlock(468);
    InitializeNativeMenuWindow(window,descriptor[0],descriptor[1],descriptor[2],descriptor[3],
        *(u16 *)(descriptor+6),13,3,11);
    BindNativeMenuWindowBuffers(window,context+192);
    ClearNativeMenuWindowText(NativeMenuLayer.buffer+
        (((u32)*(u16 *)(descriptor+14)+256)<<5),104);
    zero_byte=0;
    zero_halfword=0;
    asm("" : "+r"(zero_byte), "+r"(zero_halfword));
    *(u16 *)(context+10)=zero_halfword;
    context[14]=zero_byte;
    context[13]=zero_byte;
    context[12]=zero_byte;
}
__asm__(".global NativeMenuAssetScratch\n.set NativeMenuAssetScratch,0x02003cb0\n"
        ".global NativeMenuAssetBank\n.set NativeMenuAssetBank,0x083b4214\n"
        ".global NativeMenuLayer\n.set NativeMenuLayer,0x030008b0\n"
        ".global NativeDescriptorCopy\n.set NativeDescriptorCopy,0x0836d4bc\n"
        ".global NativeMenuDescriptorTemplate\n.set NativeMenuDescriptorTemplate,0x08393aa4\n"
        ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n"
        ".global RetailCall_0800543c\n.thumb_set RetailCall_0800543c,0x0800543d\n"
        ".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n"
        ".global RetailCall_08013b50\n.thumb_set RetailCall_08013b50,0x08013b51\n"
        ".global RetailCall_08005b28\n.thumb_set RetailCall_08005b28,0x08005b29\n"
        ".global RetailCall_08017490\n.thumb_set RetailCall_08017490,0x08017491\n"
        ".global RetailCall_08016bd8\n.thumb_set RetailCall_08016bd8,0x08016bd9\n"
        ".global RetailCall_08013a88\n.thumb_set RetailCall_08013a88,0x08013a89\n");
