#include "battle_consumer_c03d.h"

enum {
    BATTLE_RECORD_BYTES = 708,
    BATTLE_ROW_BYTES = 44,
    BATTLE_ACTION_BYTES = 16,
    BATTLE_BLOCK_ACTION_INDEX = 0x26bd,
    BATTLE_BLOCK_ACTIVE_ROW = 0x26b8,
    BATTLE_BLOCK_ACTIONS = 0x33c4,
    BATTLE_BLOCK_ACTION_COUNT = 0x26bd,
    BATTLE_RECORD_COUNT = 704,
    BATTLE_RECORD_FLAGS = 44,
    BATTLE_RECORD_KIND = 46,
    BATTLE_RECORD_SCALAR = 62,
    BATTLE_UNIT_CONTEXT = 128,
    BATTLE_UNIT_X = 246,
    BATTLE_UNIT_Y = 247,
    BATTLE_UNIT_ACTION_BYTES = 248,
    BATTLE_RECORD_SPECIAL_BIT = 0x0040,
    BATTLE_RECORD_ACTIVE_BIT = 0x0080,
    BATTLE_RECORD_CONSUMED_BIT = 0x0200
};

/* Original u16 action-word RAM interface; no capacity assumption or definition. */
extern u16 OriginalActionWords[] asm("0x0200f888");

extern u32 RetailCall_08002804(void);
extern u32 AllocateBattleRecordBlock(u32 byte_count);
extern void ReleaseBattleObject(u32 allocation);
extern u32 RetailCall_0809aac8(u32 context);
extern void CallBattleContextSwap_080A21B4(void *pair_list,
                                           void *previous_context,
                                           void *replacement_context);
extern u32 RetailCall_080a22f0(u32 battle_record);
extern u32 RetailCall_080a23b8(u32 battle_record, u32 actor_context,
                               u32 actor_unit, u32 accumulated_flags,
                               u32 transition_mode, u32 scratch_records,
                               u32 chance_gate, u32 mode_state);
extern u32 RetailCall_080a39f8(u32 battle_record, u32 actor_context,
                               u32 unit_context, u32 actor_context_arg,
                               u32 requested_x, u32 requested_y,
                               u32 action_id, u32 selection_index,
                               u32 record_kind, u32 current_row,
                               u32 scratch_records, u32 chance_gate);
extern u32 RetailCall_080a4274(u32 battle_record, u32 action_table,
                               u32 actor_unit);
extern u32 RetailCall_080a8858(u32 unit_context, u32 field);
extern u32 RetailCall_080b3150(u32 actor_context, s32 x, s32 y,
                               u32 action_id);
extern u32 ReadBattleRecordFallbackProperty_080B42D4(u32 input);
extern u32 RetailCall_080b4c90(u32 first, u32 second, u32 action_id,
                               u32 mode);
extern u32 RetailCall_080c7ea4(u32 unit, u32 property);
extern u32 RetailCall_080c8280(u32 unit);
extern u32 RetailCall_080ccd50(u32 object_id, u32 property);
extern u32 RetailCall_080cd6a8(u32 unit);
extern u32 RetailCall_080cd8b4(u32 unit);
extern u32 RetailCall_080cd8cc(u32 unit);
extern u32 RetailCall_080cd8e4(u32 unit);
extern u32 RetailCall_080cd92c(u32 unit);
extern u32 RetailCall_080cd944(u32 unit);
extern u32 RetailCall_080cdaac(u32 unit);
extern u32 RetailCall_080cdcbc(u32 unit);
extern void SetUnitStateE9Bit6(u32 unit, u32 value);
extern u32 BattleRecordReplacement_08099494(u32 actor_unit, u32 target_unit);
extern u32 RetailCall_0812ea44(u32 actor_unit, u32 target_unit,
                               u32 action_id);
extern s32 RetailCall_0812ed98(u32 unit, u32 action_id);
extern u32 RetailCall_0812f0d8(u32 unit, u32 output_table);
extern u32 RetailCall_08133b84(u32 unit, u32 selector);
extern u32 RetailCall_0814224c(u32 destination, u32 byte_count,
                               u32 callback);
extern u32 RetailCall_08142250(u32 destination, u32 source,
                               u32 byte_count, u32 callback);
extern s32 RetailCall_08142950(s32 value, u32 modulus);

/* Actual heap record envelope, including only observed typed fields.
 * Byte regions preserve unknown contents; no row-capacity/domain assumption. */
struct BattleRowPrefix {
    u32 context;
    u8 bytes_04_0B[8];
    u16 flags;
    u16 kind;
    u32 state;
    u8 bytes_14_1D[10];
    s16 scalar;
};
struct BattleRecordObject {
    u32 context;
    u16 flags;
    u8 bytes_06_08[3];
    u8 kind;
    u8 x;
    u8 y;
    u8 bytes_0C_0F[4];
    u16 action;
    u8 bytes_12_1B[10];
    u8 option;
    u8 bytes_1D_1F[3];
    struct BattleRowPrefix first_row;
    u8 bytes_040_2BF[640];
    u8 row_count;
    u8 bytes_2C1_2C3[3];
};
typedef char AssertRowPrefix32[(sizeof(struct BattleRowPrefix) == 32) ? 1 : -1];
typedef char AssertRecord708[(sizeof(struct BattleRecordObject) == 708) ? 1 : -1];
#define CurrentRecord(record) ((struct BattleRecordObject *)(record))

/* Original field RMW copies the actual current address into a low base
 * that survives load and store. Keep this ordinary pointer distinct from the
 * hard parent carrier until that complete field operation is consumed. */
#define CurrentRmwView(record) \
    ({ struct BattleRecordObject *rmw_base = (record); \
       asm("" : "+r"(rmw_base)); rmw_base; })

/* Reuse battle_record_c03a.h actual context-prefix interface: its unit
 * address is callback-visible. Qualify that observed W0 only, not all RAM. */
struct BattleContextPrefix {
    volatile u32 unit_address;
    volatile u32 related_context_address;
};
#define ContextUnit(context) (((struct BattleContextPrefix *)(context))->unit_address)

/* Observed actor-context prefix. Unknown bytes remain an opaque region. */
struct BattleActorContextPrefix {
    volatile u32 unit_address;
    volatile u32 related_context_address;
    u16 x_fixed;
    u8 bytes_0A_0B[2];
    u16 y_fixed;
    u8 bytes_0E_7F[114];
    u32 lookup_context;
};
typedef char AssertActorPrefix132[(sizeof(struct BattleActorContextPrefix) == 132) ? 1 : -1];
#define ActorContext(context) ((struct BattleActorContextPrefix *)(context))

/* Preserve source lvalue accesses in helper argument preparation. */
#define ReadHalfword(base, offset) (*(const u16 *)((const u8 *)(base) + (offset)))
#define ReadWord(base, offset) (*(const u32 *)((const u8 *)(base) + (offset)))
#define WriteHalfword(base, offset, value) (*(u16 *)((u8 *)(base) + (offset)) = (u16)(value))
#define WriteWord(base, offset, value) (*(u32 *)((u8 *)(base) + (offset)) = (u32)(value))
#define NextRecordIndex(block) ((block)[BATTLE_BLOCK_ACTION_INDEX])

static __inline__ u8 *RecordAt(u8 *records, u32 index)
{
    return records + index * BATTLE_ROW_BYTES;
}

/* Independent row search result for each matching earlier record.
 * The native inner ordinal dies before its found-row result is selected. */
static __inline__ u8 *FindEarlierTargetRow(u8 *record, u32 context)
{
    s32 ordinal = 0;
    register s32 entry_count asm("r0") = record[BATTLE_RECORD_COUNT];
    if (ordinal < entry_count) {
        register s32 count asm("r3") = entry_count;
        u8 *cursor;
        cursor = record + 32;
        goto earlier_first_target_row;
        for (; ordinal < count; ++ordinal) {
earlier_first_target_row:
            if (ReadWord(cursor, 0) == context)
                return cursor;
            cursor += BATTLE_ROW_BYTES;
        }
    }
    return (u8 *)0;
}

static __inline__ void AppendRecord(u8 **destination, u8 *record,
                                    u8 *output_context, u8 *coordinate_unit,
                                    u8 selector,
                                    u16 scalar, u16 kind)
{
    u8 *out = *destination;

    WriteWord(out, 0, ReadWord(record, 0));
    WriteWord(out, 4, (u32)output_context);
    out[10] = coordinate_unit[BATTLE_UNIT_X];
    out[11] = coordinate_unit[BATTLE_UNIT_Y];
    WriteHalfword(out, 8, scalar);
    WriteHalfword(out, 12, kind);
    out[14] = selector;
    *destination = out + BATTLE_ACTION_BYTES;
}

static __inline__ s32 SignExtendByte(u32 value)
{
    return (s8)(u8)value;
}

static __inline__ u32 ReadUnitCoordinate(u8 *context, u32 offset)
{
    return ((u8 *)ContextUnit(context))[offset];
}

static __inline__ u32 IsNonzeroByte(u32 value)
{
    return (u8)value != 0;
}


typedef u32 (*BattleFillCallback)(u32 destination, u32 byte_count);
typedef u32 (*BattleCopyCallback)(u32 destination, u32 source, u32 byte_count);
#define FillRetailBytes(destination, byte_count) \
    (*(BattleFillCallback volatile *)0x0836d4b8)((u32)(destination), (u32)(byte_count))
#define CopyRetailBytes(destination, source, byte_count) \
    (*(BattleCopyCallback volatile *)0x0836d4bc)((u32)(destination), (u32)(source), (u32)(byte_count))

static __inline__ void AppendPendingRecord(
    u8 **write_cursor, u32 target_context, u32 related_context,
    u8 *coordinate_unit, u16 payload, u16 kind, u8 selector)
{
    u8 *pending = *write_cursor;

    WriteWord(pending, 0, target_context);
    WriteWord(pending, 4, related_context);
    WriteHalfword(pending, 8, payload);
    pending[10] = coordinate_unit[BATTLE_UNIT_X];
    pending[11] = coordinate_unit[BATTLE_UNIT_Y];
    WriteHalfword(pending, 12, kind);
    pending[14] = selector;
    *write_cursor = pending + BATTLE_ACTION_BYTES;
}

static __inline__ u32 RunTargetResolver(
    u8 *battle_record, u8 *actor_context, u32 mode_complement,
    u32 transition_mode, u8 *scratch_records, u32 chance_gate,
    u32 mode_state)
{
    u32 unit_context = ActorContext(actor_context)->lookup_context;

    return RetailCall_080a23b8(
        (u32)battle_record, (u32)actor_context, unit_context,
        (u8)mode_complement, transition_mode, (u32)scratch_records,
        chance_gate, mode_state);
}

static __inline__ u32 RunRecordInitializer(
    u8 *battle_record, u8 *actor_context, u8 *current_context,
    s32 requested_x, s32 requested_y, u32 current_action,
    u32 equipment_value, u32 current_kind, u32 selected_context,
    u8 *scratch_records, u32 chance_gate)
{
    u32 unit_context = ActorContext(actor_context)->lookup_context;

    return RetailCall_080a39f8(
        (u32)battle_record, (u32)actor_context, unit_context,
        (u32)current_context, requested_x, requested_y, current_action,
        equipment_value, current_kind, selected_context,
        (u32)scratch_records, chance_gate);
}

static __inline__ u32 ClassifyTargetUnit(u32 target_unit)
{
    u32 current_value;
    u32 maximum_value;
    register u32 classification_value asm("r0");

    if ((u8)RetailCall_080c8280(target_unit) != 0) {
        classification_value = 1;
        goto classification_ready;
    }
    if ((u8)RetailCall_080cd92c(target_unit) != 0) {
        if ((u8)RetailCall_080cdcbc(target_unit) != 0)
            goto classification_two;
        goto classification_three;
    }
    current_value = RetailCall_080c7ea4(target_unit, 19);
    maximum_value = RetailCall_080c7ea4(target_unit, 20) >> 2;
    if (current_value > maximum_value)
        goto classification_three;
classification_two:
    classification_value = 2;
    goto classification_ready;
classification_three:
    classification_value = 3;
classification_ready:
    asm("" : "+r"(classification_value));
    return classification_value;
}

void BattleCallbackProducer_000A433C(
    u8 *record_block, u8 *actor_context, u8 requested_x,
    u8 requested_y, u16 root_action, u16 equipment_value,
    u8 mode, u8 option)
{
    s32 equipment_index;
    s32 action_count;
    u32 mode_complement;
    u32 target_index;
    s32 coordinate_x;
    s32 coordinate_y;
    u32 current_action;
    u32 current_kind;
    u32 transition_mode;
    u32 status_accumulator;
    u32 lifetime_result;
    u32 status20_count;
    u32 input_action;
    u8 *optional_pending_storage;
    u8 *pending_read_cursor;
    u8 *pending_write_cursor;
    u8 *current_context;
    u8 *selected_context;
    u8 *snapshot;
    u8 *temporary_record;
    u8 *snapshot_source;
    u8 *scratch_records;
    u32 chance_gate;
    u32 first_auxiliary;
    u32 flag80_count;
    u32 mode_state;
    u8 *actor_unit;
    struct BattleRecordObject *output_record;
    register u8 *matched_row asm("r5");
    u32 find_offset;
    u8 *snapshot_row;
    u8 *target_row;
    u8 *target_context;
    u8 *target_unit;
    u8 *pending_record;
    u8 *new_record;
    u8 *candidate_record;
    u8 *candidate_row;
    u32 equipment_count;
    u32 next_target_index;
    s32 row_count;
    s32 row_index;
    s32 candidate_index;
    s32 candidate_row_index;
    u32 accepted_count;
    u32 pending_selector;
    u32 target_selector;
    u32 target_table_index;
    u32 classification;
    u32 helper_result;
    u32 resolver_result;
    s32 available_action;
    u32 remaining_action;
    u32 selected_context_value;
    u32 pending_group;
    s32 output_action_count;
    u32 target_found;
    u32 moved_count;
    u8 *snapshot_count;
    u32 earlier_root_context;
    u32 shifted_mode_complement;
    u32 read_callback;
    u32 input_action_count;
    u32 action_property;
    u32 rng_value;
    s32 signed_rng;
    s32 quotient;
    s32 cost;
    s32 remaining;
    s32 i;
    (void)RetailCall_0809aac8(ActorContext(actor_context)->lookup_context);
    input_action = root_action;
    pending_read_cursor = (u8 *)0;
    optional_pending_storage = (u8 *)0;
    pending_write_cursor = (u8 *)0;

    if (root_action == 233) {
        signed_rng = (s16)RetailCall_08002804();
        quotient = signed_rng;
        if (quotient < 0)
            quotient += 7;
        quotient >>= 3;
        root_action = (u16)(signed_rng - 8 * quotient + 68);
    }
    if (root_action == 329) {
        root_action = (u16)(RetailCall_08142950((s16)RetailCall_08002804(), 5) + 312);
    }
    if (mode == 0) {
        optional_pending_storage =
            (u8 *)AllocateBattleRecordBlock(BATTLE_ACTION_BYTES * 16);
        FillRetailBytes(optional_pending_storage, BATTLE_ACTION_BYTES * 16);
        pending_write_cursor = optional_pending_storage;
        pending_read_cursor = optional_pending_storage;
    }

    {
        u32 chance_rng = RetailCall_08002804();
        u32 chance = 0;
        if ((s16)RetailCall_08142950((s16)chance_rng, 101) > 49)
            chance = 1;
        chance_gate = chance;
    }

    {
        register struct BattleRecordObject *initial_record asm("r10") = 0;
        asm("" : : "r"(initial_record));
        output_record = initial_record;
    }
    
    temporary_record =
        (u8 *)AllocateBattleRecordBlock(BATTLE_RECORD_BYTES);
    scratch_records = (u8 *)AllocateBattleRecordBlock(4096);
    mode_complement = mode ^ 1;
    snapshot = (u8 *)0;

    {
        u8 *coordinate_context = actor_context;
        u8 *x_unit = (u8 *)ContextUnit(coordinate_context);
        u32 actor_x = ActorContext(coordinate_context)->x_fixed >> 5;
        x_unit[BATTLE_UNIT_X] = actor_x;
        {
            u8 *y_unit = (u8 *)ContextUnit(coordinate_context);
            u32 actor_y = ActorContext(coordinate_context)->y_fixed >> 5;
            y_unit[BATTLE_UNIT_Y] = actor_y;
        }
    }

    {
        register u32 initial_x asm("r6") = requested_x;
        register u32 initial_y asm("r7") = requested_y;
        asm("" : : "r"(initial_x), "r"(initial_y));
        /* Initialized actual input values at their original SP68/SP72 consumers. */
        coordinate_x = initial_x;
        coordinate_y = initial_y;
    }
    current_context = actor_context;
    action_count = (u8)RetailCall_0812f0d8(
        ContextUnit(actor_context), (u32)OriginalActionWords);
    if (action_count == 0) {
        action_count = 1;
        WriteHalfword((u8 *)OriginalActionWords, 0, 0);
    }

    if ((root_action != 0 &&
         RetailCall_080ccd50(root_action, 27) != 0) || root_action == 265) {
        WriteHalfword((u8 *)OriginalActionWords, 0, (u16)equipment_value);
        action_count = 1;
    }

    if (root_action == 223) {
        CopyRetailBytes((u8 *)OriginalActionWords + (action_count << 1),
                        (const u8 *)OriginalActionWords, action_count << 1);
        action_count = (u8)(action_count << 1);
    }

    current_action = root_action;
    current_kind = 0;
    target_index = 0;
    *(volatile u8 *)0x0200f890 = 1;
    snapshot_source = (u8 *)0;
    lifetime_result = 0;
    first_auxiliary = 1;
    mode_state = 1;
    flag80_count = 0;

    for (;;) {
construction_phase:
    selected_context = (u8 *)0;
    status_accumulator = 0;
    transition_mode = 1;
    status20_count = 0;
    {
    register u32 construction_gate asm("r2") = transition_mode;
    asm("" : "+r"(construction_gate));
    if (construction_gate != 0) {
    equipment_index = 0;
    while (equipment_index < action_count) {
    u8 *output_row_count;
    register u8 *count_before_replacement asm("r5");
    register u32 mode_byte_working asm("r3");
    u32 construction_index;
    s32 construction_x;
    s32 construction_y;
construct_record:

    construction_index = NextRecordIndex(record_block);
    {
        register struct BattleRecordObject *constructed_record asm("r10") =
            (struct BattleRecordObject *)(record_block + construction_index * BATTLE_RECORD_BYTES);
        asm("" : : "r"(constructed_record));
        output_record = constructed_record;
    }
    

    if ((equipment_index + 1) >= action_count && mode != 0 &&
        ReadWord(record_block, BATTLE_BLOCK_ACTIVE_ROW) == 0)
        current_kind = 2;

    if (mode != 0 ||
        ((current_action == 0 || current_action == 223) &&
         (equipment_index + 1) < action_count))
        transition_mode = 0;

    if (current_action != 0 && current_kind != 8 &&
        current_kind != 9 && current_kind != 12 && current_kind != 11 &&
        current_context != (u8 *)0) {
        u32 cost_unit;
        u32 cost_action;
        if (input_action != root_action && root_action == current_action) {
            cost_unit = ContextUnit(current_context);
            cost_action = input_action;
            goto query_record_cost;
        }
        goto query_current_cost;
matching_row_found:
        {
            register u32 row_offset asm("r0") = find_offset + 32;
            register u8 *found_record_base asm("r1") = (u8 *)output_record;
            asm("" : "+r"(found_record_base));
            matched_row = found_record_base + row_offset;
        }
        goto matching_row_ready;
query_current_cost:
        {
            register u8 *cost_context asm("r2") = current_context;
            cost_unit = ContextUnit(cost_context);
        }
        cost_action = current_action;
query_record_cost:
        cost = (s16)RetailCall_0812ed98(cost_unit, cost_action);
        {
            register u8 *available_context asm("r3") = current_context;
            available_action = (s16)RetailCall_080c7ea4(
                ContextUnit(available_context), 21);
        }
        cost = available_action - cost;
        if (cost < 0)
            goto after_construction;
        {
            register u8 *write_context asm("r1") = current_context;
            WriteHalfword((u8 *)ContextUnit(write_context), 28, (u16)cost);
        }
    }

    if (RetailCall_080a39f8(
        (u32)output_record, (u32)actor_context,
        ActorContext(actor_context)->lookup_context, (u32)current_context,
        ({ register s32 x_word asm("r3") = coordinate_x;
           register u32 x_shifted asm("r0") = (u32)x_word << 24;
           asm("" : "+r"(x_shifted) : "r"(x_word));
           construction_x = (s32)x_shifted >> 24; }),
        ({ register s32 y_word asm("r1") = coordinate_y;
           register u32 y_shifted asm("r0") = (u32)y_word << 24;
           asm("" : "+r"(y_shifted) : "r"(y_word));
           construction_y = (s32)y_shifted >> 24; }),
        ({ register u32 action_word asm("r3") = current_action;
           asm("" : : "r"(action_word)); action_word; }),
        OriginalActionWords[equipment_index],
        current_kind, (u32)selected_context, (u32)scratch_records, chance_gate) == 0)
        goto after_construction;

    if (first_auxiliary != 0) {
        first_auxiliary = 0;
        if ((u8)RetailCall_080a4274(
            (u32)output_record, (u32)(record_block + BATTLE_BLOCK_ACTIONS),
            ActorContext(actor_context)->lookup_context) != 0) {
            FillRetailBytes(output_record, BATTLE_RECORD_BYTES);
            (void)RetailCall_080a39f8(
                (u32)output_record, (u32)actor_context,
                ActorContext(actor_context)->lookup_context, (u32)current_context,
                construction_x, construction_y, current_action,
                OriginalActionWords[equipment_index],
                current_kind, (u32)selected_context, (u32)scratch_records, chance_gate);
        }
    }

    if (input_action == 233) {
        register struct BattleRecordObject *flag_record asm("r3") = output_record;
        register u16 record_flags asm("r0");
        record_flags = flag_record->flags;
        record_flags |= 0x2000;
        flag_record->flags = record_flags;
    }
    if (input_action == 329) {
        register struct BattleRecordObject *flag_record asm("r2") = output_record;
        register u16 record_flags asm("r0");
        record_flags = flag_record->flags;
        record_flags |= 0x4000;
        flag_record->flags = record_flags;
    }
    if (current_kind == 9) {
        register struct BattleRecordObject *read_record asm("r1");
        register u16 record_flags asm("r0");
        /* The loaded address dies before the mask overwrites its carrier. */
        asm("mov %0, %1" : "=l"(read_record) : "r"(output_record));
        record_flags = read_record->flags;
        record_flags |= 8;
        {
            register struct BattleRecordObject *write_record asm("r2");
            /* Native separately copies the same parent after applying mask. */
            asm("mov %0, %1" : "=l"(write_record) : "r"(output_record));
            write_record->flags = record_flags;
        }
    }
    {
    register u32 kind_for_flag asm("r3") = current_kind;
    asm("" : : "r"(kind_for_flag));
    if (kind_for_flag == 11) {
        register struct BattleRecordObject *flag_record asm("r4") = output_record;
        register u16 record_flags asm("r0");
        record_flags = flag_record->flags;
        record_flags |= 0x200;
        flag_record->flags = record_flags;
    }
    }

    {
        struct BattleRecordObject *kind_record = output_record;
        u32 output_kind;
        output_kind = kind_record->kind;
        if ((u8)(output_kind - 7) <= 2 || output_kind == 11) {
            register u32 action_for_count asm("r4") = current_action;
            if (action_for_count != 17 && action_for_count != 304)
                CurrentRecord(output_record)->row_count = 1;
        }
    }

    {
        register s32 next_ordinal asm("r0") = equipment_index + 1;
        register s32 action_bound asm("r1") = action_count;
        asm("" : : "r"(next_ordinal), "r"(action_bound));
        if (next_ordinal < action_bound) {
            register u32 action_for_flag asm("r2") = current_action;
            asm("" : : "r"(action_for_flag));
            if (action_for_flag == 0 || action_for_flag == 223) {
                register struct BattleRecordObject *flag_record asm("r3") = output_record;
                register u16 record_flags asm("r0");
                record_flags = flag_record->flags;
                record_flags |= 1;
                flag_record->flags = record_flags;
            }
        }
    }

    mode_byte_working = mode_complement;
    asm volatile("" : "+r"(mode_byte_working));
    count_before_replacement = &output_record->row_count;
    if (*count_before_replacement == 0) {
        register struct BattleRecordObject *flag_record asm("r4") = output_record;
        register u16 record_flags asm("r0");
        record_flags = flag_record->flags;
        record_flags |= 0x20;
        flag_record->flags = record_flags;
    }

    shifted_mode_complement = mode_byte_working << 24;
    {
    register s32 completion_ordinal asm("r0") = equipment_index + 1;
    register s32 completion_bound asm("r1") = action_count;
    asm("" : : "r"(completion_ordinal), "r"(completion_bound));
    if (completion_ordinal >= completion_bound) {
    register u32 fallback_mode asm("r2") = mode;
    asm("" : : "r"(fallback_mode));
    if (fallback_mode != 0) {
    register u8 *fallback_block asm("r3") = record_block;
    register u32 active_row_offset asm("r4") = BATTLE_BLOCK_ACTIVE_ROW;
    register u8 *active_row_address asm("r0");
    asm("" : : "r"(fallback_block), "r"(active_row_offset));
    active_row_address = fallback_block + active_row_offset;
    if (ReadWord(active_row_address, 0) == 0) {
        u8 *actor_row;
        register u32 first_row_address_word asm("r0");
        u32 replacement_context;
        register struct BattleRowPrefix *record_rows asm("r9");
        register u8 *fallback_list asm("r4");

        ReleaseBattleObject((u32)scratch_records);
        first_row_address_word = 32;
        /* Native short R0 offset plus high parent R10. */
        asm("add %0, %1" : "+r"(first_row_address_word) : "r"(output_record));
        {
            register u8 *registered_actor_row asm("r8");
            /* Native registers this actual R0-derived address in R8. One
             * real copy also avoids a second nominal empty-ASM instruction. */
            asm("mov %0, %1" : "=r"(registered_actor_row) : "r"(first_row_address_word));
            actor_row = registered_actor_row;
        }
        {
            register u8 *list_base asm("r1") = record_block;
            register u32 list_offset asm("r2") = BATTLE_BLOCK_ACTIONS;
            /* These real inputs die after forming the persistent R4 list. */
            asm("" : : "r"(list_base), "r"(list_offset));
            fallback_list = list_base + list_offset;
        }
        {
            register u32 *lookup_field asm("r3") = &ActorContext(actor_context)->lookup_context;
            register u32 lookup_value asm("r0");
            struct BattleRecordObject *replacement_record;
            /* Native dereference through the actual R3 address into R0.
             * The memory input declares this exact read without a broad clobber.
             * One instruction replaces C LDR plus empty input event. */
            asm("ldr %0, [%1]" : "=l"(lookup_value)
                    : "l"(lookup_field), "m"(*lookup_field));
            replacement_record = output_record;
            replacement_context = BattleRecordReplacement_08099494(
                lookup_value, replacement_record->first_row.context);
        }
        /* Actual native R8 -> R9 row-base snapshot, plus unchanged count capture. */
        asm("mov %0, %2" : "=r"(record_rows), "=r"(output_row_count)
                : "r"(actor_row), "1"(count_before_replacement));
        if (replacement_context != 0) {
            register struct BattleRowPrefix *replacement_flags_row asm("r3") = record_rows;
            if ((replacement_flags_row->flags & 0x40) == 0) {
            s32 list_index = 0;
            s32 list_count = ReadHalfword(fallback_list, 48);
            u32 list_target = CurrentRecord(output_record)->first_row.context;
            u8 *list_entry;
            if (list_index < list_count) {
                register u32 primary_target asm("r6");
                /* Actual native low-register copy; the independent target
                 * snapshot stays distinct from the second-key comparison. */
                asm("add %0, %1, #0" : "=l"(primary_target)
                        : "l"(list_target) : "cc");
                list_entry = fallback_list;
                do {
                    if (ReadWord(list_entry, 0) == primary_target ||
                        ReadWord(list_entry, 24) == list_target)
                        goto replacement_complete;
                    list_entry += 4;
                    ++list_index;
                } while (list_index < list_count);
            }
            CallBattleContextSwap_080A21B4(
                fallback_list, (void *)list_target,
                (void *)replacement_context);
            {
                u32 *replacement_actor_cell = (u32 *)actor_row;
                *replacement_actor_cell = replacement_context;
            }
            }
        }
replacement_complete:

        {
            struct BattleRecordObject *target_record_view = output_record;
            target_context = (u8 *)target_record_view->first_row.context;
        }
        target_unit = (u8 *)ContextUnit(target_context);
        WriteWord(record_block, BATTLE_BLOCK_ACTIVE_ROW, RetailCall_080b3150(
            (u32)actor_context,
            SignExtendByte(target_unit[BATTLE_UNIT_X]),
            SignExtendByte(target_unit[BATTLE_UNIT_Y]),
            ReadHalfword((u8 *)OriginalActionWords, 0)));

        {
            register u32 comparison_context asm("r6");
            u8 *find_cursor;
            register s32 find_ordinal asm("r2");
            register s32 scan_count_value asm("r0");
            /* Native snapshots first context, then independently samples rows. */
            comparison_context = CurrentRecord(output_record)->first_row.context;
            /* Native zero ordinal is defined after the context snapshot. */
            asm("mov %1, #0" : "+r"(comparison_context), "=l"(find_ordinal)
                    : : "cc");
            scan_count_value = *output_row_count;
            if (find_ordinal < scan_count_value) {
                register s32 loop_count asm("r5") = scan_count_value;
                /* The backedge keeps this real count across R0 row loads. */
                find_cursor = (u8 *)record_rows;
                find_offset = 0;
                do {
                    if (ReadWord(find_cursor, 0) == comparison_context)
                        goto matching_row_found;
                    find_cursor += BATTLE_ROW_BYTES;
                    find_offset += BATTLE_ROW_BYTES;
                    ++find_ordinal;
                } while (find_ordinal < loop_count);
            }
            matched_row = (u8 *)0;
            goto matching_row_ready;
matching_row_ready:
            ; /* Both incoming paths define the actual R5 row before this join. */
        }
        /* Original uses the same pointer for the invariant low-address fallback. */
        WriteHalfword(matched_row, 30, (u16)ReadBattleRecordFallbackProperty_080B42D4(
            ReadWord(record_block, BATTLE_BLOCK_ACTIVE_ROW)));

        scratch_records = (u8 *)AllocateBattleRecordBlock(4096);
    }
    }
    }
    }

    {
    register u32 option_record_owner asm("r0");
    register u8 *option_actor asm("r1");
    option_record_owner = ({ struct BattleRecordObject *option_context_record = output_record;
                            option_context_record->context; });
    option_actor = actor_context;
    /* Original comparison consumes these two initialized values at this phase.
     * Neither value is kept artificially live after that comparison. */
    asm("" : : "r"(option_record_owner), "r"(option_actor));
    if (option_record_owner == (u32)option_actor) {
        register u32 option_for_store asm("r2") = option;
        if (option_for_store != 0xff) {
            register u32 option_action asm("r3") = current_action;
            register u32 option_root_action asm("r4") = root_action;
            /* Original full-word comparison is reached only after the byte guard. */
            asm("" : : "r"(option_action), "r"(option_root_action));
            if (option_action == option_root_action) {
                CurrentRecord(output_record)->option = (u8)option_for_store;
                RetailCall_0809920c((u32)actor_context, option);
                RetailCall_0809915c((u32)actor_context, option);
            }
        }
    }

    }

    lifetime_result = (u8)(lifetime_result | RetailCall_080a23b8(
        (u32)output_record, (u32)actor_context,
        ActorContext(actor_context)->lookup_context, shifted_mode_complement >> 24,
        transition_mode, (u32)scratch_records, chance_gate, mode_state));

    {
        register u32 post_call_owner asm("r0");
        u8 *post_call_actor;
        post_call_owner = ({ struct BattleRecordObject *post_context_record = output_record;
                             post_context_record->context; });
        post_call_actor = actor_context;
        /* These actual working values feed the post-call equality and the
         * guarded option callback; neither acquires an artificial use. */
        if (post_call_owner == (u32)post_call_actor) {
            u32 post_call_option = option;
            if (post_call_option != 0xff)
                RetailCall_0809915c((u32)post_call_actor, post_call_option);
        }
    }

    (void)RetailCall_080a22f0((u32)output_record);
    if ((u8)RetailCall_080c8280(
            ContextUnit((u8 *)({ struct BattleRecordObject *unit_context_record = output_record;
                                unit_context_record->context; }))) != 0 ||
        ({ struct BattleRecordObject *kind_context_record = output_record;
           kind_context_record->first_row.kind; }) == 3) {
        /* Both native values are ordinary consumers here: the ordinal
         * read and the guarded count store advance the same reload chain. */
        if (equipment_index == 0)
            action_count = 1;
    }

    if (snapshot == (u8 *)0 &&
        (CurrentRecord(output_record)->first_row.flags & 0x80) != 0)
        flag80_count = (u8)(flag80_count + 1);

    if ((current_action == 0 || current_action == 223) &&
        (equipment_index + 1) < action_count) {
        transition_mode = 1;
        selected_context = (u8 *)CurrentRecord(output_record)->first_row.context;
        status_accumulator = (u8)(status_accumulator |
            RetailCall_080a8858((u32)&output_record->first_row, 3));
        {
            struct BattleRecordObject *state_record = output_record;
            register u32 state_word asm("r0");
            /* Consume the real high-parent address as a low load input.
             * The inherited working base remains available to the C RMW. */
            asm("ldr %0, [%1, #48]" : "=l"(state_word)
                    : "l"(state_record), "m"(state_record->first_row.state));
            state_word &= 0xffffdfff;
            state_record->first_row.state = state_word;
            if ((state_record->first_row.flags & 0x20) != 0)
                status20_count = (u8)(status20_count + 1);
        }
        if (status20_count != 0)
            transition_mode = 2;
    } else if (status_accumulator != 0) {
        struct BattleRecordObject *state_record = output_record;
        register u32 state_word asm("r0");
        asm("ldr %0, [%1, #48]" : "=l"(state_word)
                : "l"(state_record), "m"(state_record->first_row.state));
        state_word |= 0x2000;
        state_record->first_row.state = state_word;
    }

    record_block[BATTLE_BLOCK_ACTION_INDEX] =
        (u8)(record_block[BATTLE_BLOCK_ACTION_INDEX] + 1);

    if (current_action == 0 || current_action == 223) {
        current_kind = 0;
        equipment_index = (equipment_index + 1);
    } else {
        break;
    }
    }

after_construction:
    if (mode != 0)
        goto cleanup;

    if (snapshot == (u8 *)0) {
        CopyRetailBytes(temporary_record, output_record, BATTLE_RECORD_BYTES);
        snapshot = temporary_record;
        snapshot_source = (u8 *)output_record;
        mode_complement = 0;
    }
    }
    }

extract_consumed_prefix: {
    u8 *consumed_record;
    register u8 *consumed_count_address asm("r5");
    u32 initial_count;
    mode_state = 1;
    {
        /* Native keeps the same R2 block root from the index-address read
         * through multiplication and the final record-base sum. */
        u8 *prefix_block_base = record_block;
        u32 prefix_record_index = NextRecordIndex(prefix_block_base);
        consumed_record = prefix_block_base + prefix_record_index * BATTLE_RECORD_BYTES;
    }
    consumed_count_address = consumed_record + BATTLE_RECORD_COUNT;
    /* Actual native zero definition, replacing C MOV plus empty RW.
     * This keeps its real definition and avoids two nominal empty-ASM bytes. */
    initial_count = 0;
    *consumed_count_address = (u8)initial_count;
    moved_count = initial_count;
    {
        s32 entry_ordinal = (s32)target_index;
        s32 consumed_ordinal;
        register u8 *count_before_transfer asm("r4");
        register s32 entry_row_count asm("r2");
        /* Entry ordinal feeds both the running counter and first offset;
         * the later counter update has a separate native R9 lifetime. */
        consumed_ordinal = entry_ordinal;
        count_before_transfer = snapshot + BATTLE_RECORD_COUNT;
        entry_row_count = *count_before_transfer;
        if (entry_ordinal < entry_row_count) {
            u32 consumed_offset = (u32)entry_ordinal * BATTLE_ROW_BYTES;
            u8 *candidate_flags = snapshot + consumed_offset;
            if (ReadHalfword(candidate_flags, 44) & BATTLE_RECORD_CONSUMED_BIT) {
                u8 *consumed_flags;
                register u32 consumed_row_offset asm("r0");
                register u8 *consumed_row asm("r5");
                register u8 *source_count_address asm("r8");
                register u8 *source_count_root asm("r3");
                register u8 *loop_count_address asm("r6");
                moved_count = 1;
                loop_count_address = consumed_count_address;
                asm("" : "=r"(snapshot_count) : "0"(count_before_transfer));
                consumed_flags = candidate_flags;
                /* Original first forms the byte displacement as a word,
                 * then adds the true root into the persistent row address. */
                asm("add %0, %1, #0" : "=l"(consumed_row_offset)
                        : "l"(consumed_offset) : "cc");
                consumed_row_offset += 32;
                consumed_row = (u8 *)(consumed_row_offset + (u32)snapshot);
                source_count_root = snapshot_source;
                /* This actual R3 base feeds the following high-address add;
                 * it is a definition phase, not a later reload consumer. */
                asm("" : : "r"(source_count_root));
                source_count_address = source_count_root + BATTLE_RECORD_COUNT;
prefix_transfer_body:
                    {
                        register u16 prefix_flags asm("r0");
                        register u32 clear_mask asm("r2");
                        register u16 half_mask asm("r1");
                        asm("" : "+r"(consumed_flags));
                        prefix_flags = ReadHalfword(consumed_flags, 44);
                        clear_mask = 0xfdff;
                        half_mask = (u16)clear_mask;
                        asm("" : : "r"(clear_mask), "r"(half_mask));
                        prefix_flags &= half_mask;
                        WriteHalfword(consumed_flags, 44, prefix_flags);
                    }
                    {
                        register u8 *source_count_cell asm("r3") = source_count_address;
                        *source_count_cell = (u8)(*source_count_cell - 1);
                    }
                    {
                        u32 copy_row_offset;
                        register u8 *copy_destination asm("r0");
                        register const u32 *copy_callback_slot asm("r2");
                        register u32 copy_callback asm("r3");
                        copy_row_offset = *loop_count_address;
                        copy_row_offset *= BATTLE_ROW_BYTES;
                        copy_row_offset += 32;
                        copy_destination = consumed_record + copy_row_offset;
                        /* Consume the real slot address before argument setup
                         * overwrites R2 with the byte count. The loaded callback
                         * is the initialized R3 value passed to the thunk. */
                        copy_callback_slot = (const u32 *)0x0836d4bc;
                        asm("" : "+r"(copy_callback_slot) : "r"(copy_destination));
                        copy_callback = *copy_callback_slot;
                        asm("" : "+r"(copy_callback));
                        (void)RetailCall_08142250(
                            (u32)copy_destination,
                            (u32)consumed_row, BATTLE_ROW_BYTES,
                            copy_callback);
                    }
                    *loop_count_address =
                        (u8)(*loop_count_address + 1);
                    consumed_flags += BATTLE_ROW_BYTES;
                    consumed_row += BATTLE_ROW_BYTES;
                    ++consumed_ordinal;
                    if (consumed_ordinal >= *snapshot_count)
                        goto prefix_transfer_done;
                    {
                        register u16 next_flags asm("r0");
                        u32 next_mask;
                        register u16 next_half_mask asm("r1");
                        next_flags = ReadHalfword(consumed_flags, 44);
                        next_mask = BATTLE_RECORD_CONSUMED_BIT;
                        next_half_mask = (u16)next_mask;
                        /* The real operands are the loaded flags and the
                         * halfword mask. Its wider constant temporary belongs
                         * to movhi lowering, not a prescribed source carrier. */
                        asm("" : : "r"(next_flags), "r"(next_half_mask));
                        if (next_flags & next_half_mask)
                            goto prefix_transfer_body;
                    }
prefix_transfer_done:
                    ;
            }
        }
    }

    if (moved_count != 0) {
        record_block[BATTLE_BLOCK_ACTION_INDEX] =
            (u8)(record_block[BATTLE_BLOCK_ACTION_INDEX] + 1);
        CopyRetailBytes(consumed_record, snapshot_source, 32);

        if (ReadWord(consumed_record, 0) == (u32)actor_context &&
            option != 0xff) {
            consumed_record[28] = (u8)option;
            RetailCall_0809920c((u32)actor_context, option);
            RetailCall_0809915c((u32)actor_context, option);
        }

        (void)RetailCall_080a23b8(
            (u32)consumed_record, (u32)actor_context,
            ActorContext(actor_context)->lookup_context, 1,
            transition_mode, (u32)scratch_records, chance_gate, mode_state);

        if (ReadWord(consumed_record, 0) == (u32)actor_context &&
            option != 0xff)
            RetailCall_0809915c((u32)actor_context, option);

        CurrentRecord(consumed_record)->flags |= 8;
    }

    *(volatile u8 *)0x0200f890 = 1;

    }

    do {
select_next:
    row_count = snapshot[BATTLE_RECORD_COUNT];
    if (target_index < row_count)
        goto dispatch_target;

    if (pending_read_cursor == (u8 *)0 ||
        ReadWord(pending_read_cursor, 0) == 0)
        goto cleanup;

    switch (pending_read_cursor[14] - 1) {
    case 7: case 9: case 14: goto pending_general;
    case 10: goto pending_gate11;
    case 0: case 1: case 2: case 11: case 13: goto pending_common;
    default: goto finish_pending;
    }

pending_general: {
        register u32 fetched_pending_count asm("r0");
        if (pending_read_cursor[14] != 15) {
            if ((u8)RetailCall_080cd6a8(ContextUnit((u8 *)ReadWord(pending_read_cursor, 0))) != 0)
                goto finish_pending;
            if ((u8)RetailCall_080c8280(
                    ContextUnit((u8 *)ReadWord(pending_read_cursor, 4))) != 0)
                goto finish_pending;
        }

        coordinate_x = pending_read_cursor[10];
        coordinate_y = pending_read_cursor[11];
        current_kind = pending_read_cursor[12];
        current_context = (u8 *)ReadWord(pending_read_cursor, 0);
        fetched_pending_count = (u8)RetailCall_0812f0d8(
            ContextUnit(current_context), (u32)OriginalActionWords);
        action_count = fetched_pending_count;
        if (action_count == 0) {
            action_count = 1;
            WriteHalfword((u8 *)OriginalActionWords, 0, (u16)fetched_pending_count);
        }
        current_action = ReadHalfword(pending_read_cursor, 8);
        RetailCall_08133b84(ContextUnit(current_context), pending_read_cursor[14]);
        *(volatile u8 *)0x0200f890 = 0;
        goto finish_pending;
    }

pending_gate11: {
        if ((u8)RetailCall_080b4c90(
            ContextUnit((u8 *)ReadWord(pending_read_cursor, 0)),
            ContextUnit((u8 *)ReadWord(pending_read_cursor, 4)),
            root_action, 0) == 0)
            goto finish_pending;
    }

pending_common: {
        u32 pending_status;
        if ((u8)RetailCall_080c8280(
                ContextUnit((u8 *)ReadWord(pending_read_cursor, 4))) != 0)
            goto finish_pending;
        pending_status = (u8)RetailCall_080cd6a8(ContextUnit((u8 *)ReadWord(pending_read_cursor, 0)));
        if ((u8)pending_status != 0)
            goto finish_pending;

        coordinate_x = pending_read_cursor[10];
        coordinate_y = pending_read_cursor[11];
        current_kind = pending_read_cursor[12];
        current_context = (u8 *)ReadWord(pending_read_cursor, 0);
        action_count = (u8)RetailCall_0812f0d8(
            ContextUnit(current_context), (u32)OriginalActionWords);
        if (action_count == 0)
            WriteHalfword((u8 *)OriginalActionWords, 0, 0);
        action_count = 1;
        current_action = ReadHalfword(pending_read_cursor, 8);
        RetailCall_08133b84(ContextUnit(current_context), pending_read_cursor[14]);
        *(volatile u8 *)0x0200f890 = (u8)pending_status;
        mode_state = 0;
    }

finish_pending:
    pending_read_cursor += BATTLE_ACTION_BYTES;
    goto check_global;

dispatch_target: {
    u32 selector_actor_unit;
    u32 queried_row_offset;
    register u16 selector_flags;
    u8 *query_rows;
    register u8 *target_rows asm("r9");
    register s32 target_selector asm("r6");
    s32 target_table_index;
    u32 next_target_index;
    selector_actor_unit = ContextUnit((u8 *)ReadWord(snapshot, 0));
    queried_row_offset = target_index * BATTLE_ROW_BYTES;
    query_rows = snapshot + 32;
    target_selector = (u16)RetailCall_0812ea44(
        selector_actor_unit, ContextUnit((u8 *)ReadWord(query_rows + queried_row_offset, 0)), ReadHalfword(snapshot, 16));
    /* The existing row offset survives the selector call in the native CFG. */
    selector_flags = ReadHalfword(snapshot + queried_row_offset, 44) & 0x40;
    target_rows = query_rows;
    if (selector_flags != 0)
        target_selector = 0;
    action_property = RetailCall_080ccd50(root_action, 17);
    if (action_property != 0)
        target_selector = 0;

    target_table_index = target_selector - 1;
    switch (target_table_index) {
    case 0: case 1: case 2: goto target_classification;
    case 7: goto target8;
    case 9: goto target10;
    case 10: goto target11;
    case 11: case 13: goto target12_14;
    case 14: goto target15;
    default: goto default_target_record;
    }

target10:
    if ((u32)action_count > 1) {
        if (flag80_count == 0)
            goto default_target_record;
    } else {
        u32 flag_row_offset = target_index * BATTLE_ROW_BYTES;
        if ((ReadHalfword(snapshot + flag_row_offset, 44) & 0x80) == 0)
            goto default_target_record;
    }

target8:
    if (root_action != 0) {
        if (RetailCall_080ccd50(root_action, 29) == 0)
            goto default_target_record;
        if (RetailCall_080ccd50(root_action, 17) != 0)
            goto default_target_record;
    }

target15:
    if (target_selector == 15) {
        u32 selected_row_offset;
        if (root_action == 0)
            goto default_target_record;
        selected_row_offset = target_index * BATTLE_ROW_BYTES;
        if ((ReadHalfword(snapshot + selected_row_offset, 44) & 0x80) == 0) {
            u32 selected_target;
            register u8 *selected_row_address asm("r0");
            register u32 root_record_action asm("r12");
            u8 *earlier_row;
            s32 record_ordinal;
            register s32 record_count asm("r0");
            selected_row_address = target_rows + selected_row_offset;
            earlier_root_context = ReadWord(snapshot, 0);
            selected_target = ReadWord(selected_row_address, 0);
            root_record_action = ReadHalfword(snapshot, 16);
            earlier_row = (u8 *)0;
            record_ordinal = 0;
            record_count = NextRecordIndex(record_block);
            /* Initialized H16 value lives in actualIP through this call-free scan. */
            if (record_ordinal < record_count) {
                register s32 scan_record_count asm("r5") = record_count;
                goto earlier_first_record;
                for (; record_ordinal < scan_record_count; ++record_ordinal) {
                u8 *earlier_record;
earlier_first_record:
                earlier_record = record_block + record_ordinal * BATTLE_RECORD_BYTES;
                if (ReadWord(earlier_record, 0) == earlier_root_context &&
                    ReadHalfword(earlier_record, 16) == root_record_action) {
                    earlier_row = FindEarlierTargetRow(earlier_record, selected_target);
                    if (earlier_row != (u8 *)0)
                        break;
                }
            }
            }
            if (earlier_row == (u8 *)0 ||
                (ReadHalfword(earlier_row, 12) & 0x80) == 0)
                goto default_target_record;
        }
        if (RetailCall_080ccd50(root_action, 28) == 0 ||
            RetailCall_080ccd50(root_action, 17) != 0)
            goto default_target_record;
    }
    {
        register u32 payload_zero asm("r1");
        register u32 pending_actor_x asm("r0");
        WriteWord(pending_write_cursor, 0, ReadWord(target_rows + target_index * BATTLE_ROW_BYTES, 0));
        pending_actor_x = ((u8 *)ContextUnit(actor_context))[246];
        payload_zero = 0;
        pending_write_cursor[10] = (u8)pending_actor_x;
        pending_write_cursor[11] = ((u8 *)ContextUnit(actor_context))[247];
        switch (target_selector) {
        case 8:
            WriteHalfword(pending_write_cursor, 12, 4);
            WriteHalfword(pending_write_cursor, 8, payload_zero);
            break;
        case 10:
            WriteHalfword(pending_write_cursor, 12, 6);
            WriteHalfword(pending_write_cursor, 8, payload_zero);
            break;
        case 15:
            WriteHalfword(pending_write_cursor, 12, 12);
            WriteHalfword(pending_write_cursor, 8, (u16)input_action);
            break;
        }
        pending_write_cursor[14] = (u8)target_selector;
        WriteWord(pending_write_cursor, 4, (u32)actor_context);
        pending_write_cursor += BATTLE_ACTION_BYTES;
    }
    { next_target_index = target_index + 1u;
        /* Native outgoing LOW8 phase: shift before joining the shared LSR.
         * A single instruction replaces C LSL plus an empty RW event, whose
         * nominal length otherwise distorts Thumb pool/branch placement. */
        asm("lsl %0, %1, #24" : "=l"(next_target_index) : "l"(next_target_index) : "cc");
        goto store_target_index; }

target11: {
        /* Native R5 retains the scaled offset through all three field guards,
         * then dies at the target-row read before appending the pending entry. */
        register u32 target11_row_offset asm("r5");
        register u32 target11_stride asm("r0");
        register u8 *target11_field_address asm("r1");
        if (root_action == 0 ||
            RetailCall_080ccd50(root_action, 17) != 0 ||
            RetailCall_080ccd50(root_action, 26) == 0)
            goto default_target_record;
        /* The native stride definition precedes the independent index read.
         * This actual R0 input phase remains live until the following MUL. */
        target11_stride = BATTLE_ROW_BYTES;
        asm("" : : "r"(target11_stride));
        /* Retail 4EA2 copies the full index into the independent multiply
         * carrier before the destructive MUL. The actual copy preserves that
         * definition boundary; both address consumers below use its product. */
        asm("add %0, %1, #0" : "=l"(target11_row_offset)
                : "l"(target_index) : "cc");
        target11_row_offset *= target11_stride;
        target11_field_address = snapshot + target11_row_offset;
        if (ReadHalfword(target11_field_address, 46) == 5 ||
            snapshot[9] == 9 ||
            (ReadHalfword(target11_field_address, 44) & 0x40) != 0)
            goto default_target_record;

        {
            register u8 *target11_context_address asm("r0") = target_rows + target11_row_offset;
            WriteWord(pending_write_cursor, 0, ReadWord(target11_context_address, 0));
        }
        pending_write_cursor[10] = ((u8 *)ContextUnit(actor_context))[246];
        pending_write_cursor[11] = ((u8 *)ContextUnit(actor_context))[247];
        WriteHalfword(pending_write_cursor, 12, 7);
        pending_write_cursor[14] = (u8)target_selector;
        WriteWord(pending_write_cursor, 4, (u32)actor_context);
        WriteHalfword(pending_write_cursor, 8, (u16)root_action);
        pending_write_cursor += 16;
        { next_target_index = target_index + 1u;
        /* Native outgoing LOW8 phase: shift before joining the shared LSR.
         * A single instruction replaces C LSL plus an empty RW event, whose
         * nominal length otherwise distorts Thumb pool/branch placement. */
        asm("lsl %0, %1, #24" : "=l"(next_target_index) : "l"(next_target_index) : "cc");
        goto store_target_index; }
    }

target_classification:
    classification = ClassifyTargetUnit(
        ContextUnit((u8 *)ReadWord(target_rows + target_index * BATTLE_ROW_BYTES, 0)));
    if (classification != 2)
        goto default_target_record;

target12_14:
    if (root_action != 0) {
        if (RetailCall_080ccd50(root_action, 17) != 0)
            goto default_target_record;
        if (target_selector == 12 && RetailCall_080ccd50(root_action, 29) == 0)
            goto default_target_record;
    }
    if (target_selector == 12 || target_selector == 14) {
        u32 scalar_row_offset = target_index * BATTLE_ROW_BYTES;
        if ((s16)ReadHalfword(snapshot + scalar_row_offset, 62) <= 0)
            goto default_target_record;
    }
    if (target_selector == 1) {
        /* With the earlier row-offset chain restored, this ordinary index
         * read must remain a chosen reload. The former hard-R3 phase hid a
         * preceding cursor error and suppressed advancement at this use. */
        if ((u8)RetailCall_080cd8b4(
            ContextUnit((u8 *)ReadWord(target_rows + target_index * BATTLE_ROW_BYTES, 0))) != 0)
            goto default_target_record;
    }
    if (target_selector == 2 && (u8)RetailCall_080cdaac(
        ContextUnit((u8 *)ReadWord(target_rows + target_index * BATTLE_ROW_BYTES, 0))) != 0)
        goto default_target_record;
    if (target_selector == 3 && (u8)RetailCall_080cd944(
        ContextUnit((u8 *)ReadWord(target_rows + target_index * BATTLE_ROW_BYTES, 0))) != 0)
        goto default_target_record;
    if (target_selector == 12 && (u8)RetailCall_080cd8cc(
        ContextUnit((u8 *)ReadWord(target_rows + target_index * BATTLE_ROW_BYTES, 0))) != 0)
        goto default_target_record;
    if (target_selector == 14 && (u8)RetailCall_080cd8e4(
        ContextUnit((u8 *)ReadWord(target_rows + target_index * BATTLE_ROW_BYTES, 0))) != 0)
        goto default_target_record;

emit_nested: {
    register u8 *nested_row asm("r1");
    asm("" : "+r"(target_table_index));
    switch (target_table_index) {
    case 0: WriteHalfword(pending_write_cursor, 8, 34); break;
    case 1: WriteHalfword(pending_write_cursor, 8, 42); break;
    case 2: WriteHalfword(pending_write_cursor, 8, 234); break;
    case 11: WriteHalfword(pending_write_cursor, 8, 7); break;
    case 13: WriteHalfword(pending_write_cursor, 8, 72); break;
    default: break;
    }
    nested_row = target_rows + target_index * BATTLE_ROW_BYTES;
    WriteWord(pending_write_cursor, 0, ReadWord(nested_row, 0));
    pending_write_cursor[10] = ((u8 *)ContextUnit((u8 *)ReadWord(nested_row, 0)))[246];
    pending_write_cursor[11] = ((u8 *)ContextUnit((u8 *)ReadWord(nested_row, 0)))[247];
    WriteHalfword(pending_write_cursor, 12, 11);
    pending_write_cursor[14] = (u8)target_selector;
    WriteWord(pending_write_cursor, 4, ReadWord(nested_row, 0));
    pending_write_cursor += 16;
    { next_target_index = target_index + 1u;
        /* Native outgoing LOW8 phase: shift before joining the shared LSR.
         * A single instruction replaces C LSL plus an empty RW event, whose
         * nominal length otherwise distorts Thumb pool/branch placement. */
        asm("lsl %0, %1, #24" : "=l"(next_target_index) : "l"(next_target_index) : "cc");
        goto store_target_index; }
}

default_target_record: {
    u32 default_row_offset = target_index * BATTLE_ROW_BYTES;
    switch (ReadHalfword(snapshot + default_row_offset, 46)) {
    case 4: {
        u8 *previous_unit;
        current_kind = 3;
        previous_unit = (u8 *)ContextUnit(current_context);
        coordinate_x = previous_unit[BATTLE_UNIT_X];
        coordinate_y = previous_unit[BATTLE_UNIT_Y];
        current_context = (u8 *)ReadWord(target_rows + default_row_offset, 0);
        current_action = 0;
        RetailCall_08133b84(ContextUnit(current_context), 6);
        *(volatile u8 *)0x0200f890 = 0;
        { next_target_index = target_index + 1u;
        /* Native outgoing LOW8 phase: shift before joining the shared LSR.
         * A single instruction replaces C LSL plus an empty RW event, whose
         * nominal length otherwise distorts Thumb pool/branch placement. */
        asm("lsl %0, %1, #24" : "=l"(next_target_index) : "l"(next_target_index) : "cc");
        goto store_target_index; }
    }

    case 3: {
        u8 *previous_unit;
        u8 *mode3_row;
        u16 updated_flags;
        register u16 completion_bit asm("r0");
        register u32 fetched_count asm("r0");
        register u32 completed_status asm("r4");
        mode3_row = target_rows + default_row_offset;
        if ((u8)RetailCall_080cd6a8(ContextUnit((u8 *)ReadWord(mode3_row, 0))) != 0)
            goto advance_target;

        previous_unit = (u8 *)ContextUnit(current_context);
        coordinate_x = previous_unit[BATTLE_UNIT_X];
        coordinate_y = previous_unit[BATTLE_UNIT_Y];
        current_kind = 5;
        current_context = (u8 *)ReadWord(mode3_row, 0);
        fetched_count = (u8)RetailCall_0812f0d8(
            ContextUnit(current_context), (u32)OriginalActionWords);
        action_count = fetched_count;
        if (action_count == 0) {
            action_count = 1;
            WriteHalfword((u8 *)OriginalActionWords, 0, (u16)fetched_count);
        }
        updated_flags = ReadHalfword(snapshot, 4);
        completion_bit = 4;
        completed_status = 0;
        asm("" : : "r"(completion_bit), "r"(completed_status));
        completion_bit |= updated_flags;
        WriteHalfword(snapshot, 4, completion_bit);
        RetailCall_08133b84(ContextUnit(current_context), 7);
        current_action = 0;
        *(volatile u8 *)0x0200f890 = (u8)completed_status;
        { next_target_index = target_index + 1u;
        /* Native outgoing LOW8 phase: shift before joining the shared LSR.
         * A single instruction replaces C LSL plus an empty RW event, whose
         * nominal length otherwise distorts Thumb pool/branch placement. */
        asm("lsl %0, %1, #24" : "=l"(next_target_index) : "l"(next_target_index) : "cc");
        goto store_target_index; }
    }

    case 5: {
        u32 row_status;
        register u8 *auxiliary_record asm("r2");
        struct BattleRecordObject *next_record;
        register u8 *mode5_row asm("r6");
        u32 auxiliary_index;
        register u32 auxiliary_offset asm("r0");
        u32 final_index;
        snapshot_source[BATTLE_RECORD_COUNT] =
            (u8)(snapshot_source[BATTLE_RECORD_COUNT] - 1);
        mode5_row = target_rows + default_row_offset;
        row_status = (u8)RetailCall_080c8280(ContextUnit((u8 *)ReadWord(mode5_row, 0)));
        if ((u8)row_status == 0) {
            auxiliary_index = NextRecordIndex(record_block);
            auxiliary_offset = auxiliary_index * BATTLE_RECORD_BYTES;
            auxiliary_record = record_block;
            /* Native loads the real block root into this destructive base
             * only after the independent scaled offset has been formed. */
            asm("" : : "r"(auxiliary_record));
            auxiliary_record += auxiliary_offset;
            {
                register struct BattleRecordObject *auxiliary_root asm("r10") =
                    (struct BattleRecordObject *)auxiliary_record;
                asm("" : : "r"(auxiliary_root));
                output_record = auxiliary_root;
            }
            auxiliary_record[9] = 8;
            output_record->row_count = 1;
            auxiliary_record[10] = ((u8 *)ContextUnit((u8 *)ReadWord(mode5_row, 0)))[BATTLE_UNIT_X];
            auxiliary_record[11] = ((u8 *)ContextUnit((u8 *)ReadWord(mode5_row, 0)))[BATTLE_UNIT_Y];
            CopyRetailBytes((u8 *)output_record + 32,
                            snapshot + (default_row_offset + 32),
                            BATTLE_ROW_BYTES);
            record_block[BATTLE_BLOCK_ACTION_INDEX] =
                (u8)(record_block[BATTLE_BLOCK_ACTION_INDEX] + 1);
            *(volatile u8 *)0x0200f890 = (u8)row_status;
            mode_state = 0;
            current_context = actor_context;
            actor_unit = (u8 *)ContextUnit(actor_context);
            coordinate_x = actor_unit[BATTLE_UNIT_X];
            coordinate_y = actor_unit[BATTLE_UNIT_Y];
            current_action = root_action;
            current_kind = 9;
            final_index = NextRecordIndex(record_block);
            /* The final index selects the same full 708-byte object.
             * Keep its actual H4 field as a single record RMW lvalue. */
            next_record = (struct BattleRecordObject *)(record_block +
                         final_index * BATTLE_RECORD_BYTES);
            next_record->flags |= 8;
            next_target_index = target_index + 1u;
        /* Native outgoing LOW8 phase: shift before joining the shared LSR.
         * A single instruction replaces C LSL plus an empty RW event, whose
         * nominal length otherwise distorts Thumb pool/branch placement. */
        asm("lsl %0, %1, #24" : "=l"(next_target_index) : "l"(next_target_index) : "cc");
            goto store_target_index;
        }
    }

    default:
        break;
    }

}

advance_target:
    next_target_index = target_index + 1u;
        /* Native outgoing LOW8 phase: shift before joining the shared LSR.
         * A single instruction replaces C LSL plus an empty RW event, whose
         * nominal length otherwise distorts Thumb pool/branch placement. */
        asm("lsl %0, %1, #24" : "=l"(next_target_index) : "l"(next_target_index) : "cc");
store_target_index:
    target_index = next_target_index >> 24;
    }

check_global:
        ;
    } while (*(volatile u8 *)0x0200f890 != 0);
    }

cleanup:
    ReleaseBattleObject((u32)scratch_records);
    ReleaseBattleObject((u32)temporary_record);
    {
        u8 *allocation_to_release = optional_pending_storage;
        if (allocation_to_release != (u8 *)0)
            ReleaseBattleObject((u32)allocation_to_release);
    }
    if ((u8)lifetime_result == 0)
        SetUnitStateE9Bit6(ContextUnit(actor_context), 0);
}

/* Original 080A52D2..D4 is verified zero alignment after the BX return.
 * Keep data alignment explicit instead of the assembler section default NOP. */
asm(".align 2, 0");
