typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ItemDefinition {
    u16 name_id;
    u16 unknown_at_02;
    u16 unknown_at_04;
    u16 unknown_at_06;
    u8 properties_at_08[6];
    u16 unknown_at_0e;
    signed char modifiers[8];
    u8 unknown_at_18[5];
    u8 ability_set;
    u8 unknown_at_1e[2];
};

typedef char ItemDefinitionSizeMustBe32[(sizeof(struct ItemDefinition) == 32) ? 1 : -1];

extern const struct ItemDefinition gItems[];
extern u8 ReadSaveByte(u16 index);

/* Selectors name only fields whose role is supported by callers or data use. */
u32 GetItemProperty(u16 item_id, u8 property)
{
    const struct ItemDefinition *item = &gItems[item_id];

    switch (property) {
    case 0: return item->name_id;
    case 1: return item->unknown_at_02;
    case 2: return item->unknown_at_04;
    case 3: return item->properties_at_08[0];
    case 4: return item->properties_at_08[1];
    case 5: return item->properties_at_08[2];
    case 6: return item->properties_at_08[3];
    case 7: return item->properties_at_08[4];
    case 8: return item->properties_at_08[5];
    case 9: return item->unknown_at_0e;
    case 10:
        if (ReadSaveByte(13)) return item->modifiers[0];
        else {
            u32 value = item->modifiers[0];
            if (item_id == 51) value += ReadSaveByte(1);
            if (value > 255) value = 255;
            return value;
        }
    case 11:
        if (ReadSaveByte(13)) return item->modifiers[1];
        else {
            u32 value = item->modifiers[1];
            if (item_id == 302) value += ReadSaveByte(3);
            if (value > 255) value = 255;
            return value;
        }
    case 12:
        if (ReadSaveByte(13)) return item->modifiers[2];
        else {
            u32 value = item->modifiers[2];
            if (item_id == 148) value += ReadSaveByte(2);
            if (value > 255) value = 255;
            return value;
        }
    case 13:
        if (ReadSaveByte(13)) return item->modifiers[3];
        else {
            u32 value = item->modifiers[3];
            if (item_id == 286) value += ReadSaveByte(4);
            if (value > 255) value = 255;
            return value;
        }
    case 14: return item->modifiers[4];
    case 15: return item->modifiers[5];
    case 16: return item->modifiers[6];
    case 17: return item->modifiers[7];
    case 18: return item->ability_set;
    default: return 0;
    }
}

/* Keep the original zero-filled alignment after this independently built span. */
asm(".align 2, 0");
