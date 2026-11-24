typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

/* Effect callbacks accumulate state kinds in the bitmap at context+16. */
void MarkEffectState(u8 *context, s32 state_kind)
{
    u8 *bitmap = context + 16;
    s32 byte_index = state_kind >> 3;
    s32 bit_index = state_kind & 7;
    u32 bit;
    bitmap += byte_index;
    bit = 1u << bit_index;
    *bitmap |= bit;
}
