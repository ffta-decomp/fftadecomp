typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneWorkRecordView { u32 key; u8 *owned; u8 remaining[172]; };
typedef char RecordStride[sizeof(struct SceneWorkRecordView)==180?1:-1];
void WriteSceneWorkOwnedHalfwords(void *work, u32 key, u16 first, u16 second, u16 third, u16 fourth)
{
    s32 ordinal = 0;
    struct SceneWorkRecordView *cursor = (struct SceneWorkRecordView *)((u8 *)work + 8);
    struct SceneWorkRecordView *matched;
visit_record:
    if (cursor->key == key) {
        matched = cursor;
        goto apply_values;
    }
    cursor++;
    ordinal++;
    if (ordinal <= 12)
        goto visit_record;
    matched = 0;
apply_values:
    if (matched != 0) {
        s32 signed_first = (s16)first;
        u8 *owned = matched->owned;
        register u32 second_value __asm__("r3") = second;
        /* Only the store phase needs this observed R3 value.
           Initialized read-only allocation constraint; no emitted instruction. */
        asm("" : : "r"(second_value));
        *(s16 *)(owned + 30) = signed_first;
        *(u16 *)(owned + 32) = second_value;
        *(u16 *)(owned + 34) = third;
        *(u16 *)(owned + 36) = fourth;
        *(s16 *)(owned + 28) = signed_first;
    }
}
