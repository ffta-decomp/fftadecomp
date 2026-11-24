typedef unsigned char u8;
typedef unsigned int u32;
/* Observed prefix only; no allocation-size or flag-meaning claim. */
struct NativeRecordByte799 { u8 opaque00[0x799]; u8 byte799; };
void SetNativeRecordByte799(struct NativeRecordByte799*,u32) __asm__("SceneTaskDependency_0002B584");
void SetNativeRecordByte799(struct NativeRecordByte799 *record,u32 value)
{
    record->byte799=(u8)value;
}
