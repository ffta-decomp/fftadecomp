typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

/* Paired state channels use only the low byte of the selector. */
u32 ReadEffectStateChannel(const u8 *mask, s32 state_index, u32 channel_selector)
{
    s32 byte_index;
    s32 bit_offset;
    s32 mask_byte;
    channel_selector = (u8)channel_selector;
    state_index = (s32)((u32)state_index << 1);
    if (channel_selector != 0)
        state_index = (s32)((u32)state_index + 1);
    byte_index = state_index >> 3;
    bit_offset = 7;
    bit_offset &= state_index;
    mask_byte = mask[byte_index];
    if ((mask_byte >> bit_offset) & 1)
        return 1;
    return 0;
}
