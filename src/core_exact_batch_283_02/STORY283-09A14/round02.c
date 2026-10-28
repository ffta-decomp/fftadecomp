typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern const u8 SceneScriptRecordTable[];
__asm__(".global SceneScriptRecordTable\n"
        ".set SceneScriptRecordTable, 0x08A19970");

u8 *SceneActionDependency_00009A14(u32 index)
{
    u32 byte_offset = ((u32)(u16)index) << 16;
    const u8 *table_base = SceneScriptRecordTable;
    byte_offset >>= 14;
    return (u8 *)(table_base + byte_offset);
}
