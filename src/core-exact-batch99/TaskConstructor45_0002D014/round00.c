typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
struct UnitTaskRows { u8 unknown0[6]; s16 row; };
struct LayerTileBindings { u8 unknown0[20]; u8 *tiles; };
extern struct LayerTileBindings gLayer2;
extern struct LayerTileBindings gLayer3;
extern void FillTileRectangle(void *, u32, u32, u32, u32);
__asm__(".global gLayer2\n.set gLayer2,0x030008b0\n.global gLayer3\n.set gLayer3,0x03000990\n.global FillTileRectangle\n.thumb_set FillTileRectangle,0x08016a99");
/* The first fill can change the live row or bindings used by the second fill. */
void ClearPrimaryTaskLayerRows(struct UnitTaskRows *payload)
{
    FillTileRectangle(gLayer2.tiles + payload->row * 64, 17, 7, 0, 32);
    FillTileRectangle(gLayer3.tiles + payload->row * 64, 17, 6, 0, 32);
}
