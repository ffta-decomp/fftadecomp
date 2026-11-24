typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct SceneWorkRecordView { u32 key; void *owned; u8 remaining[172]; };
struct SceneWorkView { u8 prefix[8]; struct SceneWorkRecordView records[13]; };
typedef char RecordStride[sizeof(struct SceneWorkRecordView)==180?1:-1];
typedef char WorkExtent[sizeof(struct SceneWorkView)==2348?1:-1];
typedef char FirstKey[(u32)&(((struct SceneWorkView *)0)->records[0].key)==8?1:-1];
u32 ContainsSceneWorkKey(const void *state_argument, u32 key)
{
    u32 result;
    s32 ordinal = 0;
    const u8 *cursor = (const u8 *)state_argument + 8;
visit_record:
    if (*(const u32 *)cursor == key) {
        result = 1;
        goto done;
    }
    cursor += sizeof(struct SceneWorkRecordView);
    ordinal++;
    if (ordinal <= 12)
        goto visit_record;
    result = 0;
done:
    return result;
}
