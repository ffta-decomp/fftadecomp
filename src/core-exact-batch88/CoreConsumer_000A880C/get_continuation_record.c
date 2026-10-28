struct ContinuationRecord;

/* Callers consume the unchanged full pointer; this is not a void no-op. */
struct ContinuationRecord *GetContinuationRecord(struct ContinuationRecord *record)
    __asm__("CoreConsumer_000A880C");
struct ContinuationRecord *GetContinuationRecord(struct ContinuationRecord *record)
{
    return record;
}
