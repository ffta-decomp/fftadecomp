typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SequenceContext;
extern u8 gContextGate;
extern u16 gTrackedContextState;
extern struct SequenceContext gFixedContext;
extern void ApplyContextRequest(struct SequenceContext *context, u32 request);
__asm__(".set gContextGate,0x020084d8\n"
        ".set gTrackedContextState,0x020084d4\n"
        ".set gFixedContext,0x0200f2a0\n"
        ".thumb_set ApplyContextRequest,0x08145359");
void ResetTrackedContextState(u32 request_word)
    __asm__("CoreFrontier_00141748");
void ResetTrackedContextState(u32 request_word)
{
    u16 request = request_word;
    if (gContextGate & 1) {
        ApplyContextRequest(&gFixedContext, request);
        /* The tracked-state reset follows the real helper's effects. */
        gTrackedContextState = 0xffff;
    }
}
