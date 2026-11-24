typedef unsigned char u8;
typedef unsigned short u16;
struct Task;
struct PositionedTaskPrefix {u8 unknown0[12];u16 halfword12;};
extern struct PositionedTaskPrefix *GetTaskPayload(struct Task*);
void SetPositionedTaskHalfword12(struct Task*,u16) __asm__("RemainingBand43_000D620C");
void SetPositionedTaskHalfword12(struct Task *task,u16 value)
{
    struct PositionedTaskPrefix *payload=GetTaskPayload(task);
    payload->halfword12=value;
}
__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload,0x08005bfd");
