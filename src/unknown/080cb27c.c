typedef unsigned char u8;

extern u8 CountPendingHalfwordRecords(void);
extern void CompactPendingHalfwordRecords(void);
extern void DispatchCompactSaveRecords(void *context, const void *records,
                                       int count, int record_size,
                                       const void *completion_callback);

/* Compact the observed 20-halfword queue before submitting its occupied span. */
void CompactPendingHalfwordRecordsAndDispatch(void *context)
{
    u8 count = CountPendingHalfwordRecords();

    if (count != 0) {
        CompactPendingHalfwordRecords();
        DispatchCompactSaveRecords(context, (const void *)0x02001f3c,
                                   count, 2, (const void *)0x080cb63d);
    }
}
