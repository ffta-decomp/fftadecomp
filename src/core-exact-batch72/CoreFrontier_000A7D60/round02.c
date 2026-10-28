typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct OwnerRecord;
struct OwnerStateProgress { u16 current, count; u16 history[0]; };
struct OwnerCommandSequence {
    struct OwnerRecord *owner;
    void *command;
    struct OwnerStateProgress progress;
};
typedef char CurrentOffset[(u32)&((struct OwnerCommandSequence *)0)->progress.current==8?1:-1];
typedef char CountOffset[(u32)&((struct OwnerCommandSequence *)0)->progress.count==10?1:-1];
typedef char HistoryOffset[(u32)&((struct OwnerCommandSequence *)0)->progress.history==12?1:-1];
extern void (*const ClearOwnerCommandMemory)(void *destination, u32 bytes);
__asm__(".global ClearOwnerCommandMemory\n.set ClearOwnerCommandMemory, 0x0836d4b8\n.global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");
static inline void PushOwnerCommandState(struct OwnerCommandSequence *sequence, u16 state)
{
    sequence->progress.history[sequence->progress.count++] = state;
}
void InitializeOwnerCommandSequence(struct OwnerCommandSequence *sequence,
                                   struct OwnerRecord *owner)
{
    u16 final_state;
    ClearOwnerCommandMemory(sequence, 80);
    sequence->owner = owner;
    final_state = 0;
    sequence->progress.current = 8;
    PushOwnerCommandState(sequence, 8);
    sequence->progress.current = 5;
    PushOwnerCommandState(sequence, 5);
    sequence->progress.current = 3;
    PushOwnerCommandState(sequence, 3);
    sequence->progress.current = 4;
    PushOwnerCommandState(sequence, 4);
    sequence->progress.current = 2;
    PushOwnerCommandState(sequence, 2);
    sequence->progress.current = final_state;
}
