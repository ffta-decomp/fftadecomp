typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct AiActionEvaluationContext {
    void *source_context;
    void *selected_candidate;
    void *primary_actors;
    void *alternate_actors;
    u16 primary_count;
    u16 alternate_count;
    void *subcontext;
    u8 remaining_state[80];
};
typedef char AiEvaluationContextSize[(sizeof(struct AiActionEvaluationContext) == 104) ? 1 : -1];
typedef void (*ClearAiEvaluationBytes)(void *, u32);
extern void ReleaseAiEvaluationSubcontext(void *subcontext);
extern void ReleaseAiEvaluationBytes(void *context);
__asm__(".global ReleaseAiEvaluationSubcontext\n.thumb_set ReleaseAiEvaluationSubcontext,0x080bdb19\n"
        ".global ReleaseAiEvaluationBytes\n.thumb_set ReleaseAiEvaluationBytes,0x08022855\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");

void ReleaseAiActionEvaluationContext(struct AiActionEvaluationContext *context)
    __asm__("CoreRegion30_000C53F8");

/* Preserve the nested context until its existing release helper has consumed it. */
void ReleaseAiActionEvaluationContext(struct AiActionEvaluationContext *context)
{
    ReleaseAiEvaluationSubcontext(context->subcontext);
    (*(ClearAiEvaluationBytes *)0x0836d4b8)(context, 104);
    ReleaseAiEvaluationBytes(context);
}
