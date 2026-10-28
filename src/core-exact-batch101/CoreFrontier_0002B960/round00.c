typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleRegistry;
struct RecordOwner;
struct RecordGroup;
struct RecordState {
    void *backing;
    void *pool;
    struct RecordOwner *owner;
    u32 unobserved12;
    struct RecordGroup *group;
    u8 phase;
};
struct UnitTaskContext {
    u8 unaccessed_prefix[916];
    struct RecordState records;
};
extern struct UnitTaskContext *gUnitTaskContext;
extern void PrepareUnitTaskTransfer(void *, u16, u8);
extern u32 ComputeBattleRecordPoolBytes(u32);
extern void *AllocateGlobalPoolBytes(u32);
extern void *InitializePool(void *, u32);
extern struct BattleRegistry *GetContentConsumerContext(void);
extern struct RecordOwner *GetBattleRegistryContextAt8(struct BattleRegistry *);
extern struct RecordGroup *CreateBattleRecordGroup(struct RecordOwner *);
typedef char RecordStateOffset[(u32)&((struct UnitTaskContext *)0)->records == 916 ? 1 : -1];
/* Reload the root once after preparation; later helpers use this captured state. */
void InitializeUnitTaskRecordState(void)
{
    struct RecordState *state;
    struct RecordOwner *owner;
    u32 bytes;
    PrepareUnitTaskTransfer((u8 *)gUnitTaskContext + 8188, 288, 1);
    state = &gUnitTaskContext->records;
    bytes = ComputeBattleRecordPoolBytes(1);
    state->backing = AllocateGlobalPoolBytes(bytes);
    state->pool = InitializePool(state->backing, bytes);
    owner = GetBattleRegistryContextAt8(GetContentConsumerContext());
    state->owner = owner;
    state->group = CreateBattleRecordGroup(owner);
    state->phase = 0;
}
asm(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200F440\n"
    ".global PrepareUnitTaskTransfer\n.thumb_set PrepareUnitTaskTransfer,0x0802C72D\n"
    ".global ComputeBattleRecordPoolBytes\n.thumb_set ComputeBattleRecordPoolBytes,0x08022081\n"
    ".global AllocateGlobalPoolBytes\n.thumb_set AllocateGlobalPoolBytes,0x08022841\n"
    ".global InitializePool\n.thumb_set InitializePool,0x080070C9\n"
    ".global GetContentConsumerContext\n.thumb_set GetContentConsumerContext,0x08096D7D\n"
    ".global GetBattleRegistryContextAt8\n.thumb_set GetBattleRegistryContextAt8,0x08099C31\n"
    ".global CreateBattleRecordGroup\n.thumb_set CreateBattleRecordGroup,0x08021B1D\n");
