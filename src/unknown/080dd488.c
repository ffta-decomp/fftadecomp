struct ContinuationRecord {
    unsigned char bytes_00_17[18];
    unsigned short field_18;
};

struct ContinuationRecord *GetContinuationRecord(struct ContinuationRecord *record)
    __asm__("UnitContinuationCall_080A880C");

unsigned short ReadContinuationRecordField18(struct ContinuationRecord *record)
    __asm__("RemainingBand43_000DD488");

unsigned short ReadContinuationRecordField18(struct ContinuationRecord *record)
{
    return GetContinuationRecord(record)->field_18;
}
