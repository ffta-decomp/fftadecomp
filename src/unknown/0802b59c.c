typedef unsigned char u8;
typedef unsigned int u32;
void SetNativeMenuControlParameter796(u8 *,u32) __asm__("SceneTaskDependency_0002B59C");
void SetNativeMenuControlParameter796(u8 *control,u32 raw_value)
{
    control[0x796] = raw_value;
}
