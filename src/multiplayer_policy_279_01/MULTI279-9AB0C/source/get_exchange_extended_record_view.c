typedef unsigned char u8;

/* The 320-byte exchange view starts at the third 264-byte record's address. */
u8 *GetExchangeExtendedRecordView(void *state)
{
    return (u8 *)state + 592;
}
