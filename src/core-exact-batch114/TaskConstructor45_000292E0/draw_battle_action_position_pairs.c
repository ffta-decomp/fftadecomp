typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
struct ActionDrawPoint { s16 x, y; u8 remaining[4]; };
extern const u8 ActionPairAssetA[], ActionPairAssetB[];
extern void DrawActionPair_08001F34(const u8 *, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32);
void TaskConstructor45_000292E0(u8 *object)
{
    int index = 0;
    const u8 *asset = ActionPairAssetA;
    register u32 zero asm("r4");
    register struct ActionDrawPoint *point asm("r5");
    asm("" : "+r" (index));
    asm("" : "+r" (asset));
    zero = 0;
    asm("" : "+r" (zero));
    point = (struct ActionDrawPoint *)(object + 128);
    asm("" : "+r" (point));
    do {
        DrawActionPair_08001F34(asset, point->x + 8, point->y, 0,
            zero, zero, zero, zero, index != 0 ? 16 : index, zero, zero);
        DrawActionPair_08001F34(ActionPairAssetB, point->x, point->y, 0,
            zero, zero, zero, zero, zero, zero, zero);
        ++point;
        ++index;
    } while (index <= 1);
}
asm(".set ActionPairAssetA,0x08391544\n.set ActionPairAssetB,0x08391530\n.thumb_set DrawActionPair_08001F34,0x08001f35\n");
