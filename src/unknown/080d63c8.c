typedef unsigned int u32; typedef unsigned short u16; typedef short s16;
struct Task; typedef void (*Callback)(void);
extern Callback GetCallback(struct Task *) __asm__("RetailCall_08005c00");
extern void *GetPayload(struct Task *) __asm__("RetailCall_08005bfc");
extern u32 GetPhase(struct Task *) __asm__("RetailCall_08005bac");
u32 IsDefinitionTransitionReady(struct Task *task) __asm__("RemainingBand43_000D63C8");
u32 IsDefinitionTransitionReady(struct Task *task)
{
    Callback callback=GetCallback(task);
    if(callback==(Callback)0x080d5129 || callback==(Callback)0x080d5595) {
        if(*(s16*)GetPayload(task)==1) return 1;
    } else if(callback==(Callback)0x080d5a61) {
        if((u16)GetPhase(task)==258) return 1;
    }
    return 0;
}
__asm__(".global RetailCall_08005c00\n.thumb_set RetailCall_08005c00, 0x8005c01");
__asm__(".global RetailCall_08005bfc\n.thumb_set RetailCall_08005bfc, 0x8005bfd");
__asm__(".global RetailCall_08005bac\n.thumb_set RetailCall_08005bac, 0x8005bad");
