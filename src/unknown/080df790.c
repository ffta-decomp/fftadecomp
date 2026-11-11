/* Contributed by gg; original source and attribution follow. */
/* RemainingBand43_000DF790
   entry 0x080DF790, 16 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned short u16;
struct TaskNode;
extern void WriteTaskState(struct TaskNode *, u16);
__asm__(".global WriteTaskState\n.thumb_set WriteTaskState,0x08005ba9");
/* C09 requests this state; actual destruction belongs to the real task. */
void RequestUnitTaskClose(struct TaskNode *task)
{
    WriteTaskState(task, 0x103);
}
