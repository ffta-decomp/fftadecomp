typedef unsigned char u8;

/* This 20-byte application record ends before the unit-record array at +64. */
u8 *GetExchangePrimaryRecordView(void *state)
{
    return (u8 *)state + 42;
}
