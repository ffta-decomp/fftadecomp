/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08020DA0.c
 * Original SHA-256: 443d850bf22b2499601a6f830d5ca4af7505f4536eb27f4e399315ca791c72a6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 active;
    u8 status;
    u16 flags;
    u8 field_04;
    s8 field_05;
    u8 unknown_06[2];
    u16 identifier;
    u16 timing;
    u16 counter;
    u16 field_0E;
    const u8 *record;
    u32 parameters;
    const u8 *source;
    u32 current_parameters;
    const u8 *source_end;
    u8 unknown_24[8];
} Slot08020DA0;

typedef struct {
    u16 timing;
    u8 unknown_02[2];
    Slot08020DA0 slots[4];
} State08020DA0;

typedef void (*BufferInitializer08020DA0)(void *destination, u32 size);
extern BufferInitializer08020DA0 const g_callbacks_0836D4B8[];
extern State08020DA0 *g_state_0200F1D4;

static inline Slot08020DA0 *find_free_slot(void)
{
    u8 index;

    for (index = 0; index < 4; index++) {
        if (g_state_0200F1D4->slots[index].active == 0)
            return &g_state_0200F1D4->slots[index];
    }
    return 0;
}

static inline u16 read_little_endian_u16(const u8 *bytes)
{
    u16 low = bytes[0];
    u16 high = bytes[1] << 8;

    return high | low;
}

/* Complete [0x08020DA0, 0x08020E3C): 156 bytes, 70 instructions. */
Slot08020DA0 *func_08020DA0(const u8 *record, u32 parameters, const u8 *source)
{
    Slot08020DA0 *slot = find_free_slot();

    g_callbacks_0836D4B8[0](slot, sizeof(Slot08020DA0));
    slot->status = 0;
    slot->flags = 1;
    slot->field_04 = 0xFF;
    slot->field_05 = -1;
    slot->identifier = read_little_endian_u16(record);
    slot->timing = g_state_0200F1D4->timing;
    slot->counter = 0;
    slot->record = record;
    slot->parameters = parameters;
    slot->source = source;
    slot->current_parameters = parameters;
    slot->source_end = source + (read_little_endian_u16(record + 6) << 5);
    slot->field_0E = 1;
    slot->active = 1;
    return slot;
}
