/* Contributed by gg; original source and attribution follow. */
/* RemainingBand43_000D3A14
   entry 0x080D3A14, 28 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned short u16;
struct TaskNode;
struct TaskPayloadFlags { u16 unknown_at_00; u16 flags; };
extern void *GetTaskPayload(struct TaskNode *node);
__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload, 0x08005bfd");
void SetManagedTaskPayloadBitZero(void) __asm__("f_target");
void SetManagedTaskPayloadBitZero(void)
{
    struct TaskPayloadFlags *payload = GetTaskPayload(*(struct TaskNode **)0x020159c0);
    payload->flags |= 0x20;
}
