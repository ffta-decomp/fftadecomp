/* Contributed by gg; original source and attribution follow. */
/* CollectContextTreePayloadsReverseAt18
   entry 0x08099E3C, 44 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef u32 (*RecordWordCallback)(u32 record_address, void *argument);
typedef u32 (*RecordNodeVisitor)(void *node, void *argument);
struct Cap { u32 count; u32 *cursor; };
struct Vis { void *argument; RecordWordCallback callback; };
struct Frame { struct Cap cap; struct Vis vis; };
struct Ctx { u8 prefix[24]; void *owner; };
extern void VisitListRev(void *owner, RecordNodeVisitor visit, void *argument);
extern u32 VisitNodeWord(void *node, void *argument);
extern u32 AppendRecord(u32 record_address, void *argument);
__asm__(".global VisitListRev\n.thumb_set VisitListRev, 0x080c7d71\n.global VisitNodeWord\n.thumb_set VisitNodeWord, 0x0809ac01\n.global AppendRecord\n.thumb_set AppendRecord, 0x0809ac21");
u32 f_target(const struct Ctx *context, u32 *record_addresses)
{
    struct Frame frame;
    RecordWordCallback append;
    struct Vis *visitor;
    frame.cap.count = 0;
    frame.cap.cursor = record_addresses;
    append = AppendRecord;
    frame.vis.argument = &frame.cap;
    visitor = &frame.vis;
    visitor->callback = append;
    VisitListRev(context->owner, VisitNodeWord, visitor);
    return frame.cap.count;
}
