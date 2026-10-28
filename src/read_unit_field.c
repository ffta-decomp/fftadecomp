/* Reads a value or an address from the observed battle-unit record layout. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct BattleUnitFieldView {
    u32 word_00;
    u8 bytes_04[0x14];
    u16 halfwords_18[14];
    u8 reserved_34[0x9c];
    s16 charge_fields_d0[3];
    u16 field_d6;
    u8 counters_d8[0x10];
    u8 state_bytes_e8[9];
    u8 bytes_f1[0x0b];
    u8 tail_fc[0];
};

u32 ReadUnitField(const struct BattleUnitFieldView *unit, u8 selector)
{
    switch (selector) {
    case 0: return unit->word_00;
    case 1: return unit->bytes_04[0];
    case 2: return unit->bytes_04[1];
    case 3: return unit->bytes_04[2];
    case 4: return unit->bytes_04[3];
    case 5: return unit->bytes_04[4];
    case 6: return unit->bytes_04[5];
    case 7: return unit->bytes_04[6];
    case 8: return unit->bytes_04[7];
    case 9: return (u32)&unit->bytes_04[8];
    case 10: return unit->bytes_04[8];
    case 11: return unit->bytes_04[9];
    case 12: return unit->bytes_04[10];
    case 13: return unit->bytes_04[11];
    case 14: return unit->bytes_04[12];
    case 15: return unit->bytes_04[13];
    case 16: return unit->bytes_04[14];
    case 17: return unit->bytes_04[15];
    case 18: return unit->bytes_04[16];
    case 19: return unit->halfwords_18[0];
    case 20: return unit->halfwords_18[1];
    case 21: return unit->halfwords_18[2];
    case 22: return unit->halfwords_18[3];
    case 23: return unit->halfwords_18[4];
    case 24: return unit->halfwords_18[5];
    case 25: return unit->halfwords_18[6];
    case 26: return unit->halfwords_18[7];
    case 27: return unit->halfwords_18[8];
    case 28: return (u32)&unit->halfwords_18[9];
    case 29: return unit->halfwords_18[9];
    case 30: return unit->halfwords_18[10];
    case 31: return unit->halfwords_18[11];
    case 32: return unit->halfwords_18[12];
    case 33: return unit->halfwords_18[13];
    case 34: return (u32)unit->reserved_34;
    case 35: return unit->charge_fields_d0[0];
    case 36: return unit->charge_fields_d0[1];
    case 37: return unit->charge_fields_d0[2];
    case 38: return unit->field_d6;
    case 39: return (u32)unit->counters_d8;
    case 40: return unit->counters_d8[0];
    case 41: return unit->counters_d8[1];
    case 42: return unit->counters_d8[2];
    case 43: return unit->counters_d8[3];
    case 44: return unit->counters_d8[4];
    case 45: return unit->counters_d8[5];
    case 46: return unit->counters_d8[6];
    case 47: return unit->counters_d8[7];
    case 48: return unit->counters_d8[8];
    case 49: return unit->counters_d8[9];
    case 50: return unit->counters_d8[10];
    case 51: return unit->counters_d8[11];
    case 52: return unit->counters_d8[12];
    case 53: return unit->counters_d8[13];
    case 54: return unit->counters_d8[14];
    case 55: return unit->counters_d8[15];
    case 56: return (u32)unit->state_bytes_e8;
    case 57: return unit->bytes_f1[0];
    case 58: return unit->bytes_f1[1];
    case 59: return unit->bytes_f1[2];
    case 60: return unit->bytes_f1[3];
    case 61: return unit->bytes_f1[4];
    case 62: return unit->bytes_f1[5];
    case 63: return unit->bytes_f1[6];
    case 64: return unit->bytes_f1[7];
    case 65: return unit->bytes_f1[8];
    case 66: return unit->bytes_f1[9];
    case 67: return unit->bytes_f1[10];
    case 68: return (u32)unit->tail_fc;
    default: return 0;
    }
}
