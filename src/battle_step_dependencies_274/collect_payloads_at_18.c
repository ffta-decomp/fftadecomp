typedef unsigned int u32;
struct LinkedNode;
struct ListOwner;
struct RecordCapture { u32 count; u32 *cursor; };
typedef u32 (*RecordCallback)(u32 record, struct RecordCapture *capture);
typedef u32 (*ListNodeVisitor)(struct LinkedNode *node, void *context);
struct ListCallbackContext { struct RecordCapture *argument; RecordCallback callback; };
struct BattleContextLists { u32 unknown_words[6]; struct ListOwner *payloads_at_18; };
extern void VisitLinkedNodes(const struct ListOwner *owner, ListNodeVisitor visitor, void *context);
extern u32 VisitListOwnerWord(struct LinkedNode *node, void *context);
extern u32 AppendBattleUnitRecordAddress(u32 record, struct RecordCapture *capture);

u32 CollectContextListPayloadsAt18(const struct BattleContextLists *context, u32 *output)
{
    struct RecordCapture capture;
    struct ListCallbackContext visit_context;
    RecordCallback append;
    capture.count = 0;
    capture.cursor = output;
    append = AppendBattleUnitRecordAddress;
    visit_context.argument = &capture;
    visit_context.callback = append;
    VisitLinkedNodes(context->payloads_at_18, VisitListOwnerWord, &visit_context);
    return capture.count;
}

__asm__(".global AppendBattleUnitRecordAddress\n.thumb_set AppendBattleUnitRecordAddress,0x0809ac21");
