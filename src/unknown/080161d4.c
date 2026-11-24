typedef unsigned char u8;
typedef unsigned int u32;
extern void RenderEncodedTextWithFont(u32,u32,u32,u8,u8,u8,u8,const void *,u32) asm("RetailCall_080154D8");
extern const u8 NativeTextFontPreset[];
void RenderEncodedTextWithNativeFont(u32,u32,u32,u8,u8,u8,u8) asm("SceneTaskDependency_000161D4");
void RenderEncodedTextWithNativeFont(u32 argument0, u32 argument1, u32 argument2,
                                   u8 argument3, u8 argument4, u8 argument5, u8 argument6)
{
    RenderEncodedTextWithFont(argument0, argument1, argument2,
                             argument3, argument4, argument5, argument6,
                             NativeTextFontPreset, 2048);
}
__asm__(".global NativeTextFontPreset\n.set NativeTextFontPreset,0x030008B0\n"
        ".global RetailCall_080154D8\n.thumb_set RetailCall_080154D8,0x080154D9");
