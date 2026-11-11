typedef unsigned char u8;
typedef unsigned int u32;

#define BATTLE_OBJECT_COUNT (*(volatile u8 *)0x03006168)
#define BATTLE_OBJECT_LIST (*(u8 * volatile *)0x0300616c)
#define BATTLE_OBJECT_STRIDE 0x98a
#define BATTLE_OBJECT_STATE_OFFSET 0x980
#define BATTLE_OBJECT_STATE_COPY_SOURCE ((const u32 *)0x0836d4b8)

extern void CallR2Trampoline(void *destination, u32 length, u32 target);

/* Publish an object pool and initialize each eight-byte observed state record. */
void InitializeBattleObjectStatePool(u8 *object, int count)
{
    u8 *current;
    int index;

    BATTLE_OBJECT_LIST = object;
    /* Keep the two published IWRAM addresses as separate literal loads. */
    __asm__ volatile("" ::: "r2");
    BATTLE_OBJECT_COUNT = count;
    current = object;
    index = 0;
    if (index < count) {
        const u32 *copy_source = BATTLE_OBJECT_STATE_COPY_SOURCE;

        do {
            CallR2Trampoline(current + BATTLE_OBJECT_STATE_OFFSET, 8,
                             *copy_source);
            ++index;
            current += BATTLE_OBJECT_STRIDE;
        /* The retail loop rereads the published byte count after every call. */
        } while (index < BATTLE_OBJECT_COUNT);
    }
}
