typedef unsigned char u8;
typedef unsigned int u32;
/* Observed prefix and byte0x80 only; no fullsize/fieldmeaning claim. */
struct NativeRecordByte80 { u8 opaque00[0x80]; u8 byte80; };
void SetNativeRecordByte80(struct NativeRecordByte80*,u32) __asm__("SceneTaskDependency_0002AB4C");
void SetNativeRecordByte80(struct NativeRecordByte80 *record,u32 value)
{
    record->byte80=(u8)value;
}
