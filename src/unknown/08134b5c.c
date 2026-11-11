typedef unsigned char u8;
typedef unsigned int u32;

typedef struct EffectSelectionRecord {
    u8 rank;
    u8 metadata[15]; /* The complete payload is copied without interpretation. */
} EffectSelectionRecord;
typedef void (*RecordCopy)(void *, const void *, u32);
extern RecordCopy gRecordCopy;
extern void CallRecordCopy(void *, const void *, u32, RecordCopy);
__asm__(".global gRecordCopy\n.set gRecordCopy,0x0836d4bc\n"
        ".global CallRecordCopy\n.thumb_set CallRecordCopy,0x08142251\n");

/* A tie keeps the earlier winner; a zero candidate does not read the winner. */
void RetainHigherRankEffectRecord(EffectSelectionRecord *winner,
                                 const EffectSelectionRecord *candidate)
{
    u32 candidate_rank = candidate->rank;
    u32 winner_rank;
    if (candidate_rank == 0)
        return;
    winner_rank = winner->rank;
    if (winner_rank > candidate_rank)
        return;
    if (winner_rank == candidate_rank)
        return;
    CallRecordCopy(winner, candidate, 16, gRecordCopy);
}
