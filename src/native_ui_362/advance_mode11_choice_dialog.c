typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ChoiceEvent { u16 phase; u8 payload[18]; u16 mode; };
struct Mode11Work { void *owner; u16 flags; u16 value; u8 mode, message; u8 unused10[2]; void *dialog; };
struct MessageState { u8 unused00[12]; u16 message; };
struct NativeDialogResource;
extern void *choice_owner;
extern struct MessageState message_state;
extern const u8 choice_text_bank[];
extern struct NativeDialogResource dialog_resource;
extern u32 dialog_auxiliary;
extern void *AllocateChoiceWork(u32);
extern void FreeChoiceWork(void *);
extern void InitializeDialogContext(void *, const u8 *, struct NativeDialogResource *, u32, u16);
/* First coordinate is the original full-word -1 carrier at this call site. */
extern void OpenChoiceDialog(int, u32, u16, u8, u16, const void *);
extern u32 PollChoiceDialog(void);
extern void SetDialogFlag1(void);
extern void ClearChoiceViewport(u32, u32, u32, u32);
extern void RequestFixedDefinition(u32);
extern void RequestDefinitionRoute(int, int);
__asm__(".global choice_owner\n.set choice_owner,0x0200f454\n"
        ".global message_state\n.set message_state,0x020020d0\n"
        ".global choice_text_bank\n.set choice_text_bank,0x084c3e60\n"
        ".global dialog_resource\n.set dialog_resource,0x030008b0\n"
        ".global dialog_auxiliary\n.set dialog_auxiliary,0x03000990\n"
        ".global AllocateChoiceWork\n.thumb_set AllocateChoiceWork,0x08005b29\n"
        ".global FreeChoiceWork\n.thumb_set FreeChoiceWork,0x08005b41\n"
        ".global InitializeDialogContext\n.thumb_set InitializeDialogContext,0x080185c9\n"
        ".global OpenChoiceDialog\n.thumb_set OpenChoiceDialog,0x08018625\n"
        ".global PollChoiceDialog\n.thumb_set PollChoiceDialog,0x08018791\n"
        ".global SetDialogFlag1\n.thumb_set SetDialogFlag1,0x08018aa9\n"
        ".global ClearChoiceViewport\n.thumb_set ClearChoiceViewport,0x0802a2c1\n"
        ".global RequestFixedDefinition\n.thumb_set RequestFixedDefinition,0x08141541\n"
        ".global RequestDefinitionRoute\n.thumb_set RequestDefinitionRoute,0x08141571");
u32 AdvanceMode11ChoiceDialog(void *, struct ChoiceEvent *, struct Mode11Work *) __asm__("RemainingCore48_00065B58");
u32 AdvanceMode11ChoiceDialog(void *task, struct ChoiceEvent *event, struct Mode11Work *work)
{
    switch (event->phase) {
    case 1:
        if (work->dialog) {
            FreeChoiceWork(work->dialog);
            work->dialog = 0;
        }
        break;
    case 0:
        work->mode = event->mode;
        work->owner = choice_owner;
        work->message = message_state.message;
        ClearChoiceViewport(0, 0, 30, 20);
        break;
    case 256:
        {
            void *dialog = AllocateChoiceWork(984);
            u32 message;
            work->dialog = dialog;
            InitializeDialogContext(dialog, choice_text_bank, &dialog_resource,
                                    (u32)&dialog_auxiliary, 448);
            message = work->message;
            if (message == 25 || message == 27 || message == 28) {
                /* Each original call consumes a fresh callback-visible message byte. */
                __asm__("" : : : "memory");
                OpenChoiceDialog(-1, 10, work->message, 20, 0, 0);
            } else {
                __asm__("" : : : "memory");
                OpenChoiceDialog(-1, 10, work->message, 0, 0, 0);
            }
            event->phase = 260;
        }
        break;
    case 260:
        if ((u16)PollChoiceDialog()) {
            u32 flags = work->flags;
            if (flags & 64) {
                u32 cleared_flags = 0xFFBF;
                /* Actual full-word mask is the destructive AND working value. */
                __asm__("" : "+r"(cleared_flags));
                cleared_flags &= flags;
                work->flags = cleared_flags;
                event->phase = 259;
            } else {
                u32 message = work->message;
                register u32 working_message __asm__("r0");
                if ((u8)(message - 16) <= 1)
                    goto common_definition;
                /* Only the failed narrow-range path defines this full-word stage. */
                working_message = message;
                __asm__("" : "+r"(working_message));
                if (working_message == 13)
                    goto common_definition;
                if (working_message == 14) {
common_definition:
                    RequestDefinitionRoute(1, 8);
                } else {
                    if (working_message == 25)
                        RequestFixedDefinition(112);
                    else if (working_message == 27)
                        RequestFixedDefinition(100);
                    else if (working_message == 28)
                        RequestDefinitionRoute(1, 107);
                }
                event->phase = 262;
            }
        }
        break;
    case 262:
        {
            u32 flags = work->flags;
            if (flags & 128) {
                u32 cleared_flags = 0xFF7F;
                /* Actual full-word mask is the destructive AND working value. */
                __asm__("" : "+r"(cleared_flags));
                cleared_flags &= flags;
                work->flags = cleared_flags;
                event->phase = 3;
            } else {
                u32 resume_requested = 64;
                __asm__("" : "+r"(resume_requested));
                resume_requested &= flags;
                if (resume_requested) {
                    SetDialogFlag1();
                    event->phase = 260;
                }
            }
        }
        break;
    case 259:
        FreeChoiceWork(work->dialog);
        work->dialog = 0;
        ClearChoiceViewport(0, 0, 30, 10);
        work->value = 0xFFFE;
        event->phase = 262;
        break;
    }
    return 0;
}
