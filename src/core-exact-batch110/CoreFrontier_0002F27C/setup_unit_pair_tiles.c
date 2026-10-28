typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u32 prefix[4]; u8 *tiles; } Screen;
extern u8 *PaletteByIndex(u8);
extern u32 DecodePairTiles(void *, const void *);
extern void *AllocatePairTransfer(void);
extern void InitializePairTransfer(void *, const void *, void *, u16);
extern void CopyPairPalette(void *, const void *, u32, void *);
extern void ClearPairRows(void *, u32, void *);
asm(".thumb_set PaletteByIndex, 0x080CBABD\n"
    ".thumb_set DecodePairTiles, 0x0800543D\n"
    ".thumb_set AllocatePairTransfer, 0x0802DFCD\n"
    ".thumb_set InitializePairTransfer, 0x08000ADD\n"
    ".thumb_set CopyPairPalette, 0x08142251\n"
    ".thumb_set ClearPairRows, 0x0814224D\n");
void CoreFrontier_0002F27C(u8 alternate)
{
    void **copy_cell = (void **)0x0836D4BC;
    u8 *palette = (u8 *)0x03003940;
    u8 *tiles;
    void **clear_cell;
    void *request;
    u8 *destination;
    u32 first_offset;
    register u32 cursor_offset asm("r2");
    CopyPairPalette(palette, PaletteByIndex(20), 32, *copy_cell);
    CopyPairPalette(palette + 64, PaletteByIndex(22), 32, *copy_cell);
    palette += 32;
    CopyPairPalette(palette, PaletteByIndex(26), 32, *copy_cell);
    tiles = (u8 *)0x02003CB0;
    DecodePairTiles(tiles, (void *)0x083C4888);
    request = AllocatePairTransfer();
    destination = ((Screen *)0x030008B0)->tiles;
    first_offset = 7168;
    /* Original computes a short-lived offset here, separate from the later cursor step. */
    asm("" : "+r"(first_offset));
    InitializePairTransfer(request, tiles, destination + first_offset, 368);
    cursor_offset = 7168;
    /* This initialized short-site offset uses original r2; no callee-save lifetime. */
    asm("" : "+r"(cursor_offset));
    /* The original 2-byte ADD retains destination-first operand encoding.
       Both pointers and offset are initialized; flags are overwritten by later calls. */
    asm("add %0, %0, %1" : "+l"(tiles) : "l"(cursor_offset) : "cc");
    DecodePairTiles(tiles, (void *)0x083C4C14);
    InitializePairTransfer(AllocatePairTransfer(), tiles,
        (void *)(alternate ? 0x06016C00 : 0x06015800), 288);
    clear_cell = (void **)0x0836D4B8;
    ClearPairRows(*(u8 **)0x0200F444 + 2012, 52, *clear_cell);
}
