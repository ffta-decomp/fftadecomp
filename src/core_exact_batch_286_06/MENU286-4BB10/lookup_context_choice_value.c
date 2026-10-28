typedef unsigned char u8;
typedef unsigned int u32;
typedef struct ContextChoiceSlot {
    u8 unknown00[2];
    u8 value;
    u8 key;
} ContextChoiceSlot;
typedef struct ContextChoiceRow {
    ContextChoiceSlot slots[4];
    u8 unknown10[4];
} ContextChoiceRow;
typedef char ChoiceRowSize[(sizeof(ContextChoiceRow) == 20) ? 1 : -1];
extern const ContextChoiceRow gContextChoiceRows[];
asm(".global gContextChoiceRows\n.set gContextChoiceRows,0x08391e40\n");
u32 LookupContextChoiceValue(u8 row_id, u8 key) asm("CoreRegion_0004BB10");
u32 LookupContextChoiceValue(u8 row_id, u8 key)
{
    const ContextChoiceRow *rows = gContextChoiceRows;
    const ContextChoiceRow *row = rows + row_id;
    /* Preserve first-match ordering; the row/key domains remain unknown. */
    if (row->slots[0].key == key)
        return row->slots[0].value;
    else if (row->slots[1].key == key)
        return row->slots[1].value;
    else if (row->slots[2].key == key)
        return row->slots[2].value;
    else if (row->slots[3].key == key)
        return row->slots[3].value;
    else
        return 255;
}
