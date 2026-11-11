/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
extern unsigned UnitField27HasBit14(const void *unit);
extern unsigned UnitField27HasBit6(const void *unit);
/* Verified declaration-only original targets; no instructions emitted. */
asm(".global UnitField27HasBit14\n.thumb_set UnitField27HasBit14,0x080c82b9\n.global UnitField27HasBit6\n.thumb_set UnitField27HasBit6,0x080c832d");


/* These are observed halfword marker codes; the surrounding layout is unknown. */
void WriteUnitStatusMarkerTiles(u16 *tiles, const void *unit)
{
    if ((u8)UnitField27HasBit14(unit) != 0) {
        u16 *cell = tiles + 49;
        *cell = 0xd0d8;
        cell += 17;
        *cell = 0xd0d9;
        cell -= 16;
        *cell = 0xd0da;
    }
    if ((u8)UnitField27HasBit6(unit) != 0)
        tiles[82] = 0xd0d7;
}
