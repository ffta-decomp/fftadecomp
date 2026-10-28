#include "../../../src/task_tree_core.h"
extern const u32 SaveChecksumTable[256];
u32 CalculateSaveImageChecksum(const u8 *bytes,u32 length,u32 seed)
{
    u32 checksum = ~seed;
    u16 index;
    for (index = 0; index < length; ++index) {
        u32 table_index = bytes[index];
        table_index ^= checksum;
        table_index = (u8)table_index;
        checksum = ((checksum >> 8) & 0x00ffffff) ^ SaveChecksumTable[table_index];
    }
    {
        register u32 final_checksum asm("r2") = ~checksum;
        /* Retail materializes this actual complemented result in R2 before return. */
        asm("" : "+r" (final_checksum));
        return final_checksum;
    }
}
asm(".global SaveChecksumTable\n.set SaveChecksumTable,0x08393318\n");
