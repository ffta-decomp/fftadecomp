typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
struct PairCursorDescriptor { const void *asset; s16 x, y; };
struct BattlePairContext {
    u16 x, y; u8 mode, unknown_05, pending_count, selected_count, row_limit;
    u8 unknown_09[6]; u8 flags15; u8 unknown_10[656]; void *allocation;
    u8 unknown_2a4[456]; const void *asset_a, *asset_b;
    u8 unknown_474[4]; const void *asset_c; u8 unknown_47c[3532];
    struct PairCursorDescriptor cursor; u8 unknown_1250[4]; u8 alpha;
};
#define OFFSET(T, M) ((u32)&(((T *)0)->M))
typedef char allocation_offset[(OFFSET(struct BattlePairContext, allocation)==672)?1:-1];
typedef char assets_offset[(OFFSET(struct BattlePairContext, asset_a)==1132)?1:-1];
typedef char cursor_offset[(OFFSET(struct BattlePairContext, cursor)==4680)?1:-1];
typedef char alpha_offset[(OFFSET(struct BattlePairContext, alpha)==4692)?1:-1];
extern struct BattlePairContext *BattlePairContextCell;
extern u8 BattlePairWorkRam[];
extern const u8 PairAssetA[], PairAssetB[], PairAssetC[];
extern void (*const ClearPairContextCell)(void *, u32);
extern void CompactPendingRecords_080CC2B4(void);
extern void *AllocatePairContext_08022840(u32);
extern u32 CountPendingRecords_080CCA80(void);
extern u32 CountPairUnitRecords_0802D764(void);
extern void SetPairCursorDescriptor_08017FA8(struct PairCursorDescriptor *, const void *, s16, s16);
extern void RequestPairService_08141540(u32);
extern void SetupPairDisplay_0802F27C(u32);
extern void ResetPairWidget_080255FC(u32);
extern u8 SceneState[];
struct PairDisplayShadow { u8 before[74]; volatile u8 byte74, byte75; };
extern struct PairDisplayShadow PairDisplayShadow;
void CoreFrontier_0002F400(u32 allocation_bytes)
{
    void *allocation;
    struct BattlePairContext *before_count, *after_count, *configured, *cursor_context;
    u8 *count_base;
    u8 zero_shadow;
    PairDisplayShadow.byte75 = 0;
    zero_shadow = PairDisplayShadow.byte75;
    PairDisplayShadow.byte74 = zero_shadow;
    CompactPendingRecords_080CC2B4();
    allocation = AllocatePairContext_08022840(allocation_bytes);
    BattlePairContextCell = allocation;
    ClearPairContextCell(allocation, 4696);
    before_count = BattlePairContextCell;
    count_base = BattlePairWorkRam;
    asm("" : "+r"(count_base));
    before_count->row_limit = count_base[0x3c32];
    after_count = BattlePairContextCell;
    after_count->x = 1;
    after_count->y = 9;
    after_count->allocation = allocation;
    BattlePairContextCell->pending_count = CountPendingRecords_080CCA80();
    BattlePairContextCell->selected_count = CountPairUnitRecords_0802D764();
    BattlePairContextCell->flags15 = 0;
    configured = BattlePairContextCell;
    configured->asset_a = PairAssetA;
    configured->asset_b = PairAssetB;
    configured->asset_c = PairAssetC;
    SetupPairDisplay_0802F27C(0);
    cursor_context = BattlePairContextCell;
    {
        int cursor_x = (cursor_context->x - 1) * 8 + 2;
        int cursor_y = cursor_context->y + 2;
        SetPairCursorDescriptor_08017FA8(&cursor_context->cursor, PairAssetC,
            (s16)cursor_x, (s16)(cursor_y * 8));
    }
    ResetPairWidget_080255FC(SceneState[3]);
    RequestPairService_08141540(101);
    BattlePairContextCell->mode = 0;
}
asm(".set BattlePairContextCell, 0x0200f444\n");
asm(".set BattlePairWorkRam, 0x02000000\n");
asm(".set PairAssetA, 0x0839173c\n");
asm(".set PairAssetB, 0x08391756\n");
asm(".set PairAssetC, 0x0839176a\n");
asm(".set ClearPairContextCell, 0x0836d4b8\n");
asm(".thumb_set CompactPendingRecords_080CC2B4, 0x080cc2b5\n");
asm(".thumb_set AllocatePairContext_08022840, 0x08022841\n");
asm(".thumb_set CountPendingRecords_080CCA80, 0x080cca81\n");
asm(".thumb_set CountPairUnitRecords_0802D764, 0x0802d765\n");
asm(".thumb_set SetPairCursorDescriptor_08017FA8, 0x08017fa9\n");
asm(".thumb_set RequestPairService_08141540, 0x08141541\n");
asm(".thumb_set SetupPairDisplay_0802F27C, 0x0802f27d\n");
asm(".thumb_set _call_via_r2, 0x0814224d\n");
asm(".set SceneState,0x0200f390\n.set PairDisplayShadow,0x03000940\n.thumb_set ResetPairWidget_080255FC,0x080255fd\n");
