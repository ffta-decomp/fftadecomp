typedef unsigned char u8;
struct ActorPaletteView { u8 reserved[30]; u8 palette_index; };
u8 ReadActorPaletteIndex(const struct ActorPaletteView *actor)
{
    return actor->palette_index;
}
