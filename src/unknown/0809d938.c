typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct SceneOwnedRecord { u32 unknown_00; void *owned; u8 remaining[172]; };
struct SceneOwnedWorkView { u8 prefix[8]; struct SceneOwnedRecord records[13]; };
typedef char RecordStride[sizeof(struct SceneOwnedRecord)==180?1:-1];
typedef char WorkExtent[sizeof(struct SceneOwnedWorkView)==2348?1:-1];
typedef char FirstOwnedOffset[(u32)&(((struct SceneOwnedWorkView *)0)->records[0].owned)==12?1:-1];
extern void FreeGlobalPoolBytes(void *);
void ReleaseBattleSceneWorkBuffer(void *state_argument)
{
    struct SceneOwnedWorkView *state = state_argument;
    s32 ordinal = 0;
    u32 byte_offset;
    u8 *first_owned;
    void **slot;
    void *owned;
visit_slot:
    byte_offset = ordinal * sizeof(struct SceneOwnedRecord);
    first_owned = (u8 *)state + 12;
    slot = (void **)(first_owned + byte_offset);
    owned = *slot;
    if (owned != 0) {
        FreeGlobalPoolBytes(owned);
        *slot = 0;
    }
    ordinal++;
    if (ordinal <= 12)
        goto visit_slot;
    FreeGlobalPoolBytes(state);
}
asm(".global FreeGlobalPoolBytes\n.thumb_set FreeGlobalPoolBytes,0x08022855\n");
