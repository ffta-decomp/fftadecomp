typedef unsigned char u8;

/* Leave an inactive object untouched. Otherwise retain its high state bit
 * and clear the two observed transient bytes beside it. Volatile preserves
 * the retail routine's second state-byte read before the masked write.
 */
void ClearActiveBattleObjectTransientState(volatile u8 *object)
{
    if (object[0x980] & 0x7f) {
        int state;
        int high_bit_mask;

        /* Keep the retail address recomputation and second state read. */
        __asm__ volatile("" : "+r" (object));
        state = object[0x980];
        /* Evaluate the signed mask after loading the observed state byte. */
        __asm__ volatile("" : "+r" (state));
        high_bit_mask = -128;
        high_bit_mask &= state;
        object[0x980] = high_bit_mask;
        object[0x984] = 0;
        object[0x985] = 0;
    }
}
