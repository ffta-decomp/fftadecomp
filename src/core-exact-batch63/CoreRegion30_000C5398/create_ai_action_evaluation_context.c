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
extern void *AllocateAiEvaluationBytes(u32 bytes);
extern void *CreateAiEvaluationSubcontext(void);
__asm__(".global AllocateAiEvaluationBytes\n.thumb_set AllocateAiEvaluationBytes,0x08022841\n"
        ".global CreateAiEvaluationSubcontext\n.thumb_set CreateAiEvaluationSubcontext,0x080bdafd\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");

struct AiActionEvaluationContext *CreateAiActionEvaluationContext(
    void *source_context, void *selected_candidate, void *primary_actors,
    u16 primary_count, void *alternate_actors, u16 alternate_count)
    __asm__("CoreRegion30_000C5398");

/* Capture the selected candidate and both prepared actor lists for AI evaluation. */
struct AiActionEvaluationContext *CreateAiActionEvaluationContext(
    void *source_context, void *selected_candidate, void *primary_actors,
    u16 primary_count, void *alternate_actors, u16 alternate_count)
{
    struct AiActionEvaluationContext *output = AllocateAiEvaluationBytes(104);
    (*(ClearAiEvaluationBytes *)0x0836d4b8)(output, 104);
    output->source_context = source_context;
    output->selected_candidate = selected_candidate;
    output->primary_actors = primary_actors;
    output->alternate_actors = alternate_actors;
    output->primary_count = primary_count;
    output->alternate_count = alternate_count;
    output->subcontext = CreateAiEvaluationSubcontext();
    return output;
}
