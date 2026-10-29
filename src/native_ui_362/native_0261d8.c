/* First fixed-O2 draft mapped from original Thumb 080261d8..0802657e. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 Call_08096d7c(u32);
extern u32 Call_080970e8(u32, u8 *);
extern u32 Call_080c7ea4(u8 *, u32);
extern u32 Call_080c9540(u32);
extern u32 Call_08025fdc(u32);
extern u32 Call_08025f8c(u32);
extern u32 Call_080c95a8(u32);
extern u32 Call_080161bc(u32);
extern u32 Call_080260e0(u8 *, u16 *);
extern u32 Call_080c8240(u8 *);
extern u32 Call_080cd4c0(u8 *);

__asm__(".global Call_08096d7c\n.thumb_set Call_08096d7c, 0x08096d7d");
__asm__(".global Call_080970e8\n.thumb_set Call_080970e8, 0x080970e9");
__asm__(".global Call_080c7ea4\n.thumb_set Call_080c7ea4, 0x080c7ea5");
__asm__(".global Call_080c9540\n.thumb_set Call_080c9540, 0x080c9541");
__asm__(".global Call_08025fdc\n.thumb_set Call_08025fdc, 0x08025fdd");
__asm__(".global Call_08025f8c\n.thumb_set Call_08025f8c, 0x08025f8d");
__asm__(".global Call_080c95a8\n.thumb_set Call_080c95a8, 0x080c95a9");
__asm__(".global Call_080161bc\n.thumb_set Call_080161bc, 0x080161bd");
__asm__(".global Call_080260e0\n.thumb_set Call_080260e0, 0x080260e1");
__asm__(".global Call_080c8240\n.thumb_set Call_080c8240, 0x080c8241");
__asm__(".global Call_080cd4c0\n.thumb_set Call_080cd4c0, 0x080cd4c1");

#define ROOT (*(u8 **)0x0200f438)
#define LIVE_UNIT ((u8 *)WORD(ROOT, 24))
#define HALF(base, off) (*(u16 *)((base) + (off)))
#define WORD(base, off) (*(u32 *)((base) + (off)))

/* The ROM row is accessed as two individual bytes in the original. */
#define UPDATE_MAXIMUM(number) \
    { \
        register const u32 *item_bank asm("r2") = (const u32 *)0x085567f0; \
        register const u8 *property_row asm("r0"); \
        register u32 index asm("r0"); \
        u32 item, result; \
        asm("" : "+r"(item_bank)); \
        property_row = (const u8 *)(0x08527244 + 4 * (number)); \
        asm("" : "+r"(property_row)); \
        index = property_row[0] | ((u32)property_row[1] << 8); \
        asm("" : "+r"(index)); \
        item = item_bank[index]; \
        result = (u16)Call_080161bc(item); \
        if (result > maximum) maximum = result; \
    }

void Source52_000261D8(u8 *context)
{
    u8 *summary = context + 128;
    u8 *descriptor;
    u8 *unit;
    u8 *type_bytes;
    register u32 slot asm("r6") = 0;
    u32 maximum = 6;
    register u32 status asm("r8");
    u32 gate_status;
    u32 first_type;
    u32 value;
    u32 enabled;
    u16 output_half;

    asm("" : "+r"(slot));
    {
    u32 initial_result = Call_08096d7c(6);
    if (Call_080970e8(initial_result, LIVE_UNIT) != 0 &&
        Call_080c7ea4(LIVE_UNIT, 3) == 13) {
        HALF(summary, 4)--;
    } else {
        u8 *first_destination = ROOT + 1152;
        first_destination += slot;
        asm("" : "+r"(first_destination));
        first_type = 12;
        *first_destination = first_type;
        if ((u8)Call_080c9540(2) != 0) {
            summary[2] -= 4;
            summary[0] += 4;
            ((u32 *)WORD(context, 148))[slot] = 13;
        } else {
            ((u32 *)WORD(context, 148))[slot] = first_type;
        }
        { register u32 next_slot asm("r0") = slot + 1; asm("" : "+r"(next_slot)); slot = (u8)next_slot; }
    }

    }

    descriptor = (u8 *)Call_080c7ea4(LIVE_UNIT, 34);
    gate_status = (u8)Call_080c9540(2);
    status = gate_status;
    asm("" : : "r"(status));
    if (gate_status != 0) {
        HALF(summary, 4)--;
    } else {
        register u8 *phase_destination asm("r0") = ROOT + 1152;
        asm("" : "+r"(phase_destination));
        phase_destination += slot;
        asm("" : "+r"(phase_destination));
        *phase_destination = 13;
        ((u32 *)WORD(context, 148))[slot] = descriptor[1];
        if ((u8)Call_08025fdc(6) == 0 ||
            (u8)Call_08025f8c(descriptor[1]) == 0 ||
            ((u8)Call_080c95a8(13) == 1 && descriptor[1] == 30))
            ((u8 *)WORD(context, 152))[slot] = status;
        UPDATE_MAXIMUM(descriptor[1]);
        { register u32 next_slot asm("r0") = slot + 1; asm("" : "+r"(next_slot)); slot = (u8)next_slot; }
    }

    if (descriptor[2] == 0) {
        HALF(summary, 4)--;
    } else {
        register u32 disabled14 asm("r8");
        register u8 *type_destination asm("r0");
        type_destination = ROOT + 1152;
        asm("" : "+r"(type_destination));
        type_destination += slot;
        disabled14 = 0;
        asm("" : "+r"(disabled14) : "r"(type_destination));
        *type_destination = 14;
        ((u32 *)WORD(context, 148))[slot] = descriptor[2];
        if ((u8)Call_08025fdc(7) == 0 ||
            (u8)Call_08025f8c(descriptor[2]) == 0 ||
            ((u8)Call_080c95a8(13) == 1 && descriptor[2] == 30))
            ((u8 *)WORD(context, 152))[slot] = disabled14;
        UPDATE_MAXIMUM(descriptor[2]);
        { register u32 next_slot asm("r0") = slot + 1; asm("" : "+r"(next_slot)); slot = (u8)next_slot; }
    }

    if (descriptor[3] == 0) {
        HALF(summary, 4)--;
    } else {
        register u32 disabled15 asm("r8");
        register u8 *type_destination asm("r0");
        type_destination = ROOT + 1152;
        asm("" : "+r"(type_destination));
        type_destination += slot;
        disabled15 = 0;
        asm("" : "+r"(disabled15) : "r"(type_destination));
        *type_destination = 15;
        ((u32 *)WORD(context, 148))[slot] = descriptor[3];
        if ((u8)Call_08025f8c(descriptor[3]) == 0 ||
            ((u8)Call_080c95a8(13) == 1 && descriptor[3] == 30))
            ((u8 *)WORD(context, 152))[slot] = disabled15;
        UPDATE_MAXIMUM(descriptor[3]);
        { register u32 next_slot asm("r0") = slot + 1; asm("" : "+r"(next_slot)); slot = (u8)next_slot; }
    }

    unit = LIVE_UNIT;
    enabled = (u8)Call_080c7ea4(unit, 38);
    if ((u8)Call_080260e0(LIVE_UNIT, &output_half) == 0) {
        HALF(summary, 4)--;
    } else {
        register u8 *phase_destination asm("r0") = ROOT + 1152;
        asm("" : "+r"(phase_destination));
        phase_destination += slot;
        asm("" : "+r"(phase_destination));
        *phase_destination = 16;
        ((u32 *)WORD(context, 148))[slot] = output_half;
        if ((u8)Call_08025f8c(0) == 0)
            ((u8 *)WORD(context, 152))[slot] = 0;
        { register u32 next_slot asm("r0") = slot + 1; asm("" : "+r"(next_slot)); slot = (u8)next_slot; }
    }

    if ((u8)Call_080c9540(2) != 0 ||
        enabled == 0 ||
        (u8)Call_080c8240(LIVE_UNIT) != 0 ||
        (u8)Call_080cd4c0(LIVE_UNIT) == 0) {
        HALF(summary, 4)--;
    } else {
        register u8 *phase_destination asm("r0") = ROOT + 1152;
        asm("" : "+r"(phase_destination));
        phase_destination += slot;
        asm("" : "+r"(phase_destination));
        *phase_destination = 17;
        ((u32 *)WORD(context, 148))[slot] = 15;
        if ((u8)Call_08025f8c(0) == 0)
            ((u8 *)WORD(context, 152))[slot] = 0;
    }

    {
        register u32 raw_count asm("r0") = HALF(summary, 4);
        asm("" : "+r"(raw_count));
        value = raw_count;
        asm("" : "+r"(raw_count) : "r"(value));
        summary[3] = (u8)raw_count;
        if ((u16)raw_count <= 5)
            summary[1] += 2 * (6 - value);
    }
    summary[2] = (u8)maximum;
    summary[0] = (u8)(28 - maximum);
    if ((u8)maximum > 10) {
        register u32 increment asm("r0") = maximum + 245;
        /* Actual full-word displacement precedes the fresh byte read. */
        asm("" : "+r"(increment));
        context[11] = increment + context[11];
    } else
        summary[9] &= 0xef;
}
