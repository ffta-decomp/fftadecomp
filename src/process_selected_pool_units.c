typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 gSaveData[];
extern void ProcessSelectedPoolUnitEntry(u8 *unit);

/* Apply the observed follow-up routine to each gated 264-byte unit record. */
void ProcessSelectedPoolUnits(void)
{
    u8 slot = 0;
    u8 *pool = gSaveData;
    u8 *payloads = pool + 0x80;
    for (; slot < 24; ++slot) {
        u32 offset = slot * 264;
        /* Offset-first addition retains the retail r2+r5 address order. */
        u8 *unit = (u8 *)(offset + (u32)pool);
        if (unit[0x84] != 0 && unit[0x170] == 0 &&
            (*(u16 *)(unit + 0xa8) & 8) != 0)
            ProcessSelectedPoolUnitEntry((u8 *)(offset + (u32)payloads));
    }
}
