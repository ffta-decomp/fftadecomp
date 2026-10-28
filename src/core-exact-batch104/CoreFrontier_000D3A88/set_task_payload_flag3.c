typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TaskNode;
struct TaskPayload { u16 unaccessed0; u16 flags; };
extern struct TaskPayload *GetCurrentTaskPayload(struct TaskNode *);
__asm__(".global GetCurrentTaskPayload\n.thumb_set GetCurrentTaskPayload,0x08005bfd");
void SetCurrentTaskPayloadFlag3(u8 disable)
{
    struct TaskPayload *payload = GetCurrentTaskPayload(*(struct TaskNode **)0x020159c0);
    register u32 flags __asm__("r0");
    register u32 previous_flags __asm__("r1");
    if (disable != 0) {
        previous_flags = payload->flags;
        __asm__("" : "+r"(previous_flags));
        flags = 0xfff7;
        flags &= previous_flags;
    } else {
        previous_flags = payload->flags;
        __asm__("" : "+r"(previous_flags));
        flags = 8;
        flags |= previous_flags;
    }
    /* Retail keeps the merged full-word result in r0 until the halfword store. */
    __asm__("" : "+r"(flags));
    payload->flags = flags;
}
