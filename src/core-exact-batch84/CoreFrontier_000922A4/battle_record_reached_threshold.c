typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

struct BattleThresholdRecord {
    u8 unknown_00[14];
    s16 current_value;
    u8 unknown_10[8];
    const u8 *encoded_threshold;
};

u32 BattleRecordReachedThreshold(const struct BattleThresholdRecord *record)
{
    const u8 *encoded = record->encoded_threshold;
    int low_byte = encoded[0];
    int threshold = (encoded[1] << 8) | low_byte;
    if (threshold > record->current_value)
        return 0;
    return 1;
}
