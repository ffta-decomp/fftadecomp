typedef unsigned char u8;
typedef unsigned int u32;

struct BattleFlagRecord {
    u8 preceding_fields[16];
    u32 flags;
};

typedef char battle_flags_offset[
    ((u32)&((struct BattleFlagRecord *)0)->flags == 16) ? 1 : -1];

/* These selector-to-bit associations are game rules. Their individual status
 * names remain unknown. Unsupported selectors do not read the record. */
u32 TestBattleRecordSelectorFlag(const struct BattleFlagRecord *record,
                                 u8 selector)
{
    u32 flags;
    u32 selector_mask;

    switch (selector) {
    case 0:
        flags = record->flags;
        selector_mask = 0x4000;
check_selected_flag:
        if (flags & selector_mask)
            goto selected;
        goto not_selected;
    case 3:
        flags = record->flags;
        selector_mask = 0x2000;
        goto check_selected_flag;
    case 4:
        flags = record->flags;
        selector_mask = 0x1000;
        goto check_selected_flag;
    case 5:
        flags = record->flags;
        selector_mask = 0x0400;
        goto check_selected_flag;
    case 1:
        flags = record->flags;
        selector_mask = 0x0200;
        goto check_selected_flag;
    case 6:
        flags = record->flags;
        selector_mask = 0x0100;
        goto check_selected_flag;
    case 7:
        if ((record->flags & 0x0080) == 0)
            goto not_selected;
        break;
    default:
        goto not_selected;
    }
selected:
    return 1;
not_selected:
    return 0;
}
