/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Unit;
struct ItemCodes {
    u8 prefix[26];
    u8 codes[3];
    u8 suffix[3];
};
typedef char ItemSizeCheck[sizeof(struct ItemCodes) == 32 ? 1 : -1];
typedef char CodeOffsetCheck[(u32)&((struct ItemCodes *)0)->codes == 26 ? 1 : -1];
extern const struct ItemCodes gItemCodes[];
extern u32 ReadUnitField(const struct Unit *unit, u8 selector);
extern int RemapClassification(s8 value);
__asm__(".global gItemCodes\n.set gItemCodes, 0x0851d180");
__asm__(".global ReadUnitField\n.thumb_set ReadUnitField, 0x080c7ea5");
__asm__(".global RemapClassification\n.thumb_set RemapClassification, 0x0812f8e9");


/* Apply the original item-code remaps in equipped-slot order. */
void ApplyEquipmentClassificationRemaps(const struct Unit *unit, s8 *classification)
{
    u16 seen = 0;
    int slot;
    int code_index;
    u32 item_id;
    const struct ItemCodes *item;
    u8 code;
    for (slot = 0; slot < 5; ++slot) {
        item_id = ReadUnitField(unit, slot + 29);
        if (item_id == 0)
            continue;
        item = &gItemCodes[item_id];
        for (code_index = 0; code_index < 3; ++code_index) {
            code = item->codes[code_index];
            if ((seen >> code) & 1)
                continue;
            seen |= 1 << code;
            switch (code) {
            case 5:
                classification[1] = RemapClassification(classification[1]);
                break;
            case 10:
                classification[2] = RemapClassification(classification[2]);
                break;
            case 15:
                classification[3] = RemapClassification(classification[3]);
                break;
            case 20:
                classification[4] = RemapClassification(classification[4]);
                break;
            case 25:
                classification[5] = RemapClassification(classification[5]);
                break;
            case 30:
                classification[6] = RemapClassification(classification[6]);
                break;
            case 35:
                classification[7] = RemapClassification(classification[7]);
                break;
            case 40:
                classification[8] = RemapClassification(classification[8]);
                break;
            }
        }
    }
}
