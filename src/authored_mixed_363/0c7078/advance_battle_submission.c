typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SubmissionTransfer { u8 prefix[8]; void *buffer; u8 remainder[84]; };
struct BattleSubmissionContext { void *record; struct SubmissionTransfer transfer; u16 phase; };
struct BattleSubmissionFlags { u8 prefix[172]; u8 value; u8 reserved; u8 flags; };
struct BattleSubmissionInput { u8 prefix[2]; u8 mode; u8 gap[285]; u16 active; u16 value; };
typedef char TransferAt4[(u32)&((struct BattleSubmissionContext *)0)->transfer == 4 ? 1 : -1];
typedef char PhaseAt100[(u32)&((struct BattleSubmissionContext *)0)->phase == 100 ? 1 : -1];
typedef char BufferAt8[(u32)&((struct SubmissionTransfer *)0)->buffer == 8 ? 1 : -1];
typedef char InputAt288[(u32)&((struct BattleSubmissionInput *)0)->active == 288 ? 1 : -1];
extern struct BattleSubmissionFlags SubmissionFlags;
extern struct BattleSubmissionInput SubmissionInput;
extern u8 SubmissionWaitStart[], SubmissionWaitEnd[];
extern void BeginBattleSubmissionWait(void);
extern u32 QueryBattleSubmissionWait(const void *start, const void *end);
extern u32 QueryBattleSubmissionMode(void);
extern void InitializeSubmissionTransfer(struct SubmissionTransfer *, void *, u32, u32);
extern u32 PollSubmissionTransfer(struct SubmissionTransfer *);
extern void ReleaseSubmissionBuffer(void *);
__asm__(".global SubmissionFlags\n.set SubmissionFlags,0x02015738\n.global SubmissionInput\n.set SubmissionInput,0x030028a0\n.global SubmissionWaitStart\n.set SubmissionWaitStart,0x08149a70\n.global SubmissionWaitEnd\n.set SubmissionWaitEnd,0x08149a7c\n.global BeginBattleSubmissionWait\n.thumb_set BeginBattleSubmissionWait,0x08005029\n.global QueryBattleSubmissionWait\n.thumb_set QueryBattleSubmissionWait,0x08003b1d\n.global QueryBattleSubmissionMode\n.thumb_set QueryBattleSubmissionMode,0x08004d69\n.global InitializeSubmissionTransfer\n.thumb_set InitializeSubmissionTransfer,0x080c5d61\n.global PollSubmissionTransfer\n.thumb_set PollSubmissionTransfer,0x080c5f95\n.global ReleaseSubmissionBuffer\n.thumb_set ReleaseSubmissionBuffer,0x08022855");
/* Phase4 alone reports completion. All other phases, including unknown ones,
 * return pending; the transfer helpers remain the original implementations. */
u32 AdvanceBattleSubmission(struct BattleSubmissionContext *context, u8 mode) __asm__("CoreFrontier_000C7078");
u32 AdvanceBattleSubmission(struct BattleSubmissionContext *context, u8 mode)
{
    switch (context->phase) {
    case 0:
        BeginBattleSubmissionWait();
        context->phase = 1;
        break;
    case 1:
        if (QueryBattleSubmissionWait(SubmissionWaitStart, SubmissionWaitEnd) != 0)
            context->phase = 2;
        break;
    case 2:
        if (mode != 0)
            InitializeSubmissionTransfer(&context->transfer, context->record, 24, 0);
        else
            InitializeSubmissionTransfer(&context->transfer, context->record, 24, 1);
        context->phase = 3;
        break;
    case 3:
        {
            register struct SubmissionTransfer *transfer __asm__("r4") = &context->transfer;
            register struct SubmissionTransfer *cleanup __asm__("r6");
            u32 flag64;
            register u32 pending __asm__("r1");
            u32 result;
            flag64 = SubmissionFlags.flags & 64;
            /* The real copy keeps cleanup alive after R4 becomes the narrowed result. */
            __asm__("add %0, %1, #0"
                : "=&l" (cleanup) : "l" (transfer) : "cc");
            if (flag64) {
                if (SubmissionFlags.flags & 128)
                    pending = QueryBattleSubmissionMode() != 1;
                else
                    pending = 0;
            } else {
                if ((SubmissionFlags.flags & 32) || SubmissionFlags.value > 13) {
                    if (SubmissionInput.active != 0)
                        goto forced_pending;
                    if (SubmissionInput.mode != 3 && SubmissionInput.value > 16)
                        goto forced_pending;
                }
                if (SubmissionFlags.flags & 8) {
                forced_pending:
                    pending = 1;
                } else {
                    pending = 0;
                }
            }
            /* The actual pending value joins before selecting raw result2 or polling. */
            __asm__("" : "+r" (pending));
            if (pending)
                result = 2;
            else
                result = PollSubmissionTransfer(transfer);
            if ((u8)result == 0) {
                if (cleanup->buffer != 0) {
                    ReleaseSubmissionBuffer(cleanup->buffer);
                    cleanup->buffer = 0;
                }
                context->phase = 4;
            }
        }
        break;
    case 4:
        return 0;
    }
    return 1;
}
