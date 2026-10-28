typedef unsigned char u8;
typedef unsigned int u32;
void SetNativeMenuControlParameter797(u8 *,u32) __asm__("SceneTaskDependency_0002B53C");
void SetNativeMenuControlParameter797(u8 *control,u32 raw_value)
{
    control[0x797] = raw_value;
}
