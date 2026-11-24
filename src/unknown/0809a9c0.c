typedef unsigned char u8;
typedef unsigned int u32;
struct ExchangeUnitRecord { u8 bytes[264]; };
struct ExchangeGameState {
    u8 prefix[64];
    struct ExchangeUnitRecord records[3];
};

/* Full-width index is retained; the application exchange traverses slots 0..2. */
struct ExchangeUnitRecord *GetExchangeUnitRecord(struct ExchangeGameState *state,
                                                u32 index)
{
    return &state->records[index];
}
