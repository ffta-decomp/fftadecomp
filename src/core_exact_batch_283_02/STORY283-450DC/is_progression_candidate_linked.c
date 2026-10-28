typedef unsigned char u8;
typedef unsigned int u32;
struct ProgressionLink { u8 unknown00[2]; u8 enabled; u8 target; };
struct ProgressionCandidate { struct ProgressionLink links[4]; u8 unknown10[4]; };
struct ProgressionLinkContext { u8 unknown000[0x67c]; const struct ProgressionCandidate * volatile candidates; };
extern struct ProgressionLinkContext * volatile progression_link_context;
asm(".global progression_link_context\n.set progression_link_context,0x03002810");

u8 IsProgressionCandidateLinked(u32 candidate_input,u32 target_input)
{
    u8 candidate=candidate_input;
    u8 target=target_input;
    if(candidate==target) return 1;
    /* Each pair uses the original fresh owner/table snapshot. */
    {
        const struct ProgressionCandidate *records=progression_link_context->candidates;
        const struct ProgressionCandidate *record=(const struct ProgressionCandidate *)((u32)candidate*sizeof(*records)+(u32)records);
        if(record->links[0].enabled && record->links[0].target==target) return 1;
    }
    {
        const struct ProgressionCandidate *records=progression_link_context->candidates;
        const struct ProgressionCandidate *record=(const struct ProgressionCandidate *)((u32)candidate*sizeof(*records)+(u32)records);
        if(record->links[1].enabled && record->links[1].target==target) return 1;
    }
    {
        const struct ProgressionCandidate *records=progression_link_context->candidates;
        const struct ProgressionCandidate *record=(const struct ProgressionCandidate *)((u32)candidate*sizeof(*records)+(u32)records);
        if(record->links[2].enabled && record->links[2].target==target) return 1;
    }
    {
        const struct ProgressionCandidate *records=progression_link_context->candidates;
        const struct ProgressionCandidate *record=(const struct ProgressionCandidate *)((u32)candidate*sizeof(*records)+(u32)records);
        if(record->links[3].enabled && record->links[3].target==target) return 1;
    }
    return 0;
}
