typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct SceneWorkRecordView { u32 key; u8 *owned; u8 remaining[172]; };
typedef char RecordStride[sizeof(struct SceneWorkRecordView)==180?1:-1];
void WriteSceneWorkOwnedByte(void *work, u32 key, u8 value)
{
    s32 ordinal = 0;
    struct SceneWorkRecordView *cursor = (struct SceneWorkRecordView *)((u8 *)work + 8);
    struct SceneWorkRecordView *matched;
visit_record:
    if (cursor->key == key) {
        matched = cursor;
        goto apply_value;
    }
    cursor++;
    ordinal++;
    if (ordinal <= 12)
        goto visit_record;
    matched = 0;
apply_value:
    if (matched != 0)
        matched->owned[38] = value;
}
