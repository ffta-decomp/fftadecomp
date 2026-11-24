typedef unsigned char u8;
typedef unsigned int u32;
/* Observed prefix only; no allocation-size or flag-meaning claim. */
struct NativeRecordByte1089 { u8 opaque00[0x1089]; u8 byte1089; };
void SetNativeRecordByte1089(struct NativeRecordByte1089*,u32) __asm__("SceneTaskDependency_00029D20");
void SetNativeRecordByte1089(struct NativeRecordByte1089 *record,u32 value)
{
    record->byte1089=(u8)value;
}
