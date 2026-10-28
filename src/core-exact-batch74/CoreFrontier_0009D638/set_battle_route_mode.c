typedef unsigned char u8;
typedef unsigned int u32;
struct BattleRouteModeRecord {
    u8 unaccessed_prefix[38];
    u8 processing_mode;
};
void SetBattleRouteProcessingMode(struct BattleRouteModeRecord *record, u32 mode)
{
    record->processing_mode = mode;
}
