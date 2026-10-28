typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct ActorDirectionByteView { u8 unknown_00[31]; u8 stored_direction; };
/* Keep the unsigned storage load separate from the signed return projection. */
s32 ReadActorSignedDirection(const struct ActorDirectionByteView *actor)
{
    u32 shifted = actor->stored_direction;
    shifted <<= 24;
    return (s32)shifted >> 24;
}
