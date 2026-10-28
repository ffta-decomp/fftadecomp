typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 gContextGate;
extern u16 gTrackedContextState;
extern void DispatchIndexedDefinition(u16 index);
__asm__(".set gContextGate,0x020084d8\n"
        ".set gTrackedContextState,0x020084d4\n"
        ".thumb_set DispatchIndexedDefinition,0x081451c1");
void DispatchTrackedContextState(u32 request_word)
    __asm__("CoreFrontier_001416DC");
void DispatchTrackedContextState(u32 request_word)
{
    u16 request = request_word;
    if (gContextGate & 1) {
        DispatchIndexedDefinition(request);
        /* Store the caller's narrowed snapshot after the real dispatch. */
        gTrackedContextState = request;
    }
}
