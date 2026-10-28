typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Task;
struct Source;
struct Event {u16 state;u8 unused2[2];struct Source **source_slot;u8 unused8[12];u16 mode;u8 unused22[6];};
extern struct Task *CreateTask(const void *,u32,struct Event *,struct Task *);
extern const u8 gActionCopySequenceEntry[];
struct Task *CreateActionCopySequence(u8 mode,struct Source **source_slot,struct Task *parent)
{
    struct Event event;
    event.mode=mode;
    event.source_slot=source_slot;
    return CreateTask(gActionCopySequenceEntry,28,&event,parent);
}
__asm__(".global RemainingBand43_000F11A8\n.thumb_set RemainingBand43_000F11A8, CreateActionCopySequence\n.global CreateTask\n.thumb_set CreateTask, 0x08005b6d\n.global gActionCopySequenceEntry\n.set gActionCopySequenceEntry, 0x080f0d59");
