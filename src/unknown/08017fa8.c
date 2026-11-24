typedef short s16;
struct PairCursorDescriptor { const void *asset; s16 x, y; };
void SetBattlePairCursorDescriptor(struct PairCursorDescriptor *descriptor,
                                  const void *asset, s16 x, s16 y)
{
    descriptor->asset = asset;
    descriptor->x = x;
    descriptor->y = y;
}
