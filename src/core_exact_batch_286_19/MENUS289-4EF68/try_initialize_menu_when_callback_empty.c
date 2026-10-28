typedef unsigned char u8;
typedef unsigned int u32;
extern u32 IsCallbackSlotEmpty(u32 slot);
extern void InitializeMenuRowPolicy(void *context);
extern void RefreshMenuModeContent(void *context);
__asm__(".global IsCallbackSlotEmpty\n.thumb_set IsCallbackSlotEmpty,0x080099a5\n.global InitializeMenuRowPolicy\n.thumb_set InitializeMenuRowPolicy,0x0804f949\n.global RefreshMenuModeContent\n.thumb_set RefreshMenuModeContent,0x0804f28d");

u32 TryInitializeMenuWhenCallbackEmpty(u8 *context) __asm__("CoreRegion_0004EF68");
u32 TryInitializeMenuWhenCallbackEmpty(u8 *context)
{
    u32 ready;
    if ((u8)IsCallbackSlotEmpty(context[9])==0) {
        ready=0;
    } else {
        InitializeMenuRowPolicy(context);
        RefreshMenuModeContent(context);
        ready=1;
    }
    return ready;
}
