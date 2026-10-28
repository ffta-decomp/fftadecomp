typedef unsigned char u8;
typedef unsigned short u16;
union LinkResultFlow {
    struct { u16 selector, depth, continuations[1]; } flow;
    struct { u8 fields_before_pending[77]; u8 pending; } command;
};
extern union LinkResultFlow *gLinkResultFlow;
extern void ClearActiveObjectFlag38(void);
__asm__(".global gLinkResultFlow\n.set gLinkResultFlow,0x0200f450\n.global ClearActiveObjectFlag38\n.thumb_set ClearActiveObjectFlag38,0x08013365");

/* This is the same scene object whose continuation region overlaps its fields. */
void QueueLinkResultContinuation(void)
{
    union LinkResultFlow *flow;
    ClearActiveObjectFlag38();
    flow = gLinkResultFlow;
    flow->flow.selector = 23;
    flow->flow.continuations[flow->flow.depth++] = 23;
    flow->flow.selector = 52;
}
