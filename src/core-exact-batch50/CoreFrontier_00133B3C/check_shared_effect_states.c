typedef unsigned char u8;
typedef unsigned int u32;
extern u32 ReadSharedEffectStateMask(u32 effect_tag, int state_index, u32 channel);
asm(".global ReadSharedEffectStateMask\n.thumb_set ReadSharedEffectStateMask,0x08133b25");

static inline u8 StateBitIsSet(const u8 *states, int state_index)
{
    int byte_index = state_index >> 3;
    int bit_offset = 7;
    int state_byte;
    bit_offset &= state_index;
    state_byte = states[byte_index];
    if ((state_byte >> bit_offset) & 1)
        return 1;
    return 0;
}

/* The caller owns the live44-state vector; opaque mask queries may change it. */
u32 AreStatesCompatibleWithSharedEffect(const u8 *states, u32 effect_tag)
{
    int state_index;
    for (state_index = 0; state_index <= 43; ++state_index) {
        if (StateBitIsSet(states, state_index)) {
            if ((u8)ReadSharedEffectStateMask(effect_tag, state_index, 0) == 0)
                return 0;
        }
    }
    return 1;
}
