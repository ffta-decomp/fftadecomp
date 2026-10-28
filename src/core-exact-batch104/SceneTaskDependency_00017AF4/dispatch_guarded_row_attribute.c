typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Call_0801799C(u8 *, int, u32, u32);
__asm__(".global Call_0801799C\n.thumb_set Call_0801799C, 0x0801799D");
void SceneTaskDependency_00017AF4(u8 *object, u32 input_row, u32 input_value)
{
    u8 row = input_row;
    u8 value = input_value;
    if (!(*(u16 *)(object + 16) & 1))
        Call_0801799C(object, (s8)row, value, object[21]);
}
