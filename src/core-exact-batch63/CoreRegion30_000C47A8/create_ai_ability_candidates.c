typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef void (*ClearAiCandidateBytes)(void *, u32);
extern void *AllocateAiCandidateBytes(u32 byte_count);
extern void PrepareAiAbilityCandidates(u8 *output, void *source_context);
extern u32 CollectAiAbilityCategories(u8 *ability_ids, u16 count, u8 *category_flags);

/* Bind existing implementations; no helper body or instruction island. */
__asm__(".global AllocateAiCandidateBytes\n.thumb_set AllocateAiCandidateBytes,0x08022841\n"
        ".global PrepareAiAbilityCandidates\n.thumb_set PrepareAiAbilityCandidates,0x080c1eb5\n"
        ".global CollectAiAbilityCategories\n.thumb_set CollectAiAbilityCategories,0x080c1c39\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");

u8 *CreateAiAbilityCandidateContext(void *source_context)
    __asm__("CoreRegion30_000C47A8");

u8 *CreateAiAbilityCandidateContext(void *source_context)
{
    u8 *output = AllocateAiCandidateBytes(0x5684);
    (*(ClearAiCandidateBytes *)0x0836d4b8)(output, 0x5684);
    PrepareAiAbilityCandidates(output, source_context);
    /* Preparation owns the count and candidate array; reload after its call. */
    output[0x527e] = CollectAiAbilityCategories(output + 8,
                                               *(u16 *)(output + 0x58),
                                               output + 0x5276);
    return output;
}
