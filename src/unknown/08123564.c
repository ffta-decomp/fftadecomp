typedef unsigned char u8;
typedef unsigned int u32;
extern void MergeScenePaths_081257D0(u32 first_slot, u32 second_slot, u32 destination_slot);
u32 ApplyScenePathMergeOperands(void *unused_context, const u8 *command)
{
    register const u8 *operands __asm__("r2") = command;
    register u32 packed __asm__("r1");
    register u32 first_slot __asm__("r0");
    u32 destination_slot;
    /* Keep the initialized command snapshot while R1 becomes the packed
       operand and then the upper nibble. These empty constraints emit no code. */
    asm("" : "+r"(operands));
    packed = operands[1];
    asm("" : : "r"(packed));
    first_slot = 15;
    asm("" : "+r"(first_slot));
    first_slot &= packed;
    asm("" : : "r"(first_slot));
    packed >>= 4;
    asm("" : : "r"(packed));
    destination_slot = operands[2];
    MergeScenePaths_081257D0(first_slot, packed, destination_slot);
    return 0x110;
}
asm(".global MergeScenePaths_081257D0\n.thumb_set MergeScenePaths_081257D0,0x081257d1\n");
