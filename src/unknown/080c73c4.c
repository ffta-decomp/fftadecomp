typedef unsigned short u16;
typedef unsigned char u8;
extern void InitializeSequence(void *sequence, void *owner, u16 size, u8 mode);
__asm__(".global InitializeSequence\n.thumb_set InitializeSequence, 0x080c5d61");

void InitializeBattleContinuationSequence(void *sequence, void *owner,
                                          u16 size, u8 mode)
    __asm__("CoreRegion30_000C73C4");
void InitializeBattleContinuationSequence(void *sequence, void *owner,
                                          u16 size, u8 mode)
{
    InitializeSequence(sequence, owner, size, mode);
}
