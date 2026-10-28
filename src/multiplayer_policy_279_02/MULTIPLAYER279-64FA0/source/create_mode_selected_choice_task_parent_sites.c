#include "../../../../src/task_tree_core.h"
/* Real5954 copies seven words, then overwrites event code0 before callback.
 * Only the halfword at20 is initialized here; do not invent zeroed fields.
 */
struct ChoiceTaskEvent {
    u32 words0_19[5];
    u16 mode;
    u8 unspecified22_27[6];
};
typedef char ChoiceEventSize28[(sizeof(struct ChoiceTaskEvent) == 28) ? 1 : -1];
extern TaskGroup **gChoiceOwner;
extern void StandardChoiceCallback(TaskNode *, u16 *, void *);
extern void Mode4ChoiceCallback(TaskNode *, u16 *, void *);
extern void Mode9Or10ChoiceCallback(TaskNode *, u16 *, void *);
extern void Mode11ChoiceCallback(TaskNode *, u16 *, void *);
extern TaskNode *CreateChoiceTask(TaskGroup *, TaskCallback, u32, const u32 *, TaskNode *);
asm(".global gChoiceOwner\n.set gChoiceOwner,0x0200f454\n"
    ".global StandardChoiceCallback\n.thumb_set StandardChoiceCallback,0x080651fd\n"
    ".global Mode4ChoiceCallback\n.thumb_set Mode4ChoiceCallback,0x08065609\n"
    ".global Mode9Or10ChoiceCallback\n.thumb_set Mode9Or10ChoiceCallback,0x080659ad\n"
    ".global Mode11ChoiceCallback\n.thumb_set Mode11ChoiceCallback,0x08065b59\n"
    ".global CreateChoiceTask\n.thumb_set CreateChoiceTask,0x08005955\n");
TaskNode *RemainingCore48_00064FA0(u8 mode)
{
    struct ChoiceTaskEvent event;
    event.mode = mode;
    switch (mode) {
    case 9:
    case 10:
        return CreateChoiceTask(*gChoiceOwner, Mode9Or10ChoiceCallback, 52,
                                (const u32 *)&event, 0);
    case 11:
        return CreateChoiceTask(*gChoiceOwner, Mode11ChoiceCallback, 16,
                                (const u32 *)&event, 0);
    case 4:
        return CreateChoiceTask(*gChoiceOwner, Mode4ChoiceCallback, 220,
                                (const u32 *)&event, 0);
    default:
        return CreateChoiceTask(*gChoiceOwner, StandardChoiceCallback, 220,
                                (const u32 *)&event, 0);
    }
}
