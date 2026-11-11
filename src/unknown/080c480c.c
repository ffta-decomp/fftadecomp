typedef unsigned int u32;
typedef void (*ClearAiCandidateBytes)(void *, u32);
extern void ReleaseAiCandidateBytes(void *context);
__asm__(".global ReleaseAiCandidateBytes\n.thumb_set ReleaseAiCandidateBytes,0x08022855\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");

void ReleaseAiAbilityCandidateContext(void *context)
    __asm__("CoreRegion30_000C480C");

/* The AI transaction publishes its candidate arrays before this cleanup. */
void ReleaseAiAbilityCandidateContext(void *context)
{
    (*(ClearAiCandidateBytes *)0x0836d4b8)(context, 0x5684);
    ReleaseAiCandidateBytes(context);
}
