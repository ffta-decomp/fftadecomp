typedef unsigned char u8;
typedef unsigned int u32;
struct OwnerCommandSequence;
extern u32 AdvanceOwnerCommandSequence(struct OwnerCommandSequence *sequence);
__asm__(".global AdvanceOwnerCommandSequence\n.thumb_set AdvanceOwnerCommandSequence, 0x080a7de1");
/* The phase controller uses the original adapter's low-byte status. */
u32 PollOwnerCommandSequence(struct OwnerCommandSequence *sequence)
{
    return (u8)AdvanceOwnerCommandSequence(sequence);
}
