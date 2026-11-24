typedef unsigned char u8;
typedef unsigned int u32;

extern u32 ExistingSceneTaskOperation(u32, u32, u32, u32, u32, u32, u32);
__asm__(".global ExistingSceneTaskOperation\n.thumb_set ExistingSceneTaskOperation,0x08021619");

void SceneTaskDependency_00029CD8(u8 *record, u32 first, u32 second)
{
    u8 *first_byte;
    u32 zero;
    u32 result;

    first_byte = record + 0x1086;
    zero = 0;
    *first_byte = (u8)first;
    record[0x1088] = (u8)second;
    result = ExistingSceneTaskOperation(
        *(u32 *)(record + 128),
        *(u32 *)(record + 124),
        zero,
        20,
        record[0x1085],
        record[0x1086],
        zero);
    *(u32 *)(record + 124) = result;
}
