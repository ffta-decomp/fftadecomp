typedef unsigned char u8;
typedef unsigned int u32;
typedef u32 (*RecordWordCallback)(u32 record_address, void *argument);
typedef u32 (*RecordNodeVisitor)(void *node, void *argument);
struct BattleRecordCapture { u32 count; u32 *cursor; };
struct RecordWordVisitor { void *argument; RecordWordCallback callback; };
struct UnitCollectionFrame {
    struct BattleRecordCapture capture;
    struct RecordWordVisitor visitor;
};
struct BattleUnitListContext { u8 prefix[16]; void *list_owner; };
typedef char CaptureSize[(sizeof(struct BattleRecordCapture)==8)?1:-1];
typedef char VisitorOffset[(u32)&((struct UnitCollectionFrame *)0)->visitor==8?1:-1];
typedef char FrameSize[(sizeof(struct UnitCollectionFrame)==16)?1:-1];
extern void VisitBattleUnitList(void *owner, RecordNodeVisitor visit, void *argument);
extern u32 VisitBattleUnitNodeWord(void *node, void *argument);
extern u32 AppendCollectedBattleRecord(u32 record_address, void *argument);
__asm__(".global VisitBattleUnitList\n.thumb_set VisitBattleUnitList, 0x080c7cc1\n.global VisitBattleUnitNodeWord\n.thumb_set VisitBattleUnitNodeWord, 0x0809abe9\n.global AppendCollectedBattleRecord\n.thumb_set AppendCollectedBattleRecord, 0x0809ac21");
/* Capacity remains the caller's obligation; the original entry has no bound. */
u32 CollectBattleUnitRecordAddresses(const struct BattleUnitListContext *context,
                                    u32 *record_addresses)
{
    struct UnitCollectionFrame frame;
    RecordWordCallback append;
    struct RecordWordVisitor *visitor;
    frame.capture.count = 0;
    frame.capture.cursor = record_addresses;
    append = AppendCollectedBattleRecord;
    frame.visitor.argument = &frame.capture;
    visitor = &frame.visitor;
    visitor->callback = append;
    VisitBattleUnitList(context->list_owner, VisitBattleUnitNodeWord, visitor);
    return frame.capture.count;
}
