typedef unsigned int u32;

extern int CompactSaveRecords64(void);
extern void DispatchCompactSaveRecords(void *context, const void *records,
                                       int count, int record_size,
                                       const void *completion_callback);

/* Notify the supplied save-operation context after compacting the 64-record table. */
void CompactSaveRecordsAndDispatch(void *context)
{
    int count = CompactSaveRecords64();

    if (count != 0) {
        DispatchCompactSaveRecords(context, (const void *)0x02002b08,
                                   count, 4, (const void *)0x080cb635);
    }
}
