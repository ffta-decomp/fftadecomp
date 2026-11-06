typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct DmaRequest;
extern u8 *PairContext;
extern u8 WorkTiles[];
struct PairBank { u8 prefix[0x3c34]; u8 pair_bytes[0]; };
extern struct PairBank PairBank;
struct Definition { u8 primary; u8 secondary; u8 unknown[14]; };
extern const struct Definition Definitions[];
extern const u8 *FallbackText;
extern u32 TransferBank[];
extern void (*ClearBytesCell)(void *, u32);
extern const u8 *LookupPairLabel(u16);
extern u32 RenderPairLabel(void *, const void *, const u8 *, u32, u32);
extern void BuildPairTileRow(void *, u8, u8, u8, u8, u8, u16, u8);
extern struct DmaRequest *TakePairRequest(void);
extern void QueuePairTiles(struct DmaRequest *, u32, u32, u16);
extern void InitializePairMarker(void);
__asm__(".global PairContext\n.set PairContext,0x0200f444\n"
        ".global WorkTiles\n.set WorkTiles,0x02004270\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
        ".global PairBank\n.set PairBank,0x02000000\n"
        ".global Definitions\n.set Definitions,0x08528f34\n"
        ".global FallbackText\n.set FallbackText,0x085567f0\n"
        ".global TransferBank\n.set TransferBank,0x030008b0\n"
        ".global ClearBytesCell\n.set ClearBytesCell,0x0836d4b8\n"
        ".global LookupPairLabel\n.thumb_set LookupPairLabel,0x080cb4e1\n"
        ".global RenderPairLabel\n.thumb_set RenderPairLabel,0x08015111\n"
        ".global BuildPairTileRow\n.thumb_set BuildPairTileRow,0x080157a9\n"
        ".global TakePairRequest\n.thumb_set TakePairRequest,0x0802dfcd\n"
        ".global QueuePairTiles\n.thumb_set QueuePairTiles,0x08000add\n"
        ".global InitializePairMarker\n.thumb_set InitializePairMarker,0x0802e009\n");

/* Each pair has two separately rendered labels. Helpers may replace the live
 * context/count; only the selected primary ID survives those calls. */
void CoreFrontier_0002E160(void)
{
    int row = 0;
    u8 *destination;
    register u32 label_id __asm__("r4");
    const u8 *text;
    struct DmaRequest *request;

    if (row < PairContext[8]) {
        do {
            label_id = 2 * row;
            __asm__("" : "+r"(label_id));
            destination = WorkTiles + 704 * row;
            ClearBytesCell(destination, 704);
            label_id = PairBank.pair_bytes[label_id];
            if (label_id != 0) {
                text = LookupPairLabel(label_id);
                RenderPairLabel(PairContext + 16, destination, text, 0, 1);
            } else {
                register void *text_context __asm__("r0") = PairContext + 16;
                __asm__("" : "+r"(text_context));
                text = FallbackText;
                RenderPairLabel(text_context, destination, text, 0, 1);
            }
            BuildPairTileRow(PairContext + 0x49c + 104 * row,
                             0, 0, 11, 1, 26, (u16)(22 * row + 270), 7);

            destination = WorkTiles + 704 * (row + PairContext[8]);
            ClearBytesCell(destination, 704);
            {
                const u8 *definition_base;
                register u32 definition_offset __asm__("r0") = label_id * 16;
                __asm__("" : "+r"(definition_offset));
                /* Original forms the table base separately, then reads lane 1. */
                definition_base = (const u8 *)Definitions;
                __asm__("" : "+r"(definition_base));
                label_id = definition_base[definition_offset + 1];
            }
            if (label_id != 0) {
                text = LookupPairLabel(label_id);
                RenderPairLabel(PairContext + 16, destination, text, 0, 1);
            } else {
                register void *text_context __asm__("r0") = PairContext + 16;
                __asm__("" : "+r"(text_context));
                text = FallbackText;
                RenderPairLabel(text_context, destination, text, 0, 1);
            }
            {
                register u32 row_address __asm__("r0") = 104u * row + (u32)PairContext;
                __asm__("" : "+r"(row_address));
                BuildPairTileRow((void *)(row_address + 0x4b4),
                                 0, 0, 11, 1, 26,
                                 (u16)(22 * (row + PairContext[8]) + 270), 8);
            }
            ++row;
        } while (row < PairContext[8]);
    }
    request = TakePairRequest();
    QueuePairTiles(request, (u32)WorkTiles, TransferBank[4] + 8640,
                   (u16)(PairContext[8] * 352));
    PairContext[14] = 0;
    InitializePairMarker();
}
