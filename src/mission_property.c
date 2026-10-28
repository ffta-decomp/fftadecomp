typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Observed packed 70-byte mission definition; names retain selector evidence. */
typedef struct {
    u16 record_id;
    u32 behavior_code:3, icon_group:3, packed_03:6, packed_04:3,
        packed_07:3, unknown_04:6;
    u16 field_08;
    u8 field_09;
    u16 field_10;
    u8 field_11;
    u16 field_12;
    u8 field_13;
    u32 packed_14:3, field_15:8, field_16:8, packed_17:3,
        field_18:8, unknown_17:2;
    u8 pointer_block_19[4];
    u8 pointer_block_21[4];
    u8 pointer_block_22[4];
    u8 pointer_block_23[4];
    u16 field_25, field_26, field_27, field_28;
    u8 clan_rewards[9];
    u8 gil_reward_units, ap_reward_units, item_reward, required_item_a,
        required_item_b;
    u32 packed_46:4, packed_47:7, packed_48:6, packed_49:4,
        packed_50:7, packed_51:6, packed_52:6;
    u8 excluded_item, field_54, field_57, field_58;
    u16 flags;
    u16 field_59;
    u8 field_60;
} __attribute__((packed)) MissionDefinition;
typedef char MissionDefinitionSize[(sizeof(MissionDefinition) == 70) ? 1 : -1];

extern u16 DecodeMissionItemId(u8 value);
extern const MissionDefinition gMissionDefinitions[];
u32 GetMissionProperty(u16 mission_id, u8 selector)
{
    const MissionDefinition *mission = &gMissionDefinitions[mission_id];
    /* Retain the byte-width flag reads used by the retail switch cases. */
    switch (selector) {
    case 0: return mission->record_id;
    case 1: return mission->behavior_code;
    case 2: return mission->icon_group;
    case 3: return mission->packed_03;
    case 4: return mission->packed_04;
    case 5: return (mission->flags >> 0) & 1;
    case 6: return (u8)(mission->flags >> 1) & 1;
    case 7: return mission->packed_07;
    case 8: return mission->field_08;
    case 9: return mission->field_09;
    case 10: return mission->field_10;
    case 11: return mission->field_11;
    case 12: return mission->field_12;
    case 13: return mission->field_13;
    case 14: return mission->packed_14;
    case 15: return mission->field_15;
    case 16: return mission->field_16;
    case 17: return mission->packed_17;
    case 18: return mission->field_18;
    case 19: case 20: return (u32)mission->pointer_block_19;
    case 21: return (u32)mission->pointer_block_21;
    case 22: return (u32)mission->pointer_block_22;
    case 23: return (u32)mission->pointer_block_23;
    case 24: return (u32)&mission->field_25;
    case 25: return mission->field_25;
    case 26: return mission->field_26;
    case 27: return mission->field_27;
    case 28: return mission->field_28;
    case 29: return mission->item_reward;
    case 30: return mission->gil_reward_units * 200;
    case 31: return mission->ap_reward_units;
    case 32: return (u32)&mission->clan_rewards[0];
    case 33: return mission->clan_rewards[0];
    case 34: return mission->clan_rewards[1];
    case 35: return mission->clan_rewards[2];
    case 36: return mission->clan_rewards[3];
    case 37: return mission->clan_rewards[4];
    case 38: return mission->clan_rewards[5];
    case 39: return mission->clan_rewards[6];
    case 40: return mission->clan_rewards[7];
    case 41: return mission->clan_rewards[8];
    case 42: return DecodeMissionItemId(mission->required_item_a);
    case 43: return (u8)(mission->flags >> 4) & 1;
    case 44: return DecodeMissionItemId(mission->required_item_b);
    case 45: return (u8)(mission->flags >> 5) & 1;
    case 46: return mission->packed_46;
    case 47: return mission->packed_47;
    case 48: return mission->packed_48;
    case 49: return mission->packed_49;
    case 50: return mission->packed_50;
    case 51: return mission->packed_51;
    case 52: return mission->packed_52;
    case 53: return DecodeMissionItemId(mission->excluded_item);
    case 54: return mission->field_54 * 200;
    case 55: return (u8)(mission->flags >> 2) & 1;
    case 56: return (u8)(mission->flags >> 3) & 1;
    case 57: return mission->field_57;
    case 58: return mission->field_58;
    case 59: return mission->field_59;
    case 60: return mission->field_60;
    case 61: return (u8)(mission->flags >> 6) & 1;
    case 62: return (u8)(mission->flags >> 7) & 1;
    case 63: return (u8)(mission->flags >> 8) & 1;
    case 64: return (u8)(mission->flags >> 9) & 1;
    default: return 0;
    }
}
