typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

extern u8 ReadRuleStateChannel(u32 rule_index, s32 state_index, u8 channel);
__asm__(".global ReadRuleStateChannel\n"
        ".thumb_set ReadRuleStateChannel,0x081339cd\n");

/* This local predicate preserves the observed normalized bit-reader join. */
static inline u8 required_state_selected(const u8 *mask, s32 state_index)
{
    s32 byte_index;
    s32 bit_offset;
    s32 mask_byte;

    byte_index = state_index >> 3;
    bit_offset = 7;
    bit_offset &= state_index;
    mask_byte = mask[byte_index];
    if ((mask_byte >> bit_offset) & 1)
        return 1;
    return 0;
}

/* Only the 44 defined state bits participate. Check each selected bit against
 * channel zero and stop at the first rejection; no mask snapshot spans a call. */
u32 RequiredStatesAllowedByRule(const u8 *required_mask, u32 rule_index)
{
    s32 state_index;

    for (state_index = 0; state_index <= 43; ++state_index) {
        if (required_state_selected(required_mask, state_index)) {
            if (ReadRuleStateChannel(rule_index, state_index, 0) == 0)
                return 0;
        }
    }
    return 1;
}
