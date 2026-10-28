#ifndef BATTLE_CONSUMER_C03D_H
#define BATTLE_CONSUMER_C03D_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

enum {
    C03D_FIRST_DEFAULT = 0,
    C03D_FIRST_GROUP_1_2_3_12_14 = 1,
    C03D_FIRST_GROUP_8_10_15 = 2,
    C03D_FIRST_GROUP_11 = 3,
    C03D_SECOND_DEFAULT = 0,
    C03D_SECOND_GROUP_1_2_3 = 1,
    C03D_SECOND_GROUP_8 = 2,
    C03D_SECOND_GROUP_10 = 3,
    C03D_SECOND_GROUP_11 = 4,
    C03D_SECOND_GROUP_12_14 = 5,
    C03D_SECOND_GROUP_15 = 6
};

/* The first selector is previous_record[14], read as a byte. */
static __inline__ u32 C03DPreviousRecordDispatch(u8 selector)
{
    if (selector == 1 || selector == 2 || selector == 3 ||
        selector == 12 || selector == 14) {
        return C03D_FIRST_GROUP_1_2_3_12_14;
    }
    if (selector == 8 || selector == 10 || selector == 15) {
        return C03D_FIRST_GROUP_8_10_15;
    }
    if (selector == 11) {
        return C03D_FIRST_GROUP_11;
    }
    return C03D_FIRST_DEFAULT;
}

/* The effect selector is a separate u16 producer and a separate table. */
static __inline__ u32 C03DEffectDispatch(u16 selector)
{
    if (selector == 1 || selector == 2 || selector == 3) {
        return C03D_SECOND_GROUP_1_2_3;
    }
    if (selector == 8) {
        return C03D_SECOND_GROUP_8;
    }
    if (selector == 10) {
        return C03D_SECOND_GROUP_10;
    }
    if (selector == 11) {
        return C03D_SECOND_GROUP_11;
    }
    if (selector == 12 || selector == 14) {
        return C03D_SECOND_GROUP_12_14;
    }
    if (selector == 15) {
        return C03D_SECOND_GROUP_15;
    }
    return C03D_SECOND_DEFAULT;
}

static __inline__ u16 C03DRemapScalar(u32 derived_selector,
                                      u16 current_value)
{
    /* A third nested table only overwrites five of its fourteen slots. */
    if (derived_selector > 13) {
        return current_value;
    }
    if (derived_selector == 0) {
        return 34;
    }
    if (derived_selector == 1) {
        return 42;
    }
    if (derived_selector == 2) {
        return 234;
    }
    if (derived_selector == 11) {
        return 7;
    }
    if (derived_selector == 13) {
        return 72;
    }
    return current_value;
}

u8 *BattleCallbackProducer_000A8194(
    u8 *actor_context, u32 action_id, u32 equipment_id,
    u32 requested_x, u32 requested_y, u32 mode, u32 option);

void BattleCallbackProducer_000A433C(
    u8 *record_block, u8 *actor_context, u8 requested_x, u8 requested_y,
    u16 root_action, u16 equipment_value, u8 mode, u8 option);


#endif
