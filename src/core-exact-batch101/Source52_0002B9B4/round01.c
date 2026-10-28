typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct RecordGroup;
struct RecordState {
    void *backing;
    void *pool;
    void *owner;
    void *entry;
    struct RecordGroup *group;
    u8 phase;
};
struct UnitTaskContext {
    u8 unaccessed_prefix[916];
    struct RecordState records;
};
extern struct UnitTaskContext *gUnitTaskContext;
extern void PrepareUnitTaskTransfer(void *, u16, u8);
extern void RemoveGroupEntry(struct RecordGroup *, void *);
extern void DestroyGroup(struct RecordGroup *);
extern void ClearPoolFirstWord(void *);
extern void FreeGlobalPoolBytes(void *);
/* Match the initializer's one post-preparation root snapshot and callback reloads. */
void ReleaseUnitTaskRecordState(void)
{
    struct RecordState *state;
    PrepareUnitTaskTransfer((u8 *)gUnitTaskContext + 8188, 288, 0);
    state = &gUnitTaskContext->records;
    if (state->entry != 0) {
        RemoveGroupEntry(state->group, state->entry);
        state->entry = 0;
    }
    if (state->group != 0) {
        DestroyGroup(state->group);
        state->group = 0;
    }
    ClearPoolFirstWord(state->pool);
    FreeGlobalPoolBytes(state->backing);
}
asm(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200F440\n"
    ".global PrepareUnitTaskTransfer\n.thumb_set PrepareUnitTaskTransfer,0x0802C72D\n"
    ".global RemoveGroupEntry\n.thumb_set RemoveGroupEntry,0x08021BD5\n"
    ".global DestroyGroup\n.thumb_set DestroyGroup,0x08021B55\n"
    ".global ClearPoolFirstWord\n.thumb_set ClearPoolFirstWord,0x0800718D\n"
    ".global FreeGlobalPoolBytes\n.thumb_set FreeGlobalPoolBytes,0x08022855\n");
