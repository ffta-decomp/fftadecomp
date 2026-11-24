typedef unsigned char u8;
typedef unsigned short u16;
extern u8 UnitPairGameState[];

u8 CountOccupiedSelectionRecordIds(void)
{
    int count = 0;
    register const u8 *game asm("r1") = UnitPairGameState;
    register unsigned int bound asm("r0");

    asm("" : "+r" (game), "+r" (count));
    bound = game[0x3c32];
    asm("" : "+r" (bound));
    if (count < (int)bound) {
        register unsigned int table_offset asm("r4") = 0x3c34;
        register const u16 *records asm("r2");
        int remaining;
        asm("" : "+r" (table_offset));
        records = (const u16 *)(game + table_offset);
        asm("" : "+r" (records));
        remaining = bound;
        do {
            if (*records != 0)
                ++count;
            ++records;
            --remaining;
        } while (remaining != 0);
    }
    return count;
}

asm(".global UnitPairGameState\n.set UnitPairGameState, 0x02000000\n");
