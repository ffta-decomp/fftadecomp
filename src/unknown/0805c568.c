typedef unsigned char u8;
extern void ResetNativeRecordWindowBounds(u8,u8,u8,u8);
extern void ConfigureNativeRecordWindowFirst(u8,u8,u8,u8);
extern void ConfigureNativeRecordWindowSecond(u8,u8,u8,u8);
__asm__(".global ResetNativeRecordWindowBounds\n.thumb_set ResetNativeRecordWindowBounds,0x0802a425\n"
        ".global ConfigureNativeRecordWindowFirst\n.thumb_set ConfigureNativeRecordWindowFirst,0x0802a2c1\n"
        ".global ConfigureNativeRecordWindowSecond\n.thumb_set ConfigureNativeRecordWindowSecond,0x0802a371");
void InitializeNativeRecordWindowBounds(void) __asm__("CoreClosure31_0005C568");
void InitializeNativeRecordWindowBounds(void)
{
    ResetNativeRecordWindowBounds(0,0,0,0);
    ConfigureNativeRecordWindowFirst(0,0,30,9);
    ConfigureNativeRecordWindowSecond(20,10,10,10);
}
