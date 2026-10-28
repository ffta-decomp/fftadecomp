typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
struct UnitTaskRows { u8 unknown0[6]; s16 row; };
struct LayerTileBindings { u8 unknown0[20]; u8 *tiles; };
struct TaskVisualRecord;
extern struct LayerTileBindings gLayer2;
extern struct LayerTileBindings gLayer3;
extern struct TaskVisualRecord *TakeUnitTaskRingRecord(void);
extern void QueueTileRectangle(struct TaskVisualRecord *, const void *, void *,
                               u32, u32, u32, u32);
__asm__(".global gLayer2\n.set gLayer2,0x030008b0\n.global gLayer3\n.set gLayer3,0x03000990\n.global TakeUnitTaskRingRecord\n.thumb_set TakeUnitTaskRingRecord,0x0802ba09\n.global QueueTileRectangle\n.thumb_set QueueTileRectangle,0x08000bad");
/* Exact source offsets identify buffers; the call dimensions do not prove their capacity. */
void RestorePrimaryTaskLayerRows(struct UnitTaskRows *payload)
{
    QueueTileRectangle(TakeUnitTaskRingRecord(), (u8 *)payload + 1064,
                       gLayer3.tiles + payload->row * 64, 17, 6, 34, 64);
    QueueTileRectangle(TakeUnitTaskRingRecord(), (u8 *)payload + 808,
                       gLayer2.tiles + payload->row * 64, 17, 7, 34, 64);
}
