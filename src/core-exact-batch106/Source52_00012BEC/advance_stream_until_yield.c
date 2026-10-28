typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct InputSnapshot { u16 held; volatile u16 pressed; };
extern struct InputSnapshot gInputSnapshot;
__asm__(".global gInputSnapshot\n.set gInputSnapshot,0x03000000");
struct StreamContext {
    u8 unaccessed0[8];
    u8 state;
    u8 unaccessed9[19];
    u8 yield_requested;
};
extern u8 AdvanceCurrentStream(u8 skip);
__asm__(".global AdvanceCurrentStream\n.thumb_set AdvanceCurrentStream,0x08012951");
#define CURRENT_STREAM (*(struct StreamContext **)0x0200918c)
void AdvanceStreamUntilYield(void)
{
    u32 skip = 0;
    u32 previous_state;
    struct InputSnapshot *input;
    struct StreamContext **stream_slot = (struct StreamContext **)0x0200918c;
    __asm__("" : "+r"(stream_slot));
    goto advance;
check_input:
    input = &gInputSnapshot;
    if (input->pressed & 3)
        skip = 1;
    if ((*stream_slot)->yield_requested == 1 || skip == 0)
        return;
advance:
    previous_state = (*stream_slot)->state;
    if ((u8)AdvanceCurrentStream(skip) == previous_state)
        goto check_input;
}
